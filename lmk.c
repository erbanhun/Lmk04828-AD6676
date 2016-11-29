#include "C8051F340.h"
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

sbit LMK_RESET  = P2^3;		//output
sbit LMK_SYNC   = P2^4;		//output
sbit LMK_SCK    = P2^5;		//output
sbit LMK_SDIO   = P2^6;		//output
sbit LMK_CSB    = P2^7;		//output

sbit STATUS_LD1 = P1^6; // input
sbit STATUS_LD2 = P1^7; // input
sbit CLKIN_SEL0 = P2^1; // input
sbit CLKIN_SEL1 = P2^2; // input
extern void delay(uint cnt);			 // 延时


void iniLMK04828(void);			 // 初始化LMK04828
uchar read_CLK04828(uint add);
void CLK_SPI04828(uint add, uchar num);

/*---------------------------------------
purpose:初始化CLK
input:10M, output:2211.84M

----------------------------------------*/

/*---------------------------------------
purpose:在CLK指定的地址写寄存器的值
parameters:
modify:
----------------------------------------*/


 void iniLMK04828(void)
{		idata uchar a=0;
	
	LMK_RESET  =0;	
		delay(5);
		LMK_RESET  =1;	
    	delay(5);
		LMK_RESET  =0;	
		delay(5);
a=read_CLK04828(0x13b);
CLK_SPI04828(0x13b,0x12);
a=read_CLK04828(0x13b);

CLK_SPI04828(0X0000,0X80);//Programming register 0x000 with RESET = 1.
CLK_SPI04828(0X0002,0X00);// normal:0;powerdown:1//Programming registers in numeric order from 0x000 to 0x165.

CLK_SPI04828(0X0100,0X10);	//0,1 138.24MHz,1/16,LVDS
CLK_SPI04828(0X0103,0X00);
CLK_SPI04828(0X0104,0X20);
CLK_SPI04828(0X0106,0X70);
CLK_SPI04828(0X0107,0X11);	 //format lvds,lvds

//	CLK_SPI04828(0X0105,0X14);
	
/*CLK_SPI04828(0X0108,0X04); //2,3  552.96MHz,1/4,LVPECL
CLK_SPI04828(0X0109,0X45); //CNTL=5,CNTH=4
	CLK_SPI04828(0X010e,0X70);//DDLY_PD=0
	CLK_SPI04828(0X0141,0X02);//DDLY_EN=1
	CLK_SPI04828(0X0144,0X7D);//SYNC_DIS2=0,QITA =1
	CLK_SPI04828(0X0143,0X13);//SYNC_MODE=3
	CLK_SPI04828(0X0143,0X12);
	CLK_SPI04828(0X0139,0X02);//SYNC_MODE=2 SYSREF_MUX=2
	CLK_SPI04828(0X0142,0X08);//DDLY_STEP_CNT=1

CLK_SPI04828(0X010b,0X00);
CLK_SPI04828(0X010c,0X20);
CLK_SPI04828(0X010d,0X18);
CLK_SPI04828(0X010e,0X70);
CLK_SPI04828(0X010f,0X55);
*/

CLK_SPI04828(0X0108,0X02); //2,3  1105.926MHz,1/2,LVPECL
CLK_SPI04828(0X010b,0X00);
CLK_SPI04828(0X010c,0X20);
//CLK_SPI04828(0X010d,0X11);
CLK_SPI04828(0X010e,0X70);
CLK_SPI04828(0X010f,0X55);

CLK_SPI04828(0X0110,0X01); //4,5 2211.84MHZ,sin(LVPECL)
CLK_SPI04828(0X0113,0X02);
CLK_SPI04828(0X0114,0X20);
CLK_SPI04828(0X0116,0X70);
CLK_SPI04828(0X0117,0X55);

CLK_SPI04828(0X0118,0X01);//6,7	 2211.84MHZ,sin(LVPECL)
CLK_SPI04828(0X011b,0X02);
CLK_SPI04828(0X011c,0X20);
CLK_SPI04828(0X011e,0X70);
CLK_SPI04828(0X011f,0X55);

CLK_SPI04828(0X0120,0X10);//8,9 138.24MHz ,1/16,LVDS
//CLK_SPI04828(0X0121,0X58);
CLK_SPI04828(0X0123,0X00);
CLK_SPI04828(0X0124,0X20);
CLK_SPI04828(0X0126,0X71); //sdclk pd
CLK_SPI04828(0X0127,0X11);
							 
CLK_SPI04828(0X0128,0X10); //10,11	138.24MHz ,1/16,LVDS
CLK_SPI04828(0X012b,0x00);
CLK_SPI04828(0X012c,0X20);	
CLK_SPI04828(0X012e,0X71); //sdclk pd
CLK_SPI04828(0X012f,0X11);

CLK_SPI04828(0X0130,0X10);	// 12,13	138.24MHz ,1/16,LVDS
CLK_SPI04828(0X0133,0X00);
CLK_SPI04828(0X0134,0X20);
//CLK_SPI04828(0X0135,0X16);
CLK_SPI04828(0X0136,0X70);
CLK_SPI04828(0X0137,0X11);



CLK_SPI04828(0X0138,0X40);	   //vco=clkin1	,osc pd







//CLK_SPI04828(0X0109,0X58);

//CLK_SPI04828(0X0143,0XFD);


/*CLK_SPI04828(0X0139,0X02);	  //sysref_mux=2
CLK_SPI04828(0X013a,0X01);
CLK_SPI04828(0X013b,0X80);	   //sys=div192

CLK_SPI04828(0X0140,0XF9);	
CLK_SPI04828(0X0143,0X10);
CLK_SPI04828(0X016a,0X60);*/
//sysref
CLK_SPI04828(0X0143,0X01);	 //sync_pol=0,sync_mode=1;
CLK_SPI04828(0X0139,0X00);	  //sysref_mux=0
CLK_SPI04828(0X013a,0X00);
CLK_SPI04828(0X013b,0XC0);	   //sys=div192 00C0

CLK_SPI04828(0X0140,0XF8);	  //pd mode  sysref_pd=0,sysref_ddly_pd=0,	 sysref_plsr_pd=0
CLK_SPI04828(0X0143,0X91);	 //sync_en=1;sysref_clr=1;

CLK_SPI04828(0X0144,0X00);	 //sysref_dis=0;

CLK_SPI04828(0X0143,0XB1);	 //sysref_pol=1then sysref_pol=0;
CLK_SPI04828(0X0143,0X91);	 //sysref_pol=1then sysref_pol=0;


CLK_SPI04828(0X0144,0Xff);	 //sysref_dis=1;
CLK_SPI04828(0X0143,0X11);	 //sysref_clr=0;

CLK_SPI04828(0X016a,0X60);
CLK_SPI04828(0X0143,0X10);	 //sync_mode=2;
CLK_SPI04828(0X0139,0X02);	  //sysref_mux=2



CLK_SPI04828(0X0146,0X10);
CLK_SPI04828(0X0147,0X13);// clk1in
CLK_SPI04828(0X0148,0X13);
CLK_SPI04828(0X0149,0X13);
CLK_SPI04828(0X014A,0X02);	 //RESET=INPUT	1
CLK_SPI04828(0X0150,0X40);


//CLK_SPI04828(0X016a,0X40);
CLK_SPI04828(0X1FFD,0X0);
CLK_SPI04828(0X1FFE,0X0);
CLK_SPI04828(0X1FFF,0X53);		



	}


