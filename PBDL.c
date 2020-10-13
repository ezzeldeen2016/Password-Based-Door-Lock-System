/*
 * PBDL.c
 *
 * Created: 09/10/2020 10:49:01 م
 *  Author: omar.M.ezzeldeen
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include "GPIO.h"
#include "LCD.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
void keypad_phone();
void lcd_screen();
void door_motor();
TaskHandle_t kypd;
TaskHandle_t lcd;
TaskHandle_t motor;
QueueHandle_t kypd_press;
QueueHandle_t door;
int main(void)
{
	bin_direction(C, 0,output);
	lcd_init();
	keypad_init();
	xTaskCreate(keypad_phone,"keypad",85,NULL,0,&kypd);
	xTaskCreate(lcd_screen,"screen",85,NULL,0,&lcd);
	xTaskCreate(door_motor,"door",85,NULL,0,&motor);
	vTaskStartScheduler();
	while(1);
}

void keypad_phone()
{
	unsigned char n=0,x=0;
	char i=0;
	kypd_press=xQueueCreate(1,sizeof(char));
	while(1)
	{
		n=scan();
		xQueueSend(kypd_press,(void*)&n,( TickType_t ) 0);
		vTaskDelay(1);
	}
}

void lcd_screen()
{
	char keypressed=0;
	char i=0,j=0;
	char digit,x=0;
	char keys[5];
	char password[5]={'1','2','3','4','\0'};
	char ans=0;
	door=xQueueCreate(1,sizeof(char));
	while(1)
	{
		xQueueReceive(kypd_press,(void*)&keypressed,( TickType_t ) 0);
		lcd_command(0x80);
		lcd_print("Enter password");
		lcd_command(0xC0);
		if(keypressed!=0 && x==0)
		{
			digit=keypressed;
			x=1;
		}
		if(keypressed ==0 && x==1 && i<4)
		{
			keys[i]=digit;
			x=0;
			i++;
			for(j=0;j<i;j++)
			{
				lcd_print("*");
			}
		}
		if(i==4)
		{
			for(j=0;j<4;j++)
			{
				if(keys[j]!=password[j])
				{
					ans=1;
				}
			}
			if(ans!=1)
			{
				ans=2;
			}
		}
		if(i==4 && ans==1)
		{
			vTaskSuspend(kypd);
			lcd_command(0xC0);
			lcd_print("wrong password");
			vTaskDelay(1000);
			i=0;
			ans=0;
			x=0;
			keypressed=0;
			lcd_command(0x01);
			vTaskResume(kypd );
		}
		else if(i==4 && ans==2)
		{
			vTaskSuspend(kypd);
			lcd_command(0xC0);
			lcd_print("opening....");
			xQueueSend(door,(void*)&ans,( TickType_t ) 0);
			vTaskDelay(1000);
			i=0;
			ans=0;
			x=0;
			keypressed=0;
			lcd_command(0x01);
			vTaskResume(kypd );
		}
		
		vTaskDelay(1);
	}
}

void door_motor()
{
	char state=0;
	while(1)
	{
		xQueueReceive(door,(void*)&state,( TickType_t ) 0);
		if(state==2)
		{
			bin_write(C, 0, 1);
			vTaskDelay(500);
			state=0;
		}
		bin_write(C, 0, 0);
		vTaskDelay(1);
	}
}