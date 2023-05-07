
#include "application/app.h"
#include <util/delay.h>
#define F_CPU   8000000u
uint8_t ad=0x00,ad2=0x10,str1[16]={0},str2[4]={},ad3=0b1010000,ad4=0b1010001;
int main(void)
{

	SPI_MasterInit(PRESCALER_16);
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
//  	for (int i=0;i<16;i++)
//  	{
//  		pan[i]=pan[i]-'30';
//  	}
	//pan[16]= '\0';
	//EEPROM_Write_WithSize(pan,&ad,16); //---------------------------
  // _delay_ms(100);
  
   
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
/*
		for (int i=0;i<4;i++)
		{
			pin[i]=pin[i]-'30';
		}
	*/	
		EEPROM_Write_WithSize(pan,&ad,16); //--- pan sent to EEPROM	
		_delay_ms(100);
		 //--- pan receive to EEPROM
		 	EEPROM_Read_String_With_size(str1 ,16);
		_delay_ms(100);
	
		EEPROM_Write_WithSize(pin,&ad2,4);// PAN sent to EEPROM
		_delay_ms(100);
	
		EEPROM_Read_String_With_size(str2 ,4);
		
	
	
// user mode
	DIO_WRITEPIN(pinb0,LOW);
	
	// sending 
	uint8_t index = 0;
	DIO_WRITEPIN(SS, LOW);

	while (str1[index] != '\0')
	{
		SPI_SendReceive(str1[index]);
		index++;
		_delay_ms(800);
	}
	SPI_SendReceive('\0');

	DIO_WRITEPIN(SS, HIGH);
	
	
//USART_init();
//SPI_master_init();
//********************************************


//USART_Transmit_string(str1);
//SPI_transmit_string(str1);

//*******************************************	*/	
	
}
	
