/*
 * keypad_phone.c
 *
 * Created: 10/10/2020 05:14:58 ص
 *  Author: omar.M.ezzeldeen
 */ 
#include "keypad-phone.h"
unsigned char m[4][3]={{'1','2','3'},
	                    {'4','5','6'},
						{'7','8','9'},
						{'*','0','#'}};
unsigned char outbins[]={bin1,bin2,bin3};
unsigned char inbins[]={binA,binB,binC,binD};
void keypad_init()
{
	bin_direction(keypadport , binA, input);
	bin_direction(keypadport , binB, input);
	bin_direction(keypadport , binC, input);
	bin_direction(keypadport, binD, input);
	bin_direction(keypadport , bin1, output);
	bin_direction(keypadport , bin2, output);
	bin_direction(keypadport, bin3, output);
	
}
char keypad_read()
{
	char y=0;
	while(y==0)
	{
		y=scan();
		
	}
	return y;
}

unsigned char scan()
{
	char i,j;
	for(i=0;i<3;i++)
	{
			bin_write(keypadport,outbins[i],1);
			for(j=0;j<4;j++)
			{
				if(bin_read(keypadport,inbins[j])==1)
				{
					bin_write(keypadport,outbins[i],0);
					return m[j][i];
				}
			}
			bin_write(keypadport,outbins[i],0);
	}
	
	return 0;
}
