
#include "application/app.h"
#include <util/delay.h>
#define F_CPU   8000000u
uint8_t ad=0x00,ad2=0x10,str1[20]={0},ad3=0b1010000,ad4=0b1010001;
int main(void)
{
	
	// Programming mode
	DIO_INITPIN(pinb0,OUTPUT);
	DIO_WRITEPIN(pinb0,HIGH);
	LCD_INIT();
	USART_init();
	I2C_init(I2C_PRESCALER_16);
	//******************************************************************************************************
	
	
	// PAN RECIEVE AND SEND
	unsigned char arr_pan[16]={0};
	USART_Transmit_string ("Please Enter Card PAN:");
	char *pan =  USART_receive_string(arr_pan);
	USART_transmit('\n');
	for (int i=0;i<16;i++)
	{
		pan[i]=pan[i]-'30';
	}
	EEPROM_Write_WithSize(pan,&ad,16); //---------------------------
   _delay_ms(100);
	//*********************************************************************************************************
	// PIN RECIEVE AND SEND
	uint8_t pinRecieved='0';
	char *pin;
	while (pinRecieved=='0')
	{
	// PIN RECIEVE 
	unsigned char arr_pin[7]={0};
	unsigned char arr_npin[7]={0};
	USART_Transmit_string ("Please Enter New PIN:");
	pin =  USART_receive_string(arr_pin);
	//**************************************************
	// CONFIRM PIN RECIEVE
	USART_Transmit_string ("Please Confirm New PIN:");
	char *new_pin = USART_receive_string(arr_npin);
   //***********************************************
   // CHECK PIN CONDITION
	if (arr_pin[4] == 0 && arr_pin[3]!= 0) 
	{
	 pinRecieved='1';
	 	 for (int y=0;y<4;y++)
	 	 {
		 	 if (arr_pin[y]<48 || arr_pin[y]>57) 
			  {
				  USART_transmit('\n');  
				  pinRecieved='0'; 
			  }
			 
	 	 }
	}
	//**************************************************************
	// CHECK PIN CONFIRMATION
		uint8_t npin = *(new_pin);
		uint8_t pin_in = *(pin);
		int c=0;
		for (c=0;c<4;c++)
		{
			if ((*(new_pin+c)) != (*(pin+c)) ) 
			{ 
				pinRecieved='0';
			}
		}
		if (pinRecieved=='0') USART_Transmit_string ("Wrong PIN "); 	 
	}
	USART_Transmit_string (" finished ");

		for (int i=0;i<4;i++)
		{
			pin[i]=pin[i]-'30';
		}
		EEPROM_Write_WithSize(pin,&ad2,4);// Need No size init // SEND D0 at further input // write PAN to EEPROM
		_delay_ms(100);

// user mode
_delay_ms(500);
DIO_INITPIN(pinc0,OUTPUT);
DIO_INITPIN(pinc1,OUTPUT);
	DIO_WRITEPIN(pinc0,LOW);
		DIO_WRITEPIN(pinc1,LOW);
	I2C_init(I2C_PRESCALER_16);
//USART_init();
//SPI_master_init();
//********************************************

EEPROM_Read_String(str1);	
//USART_Transmit_string(str1);
//SPI_transmit_string(str1);

//*******************************************	*/		
}
	
	/*	
	LCD_INIT();
	
	I2C_init(I2C_PRESCALER_1);
	
	TIMER_0_init(NORMAL_MODE);
	uint8_t STR_Term[16]={1,2,3,4,5,6,7,8,9,9,8,7,6,5,2,2},STR_REad[4]={1,2,3,4},ad=0x00,ad2=0x10,flag=0,str1[21]={0},str2[16]={0},ad3=0b1010000,ad4=0b1010001;
	
	if (flag==0)
	{
	EEPROM_Write_WithSize(STR_Term,&ad,16);
		_delay_ms(100);
		EEPROM_Write_WithSize(STR_REad,&ad2,4);

	}

			//EEPROM_Read_String(str1);

    while (1) 
    {
    }
}

*/