/*---------------------------------------
purpose:在CLK指定的地址写寄存器的值
parameters:
modify:
----------------------------------------*/
void CLK_SPI04828(uint add, uchar num)
{	
	idata uchar i=0;
	idata ulong reg=0;

	LMK_SDIO = 0;
	LMK_CSB=1;
	reg=add;
	reg=reg<<8;
	reg=reg+num;
	LMK_CSB=0;
	do
	{
		if((reg&0x800000) == 0x800000)
			LMK_SDIO = 1;
		else
			LMK_SDIO = 0;
		LMK_SCK = 0;
		delay(10);						//最小50ns
		LMK_SCK= 1;
		delay(10);
		LMK_SCK = 0;
		reg=reg<<1;
		i++;
	}while(i<24);
	LMK_CSB=1;
}
/*---------------------------------------
purpose:read CLK
parameters:
modify:
----------------------------------------*/									 
uchar read_CLK04828(uint add)
{	
	idata uchar i=0;
	idata uint reg=0;
	idata uchar da_temp,temp;
		
	LMK_CSB=1;
	reg=add+0x8000;						//16bit instruction
	LMK_SDIO = 0;
	LMK_CSB=0;
	do									
	{
		if((reg&0x8000) == 0x8000)
			LMK_SDIO = 1;
		else
			LMK_SDIO = 0;
		LMK_SCK = 0;
		delay(10);						//最小50ns
		LMK_SCK = 1;
		delay(10);
		LMK_SCK = 0;
		reg=reg<<1;
		i++;
	}while(i<16);

	i=0;

   P2MDOUT  = 0xb8;                    //output,p2.6 input
   P2       = 0x40;

	do
	{
		LMK_SCK = 0;
		delay(10);						//最小50ns
		LMK_SCK = 1;
		da_temp=da_temp<<1;
		temp=LMK_SDIO;
		da_temp=temp+da_temp;
		delay(10);
		LMK_SCK = 0;
		i++;
	}while(i<8);
	LMK_CSB=1;

   P2MDOUT  = 0xf8;                    //output
   P2       = 0x00;
	return da_temp;
}
