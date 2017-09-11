/********************************************************************************
 Author : CAST (China Applications Support Team) 

 Date :   April, 2011

 File name :   AD2S1210.h

 Description :	 Use the GPIO to simulate the SPI communication of AD2S1210

 Hardware plateform : 	ADuC7026 and AD2S1210
********************************************************************************/

#ifndef AD2S1210_H
#define AD2S1210_H

// add the header file here

//Mode Select
#define POSITION	0
#define	VELOCITY	1
#define CONFIG		2  


//Register Map 
#define	POSITIONMSB		0x80
#define	POSITIONLSB		0x81
#define	VELOCITYMSB		0x82
#define	VELOCITYLSB		0x83
#define	LOSTHRES		0x88
#define	DOSORTHRES		0x89
#define	DOSMISTHRES		0x8A
#define	DOSRSTMXTHRES	0x8B
#define	DOSRSTMITHRES	0x8C
#define	LOTHITHRES		0x8D
#define	LOTLOTHRES		0x8E
#define	EXFREQUENCY		0x91
#define	CONTROL			0x92
#define	SOFTRESET		0xF0
#define	FAULT			0xFF
#define POS_VEL			0x00  //void register for normal read address

void AD2S1210Initiate(void);
void AD2S1210SelectMode(unsigned char mode);
void AD2S1210SoftReset(void);
void WriteToAD2S1210(unsigned char address, unsigned char data);
void ReadFromAD2S1210(unsigned char mode, unsigned char address, unsigned char * buf);

#endif

