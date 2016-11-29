#include "C8051F340.h"
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

sbit AD_SCK  = P1^1;		//output
sbit AD_SDIO   = P1^2;		//output
sbit AD_CSB    = P1^3;		//output
sbit AD_AGC1   = P1^4;		//output
sbit AD_AGC2    = P1^5;		//output


extern void delay(uint cnt);			 // 延时


void iniAD6676(void);			 // 初始化LMK04828
uchar read_AD6676(uint add);
void CLK_SPIAD6676(uint add, uchar num);

void iniAD6676(void)
{
idata uchar a=0;
CLK_SPIAD6676(0x000,0x88);
CLK_SPIAD6676(0x000,0x00);
a=read_AD6676(0x003);
a=read_AD6676(0x101);
CLK_SPIAD6676(0x101,0x1F);
a=read_AD6676(0x101);
}

void CLK_SPIAD6676(uint add, uchar num)
{	
	idata uchar i=0;
	idata ulong reg=0;

	AD_SDIO = 0;
	AD_CSB=1;
	reg=add;
	reg=reg<<8;
	reg=reg+num;
	AD_CSB=0;
	do
	{
		if((reg&0x800000) == 0x800000)
			AD_SDIO = 1;
		else
			AD_SDIO = 0;
		AD_SCK = 0;
		delay(10);						//最小50ns
		AD_SCK= 1;
		delay(10);
		AD_SCK = 0;
		reg=reg<<1;
		i++;
	}while(i<24);
	AD_CSB=1;
}
/*---------------------------------------
purpose:read CLK
parameters:
modify:
----------------------------------------*/									 
uchar read_AD6676(uint add)
{	
	idata uchar i=0;
	idata uint reg=0;
	idata uchar da_temp,temp;
		
	AD_CSB=1;
	reg=add+0x8000;						//16bit instruction
	AD_SDIO = 0;
	AD_CSB=0;
	do									
	{
		if((reg&0x8000) == 0x8000)
			AD_SDIO = 1;
		else
			AD_SDIO = 0;
		AD_SCK = 0;
		delay(10);						//最小50ns
		AD_SCK = 1;
		delay(10);
		AD_SCK = 0;
		reg=reg<<1;
		i++;
	}while(i<16);

	i=0;

   P1MDOUT  = 0x0B;                    //output,p2.6 input
   P1       = 0x04;

	do
	{
		AD_SCK = 0;
		delay(10);						//最小50ns
		AD_SCK = 1;
		da_temp=da_temp<<1;
		temp=AD_SDIO;
		da_temp=temp+da_temp;
		delay(10);
		AD_SCK = 0;
		i++;
	}while(i<8);
	AD_CSB=1;

   P1MDOUT  = 0x0f;                    //output
   P1       = 0x00;
	return da_temp;
}
