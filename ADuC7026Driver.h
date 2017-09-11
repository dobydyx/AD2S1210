/********************************************************************************
 Author : CAST (China Applications Support Team) 

 Date :   April, 2011

 File name :   ADuC7026Driver.h

 Description :	 Use the GPIO to simulate the SPI communication of AD2S1210

 Hardware plateform : 	ADuC7026 and AD2S1210
********************************************************************************/

#ifndef ADUC7026_DRIVER_H
#define ADUC7026_DRIVER_H

// add the header file here
//GPIO Define
#define SET_CS()		GP4DAT = (GP4DAT | 0x00080000)	//P4.3->CS
#define CLR_CS()		GP4DAT = (GP4DAT & 0xFFF7FFFF)

#define	SET_SCLK()		GP4DAT = (GP4DAT | 0x00100000)	//P4.4->SCLK
#define	CLR_SCLK()		GP4DAT = (GP4DAT & 0xffefffff)

#define SET_SDI()		GP4DAT = (GP4DAT | 0x00200000)	//P4.5->SDI
#define CLR_SDI()		GP4DAT = (GP4DAT & 0xffdfffff)

#define	SET_A0()		GP4DAT = (GP4DAT | 0x00400000)	//P4.6->A0
#define	CLR_A0()		GP4DAT = (GP4DAT & 0xffbfffff)

#define SET_A1()		GP4DAT = (GP4DAT | 0x00800000)	//P4.7->A1
#define CLR_A1()		GP4DAT = (GP4DAT & 0xff7fffff)

#define SET_WR()		GP4DAT = (GP4DAT | 0x00040000)	//P4.2->WR
#define CLR_WR()		GP4DAT = (GP4DAT & 0xfffbffff)

#define SET_SPL()		GP4DAT = (GP4DAT | 0x00020000)	//P4.1->SPL
#define CLR_SPL()		GP4DAT = (GP4DAT & 0xfffdffff)

//#define SET_RD()		GP4DAT = (GP4DAT | 0x00010000)	//P4.0->RD for parallel
//#define CLR_RD()		GP4DAT = (GP4DAT & 0xfffeffff)

#define SET_RESET()		GP4DAT = (GP4DAT | 0x00010000)	//P4.0->RESET
#define CLR_RESET()		GP4DAT = (GP4DAT & 0xfffeffff)



void ADuC7026_Initiate(void);

void delay (int length);	   
void putchar(unsigned char ch);
void SPIWrite(unsigned char count, unsigned char *buf);
void SPIRead(unsigned char count, unsigned char *buf);

#endif





