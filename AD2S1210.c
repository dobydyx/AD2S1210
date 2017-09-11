/********************************************************************************
 Author : CAST (China Applications Support Team) 

 Date :   April, 2011

 File name :   AD2S1210.c

 Description :	 Use the GPIO to simulate the SPI communication of AD2S1210

 Hardware plateform : 	ADuC7026 and AD2S1210
********************************************************************************/

#include "ADuC7026.h"
#include "ADuC7026Driver.h"
#include "AD2S1210.h"

// add the c file here


//---------------------------------
//void WriteToAD2S(unsigned char count,unsigned char *buf);
//---------------------------------
//Function that writes to the AD2S via the SPI port. 
//--------------------------------------------------------------------------------
void AD2S1210Initiate()
{
//RESET->0 initially  
	CLR_RESET();  
	SET_SPL();
	delay(1);
	SET_RESET(); 
	delay(2);
	CLR_SPL();
	delay(1);
	SET_SPL();
}

void AD2S1210SelectMode(unsigned char mode)
{
	if (mode==POSITION)
	{
		CLR_A0();
		CLR_A1();
		delay(1);		//Normal Mode position output
	}
	else if (mode==VELOCITY)
	{
		CLR_A0();
		SET_A1();
		delay(1);		//Normal Mode velocity output
	}
	else if (mode==CONFIG)
	{
		SET_A0();
		SET_A1();
		delay(1);		//Configuration Mode
	}
}

void WriteToAD2S1210(unsigned char address, unsigned char data)
{
	unsigned	char	buf;

	//write control register address
	buf = address;

	SET_SCLK();
	delay(1);
	SET_CS();
	delay(1);
	CLR_CS();
	delay(1);
	
	SET_WR();
	delay(1);
	CLR_WR();
	delay(1);

	SPIWrite(1,&buf);	  	 
	
	SET_WR();
	delay(1);	
	SET_CS();	
	//write control register address

	//write control register data
	buf = data;

	SET_SCLK();
	delay(1);
	SET_CS();
	delay(1);
	CLR_CS();
	delay(1);
	
	SET_WR();
	delay(1);
	CLR_WR();
	delay(1);

	SPIWrite(1,&buf);	  	 

	SET_WR();
	delay(1);	
	SET_CS();
	//write control register data
}

void ReadFromAD2S1210(unsigned char mode, unsigned char address, unsigned char * buf)
{

	if (mode==CONFIG)
	{
		
		//write control register address
		buf[0] = address;

		SET_SCLK();
		delay(1);
		SET_CS();
		delay(1);
		CLR_CS();
		delay(1);
		
		SET_WR();
		delay(1);
		CLR_WR();
		delay(1);

		SPIWrite(1,buf);

		SET_WR();
		delay(1);	
		SET_CS();
		//write control register address


		//read 1-byte register
		SET_SCLK();
			
		SET_CS();
		SET_WR();
		delay(1);
	
		CLR_CS();
		delay(1);
	
		CLR_SCLK();	
		delay(1);
		
		CLR_WR();
		delay(1);

		SPIRead(1,buf);	

		SET_WR();
		delay(1);

		SET_CS();
		//read 1-byte register
	}
	else if (mode==POSITION||mode==VELOCITY)
	{
		SET_SPL();
		delay(1);
		CLR_SPL();
		delay(5);

		//read 3-byte register 
		SET_SCLK();
				
		SET_CS();
		SET_WR();
		delay(1);
		
		CLR_CS();
		delay(1);
	
		CLR_SCLK();	
		delay(1);
			
		CLR_WR();
		delay(1);
	
		SPIRead(3,buf);		//read data register
	
		SET_WR();
		delay(1);
	
		SET_CS();
		//read 3-byte register


	}
}

void AD2S1210SoftReset(void)
{
	unsigned char buf=	SOFTRESET;
	SPIWrite (1,&buf);	  	//soft reset 
	delay(10);
}
