/********************************************************************************
 Author : CAST (China Applications Support Team) 

 Date :   April, 2011

 File name :   ADuC7026Driver.c

 Description :	 Use the GPIO to simulate the SPI communication of AD2S1210

 Hardware plateform : 	ADuC7026 and AD2S1210
********************************************************************************/

#include "ADuC7026.h"
#include "ADuC7026Driver.h"

/*    Function Pointers for Interrupts  */
// Copied from irq_arm.c in Keil uV4, required 
tyVctHndlr    IRQ     = (tyVctHndlr)0x0;
tyVctHndlr    SWI     = (tyVctHndlr)0x0;
tyVctHndlr    FIQ     = (tyVctHndlr)0x0;
tyVctHndlr    UNDEF   = (tyVctHndlr)0x0;
tyVctHndlr    PABORT  = (tyVctHndlr)0x0;
tyVctHndlr    DABORT  = (tyVctHndlr)0x0;

void	IRQ_Handler   (void) __irq;
void	SWI_Handler   (void) __irq;
void	FIQ_Handler   (void) __irq;
void	Undef_Handler (void) __irq;
void	PAbt_Handler  (void) __irq;
void	DAbt_Handler  (void) __irq;

void	IRQ_Handler(void) __irq
{
	if ( *IRQ !=0x00)
	{
		IRQ();
	}
}

void	FIQ_Handler(void) __irq
{
	if ( *FIQ !=0x00)
	{
		FIQ();
	}
}

void	SWI_Handler(void) __irq
{
	if ( *SWI !=0x00)
	{
		SWI();
	}
}

void	Undef_Handler(void)__irq 
{
	if ( *UNDEF !=0x00)
	{
		UNDEF();
	}
}

void	PAbt_Handler(void) __irq
{
	if ( *PABORT !=0x00)
	{
		PABORT();
	}
}

void	DAbt_Handler(void) __irq
{
	if ( *DABORT !=0x00)
	{
		DABORT();
	}
}
/*    Function Pointers for Interrupts  */

// add the c file here
void ADuC7026_Initiate(void)
{
    //Clock Initial
    POWKEY1 = 0x01;				//Start PLL Setting
    POWCON = 0x00;				//Set PLL Active Mode With CD = 0  CPU CLOCK DIVIDER = 41.78MHz
    POWKEY2 = 0xF4;				//Finish PLL Setting

	GP1CON = 0x011;				  //PIN set up for UART
     
	GP0DAT = GP0DAT & 0xDFFFFFFF; //Configure the P0.5 pin as input for SDOUT
	GP4DAT = GP4DAT | 0xffff0000; //Configure the P4.x pin as output
								  
								 								  
   	//UART Initial?¨º?Baud Rate = 9600								  	
	COMCON0 = 0x080;  
	COMDIV0 = 0x088;    		
	COMDIV1 = 0x000;
	COMCON0 = 0x007; 

}  

void delay (int length)
{
	while (length >0)
    	length--;
}

void putchar(unsigned char ch)/* Write character to Serial Port  */  
{          
	COMTX = ch;				 //COMTX is an 8-bit transmit register.
    while(!(0x020==(COMSTA0 & 0x020)))
    {;}
}


void SPIWrite(unsigned char count, unsigned char *buf)
{
	unsigned	char	ValueToWrite = 0;
  	unsigned	char	i = 0;
	unsigned	char	j = 0;
		
	

	for(i=count;i>0;i--)
 	{
	 	ValueToWrite = *(buf + i - 1);
		for(j=0; j<8; j++)
		{
			SET_SCLK();
			if(0x80 == (ValueToWrite & 0x80))
			{
				SET_SDI();	  //Send one to SDI pin
			}
			else
			{
				CLR_SDI();	  //Send zero to SDI pin
			}
			delay(1);
			CLR_SCLK();
			delay(1);
			ValueToWrite <<= 1;	//Rotate data
		}

	

	}

}


//---------------------------------
//void ReadFromAD2S(unsigned char count,unsigned char *buf)
//---------------------------------
//Function that reads from the AD2S via the SPI port. 
//--------------------------------------------------------------------------------

void SPIRead(unsigned char count, unsigned char *buf)
{
	unsigned	char	i = 0;
	unsigned	char	j = 0;
	unsigned	int  	iTemp = 0;
	unsigned	char  	RotateData = 0;

	


	for(j=count; j>0; j--)
	{
		for(i=0; i<8; i++)
		{
		    SET_SCLK();
			RotateData <<= 1;		//Rotate data
			delay(1);
			iTemp = GP0DAT;			//Read SDO of AD2S
			CLR_SCLK();	
			if(0x00000020 == (iTemp & 0x00000020))
			{
				RotateData |= 1;	
			}
			delay(1);
		
		}
		*(buf + j - 1)= RotateData;	  	
	}


}	 	 
