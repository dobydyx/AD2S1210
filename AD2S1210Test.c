/********************************************************************************
 Author : CAST (China Applications Support Team) 

 Date :   April, 2011

 File name :   AD2S1210Test.c

 Description :	 Use the GPIO to simulate the SPI communication of AD2S1210

 Hardware plateform : 	ADuC7026 and AD2S1210
********************************************************************************/

#include "ADuC7026.h"
#include "ADuC7026Driver.h"
#include "AD2S1210.h"

int main(void)
{
	// Add the test functions here
	unsigned	char	buf[4] = {0,0,0,0};

    ADuC7026_Initiate();   
	AD2S1210Initiate(); 

	AD2S1210SelectMode(CONFIG);		//Configuration Mode

	
	WriteToAD2S1210(CONTROL, 0x7F);  	//write control register address 

	ReadFromAD2S1210(CONFIG, CONTROL, buf);		//read control register
	putchar(buf[0]);

	WriteToAD2S1210(EXFREQUENCY, 0x14);	  	//write frequency register address for 5KHz	Excitation

	ReadFromAD2S1210(CONFIG, EXFREQUENCY, buf);		//read frequency register
	putchar(buf[0]);

	ReadFromAD2S1210(CONFIG, POSITIONMSB, buf);		//read position register MSB
 	putchar(buf[0]);

	ReadFromAD2S1210(CONFIG, POSITIONLSB, buf);		//read position register LSB
 	putchar(buf[0]);

	delay(5);

	WriteToAD2S1210(LOSTHRES, 0x01);  	//write LOS register address >0.5V	

	ReadFromAD2S1210(CONFIG, LOSTHRES, buf);		//read control register
	putchar(buf[0]);

	WriteToAD2S1210(DOSMISTHRES, 0x0D);	//write DOS register address >0.5V	



//	AD2S1210SoftReset();


	ReadFromAD2S1210(CONFIG, FAULT, buf); 		//read/clear fault register
	putchar(buf[0]);
	

	AD2S1210SelectMode(POSITION);		//Normal Mode position output

	ReadFromAD2S1210(POSITION, POS_VEL, buf);		//read data register
	putchar(buf[2]);
	putchar(buf[1]);
	putchar(buf[0]);

	AD2S1210SelectMode(VELOCITY);		//Normal Mode velocity output
								   
	ReadFromAD2S1210(VELOCITY, POS_VEL, buf);		//read data register
	putchar(buf[2]);
	putchar(buf[1]);
	putchar(buf[0]);

	while(1)
    {
	
/*
//	for normal mode
	AD2S1210SelectMode(POSITION);		//Normal Mode position output

	ReadFromAD2S1210(POSITION, POS_VEL, buf);
	putchar(buf[2]);
	putchar(buf[1]);
	putchar(buf[0]);
	delay(500000);

	AD2S1210SelectMode(VELOCITY);		//Normal Mode velocity output
								   
	ReadFromAD2S1210(VELOCITY, POS_VEL, buf);
	putchar(buf[2]);
	putchar(buf[1]);
	putchar(buf[0]);
	delay(5000000);	
		  
//	for config mode, position output
	AD2S1210SelectMode(CONFIG);

	ReadFromAD2S1210(CONFIG, POSITIONMSB, buf);		//read position register MSB
 	putchar(buf[0]);
	delay(500000);
	ReadFromAD2S1210(CONFIG, POSITIONLSB, buf);		//read position register LSB
 	putchar(buf[0]);
	delay(5000000);	
*/
	;
	}

}
