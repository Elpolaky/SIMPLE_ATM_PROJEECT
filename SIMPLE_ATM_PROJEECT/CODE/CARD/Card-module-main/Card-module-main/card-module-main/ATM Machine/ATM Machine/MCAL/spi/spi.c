/*
 * spi.h
 *
 * Created: 5/2/2023 2:15:50 PM
 *  Author: Nada
 */ 

//Includes
#include "spi.h"
// Functions deceleration

void SPI_master_init(void)
{
    
		// mosi 5----miso6---------sck 7-----ss 4
		// configured (MOSI,SS',SCK) pins as output

		DIO_INITPIN(pinb4,OUTPUT);
		DIO_INITPIN(pinb5,OUTPUT);
		DIO_INITPIN(pinb7,OUTPUT);
		DIO_INITPIN(pinb4,OUTPUT);
		
		// configured MISO pin as input

		DIO_INITPIN(pinb6,INFREE);
		
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<6)|(1<<4)|(1<<0);
	
}
void SPI_slave_init(void)
{ 
	  DDRB &= (~(1<<6)) ;    // B6 are configured as input (MISO)
	  SPCR=0x43;            //SPI is Enable , MSB is transmitted first,  Slave SPI ,SCK is low when idle,Sample in Leading Edge, FOSC/128.
	  SPSR=0x00;            //Flag is reset , and FOSC/128 is used .
}
void SPI_transmit_char(char data)
{
/* Start transmission */
SPDR = data;
/* Wait for transmission complete */
while(!(SPSR & (1<<7)))
;
}
uint8_t SPI_recieve_char(void)
{
	// Wait for reception complete
	while(!(SPSR & (1<<7)));
	// Return data register 
	return SPDR;
}

	void SPI_transmit_string(char * string)
	{
		
		uint8_t i =0 ;
		while(string[i]!=0)
		{ SPI_transmit_char((string[i]-'30')); i++;}
	}

/*
void SPI_transmit_string( data)
{
	 char i=0;
	 for(i=0;i<10;i++)
	 { SPI_SendChar(i);
		 _delay_ms(1000);
}
uint8_t SPI_recieve_string(void)
{
	while( (SPSR&&(1<<7))==0 ) ;   // While Transmission not completed wait untill it's complete
	return SPDR;                 //Return the received data found in Datareister .
}

int main (void)
{  
	}
	
	
}
*/
