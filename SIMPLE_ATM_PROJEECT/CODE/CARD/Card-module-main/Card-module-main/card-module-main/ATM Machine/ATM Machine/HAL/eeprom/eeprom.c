#include "eeprom.h"
#include <util/delay.h>

/**DESCRIPTION:-
 This Function is used To Write Data On External EEPROM Using I2C Communication*/
void EEPROM_Write (uint8_t *data, uint8_t *_address){
	
	uint8_t LV_Index_I=0,LV_Length=0;
	while (data[LV_Length])											//Calculate The Length Of the Data String
	{
		LV_Length++;
	}

	if(I2C_start()==EVENT_OK){										//Send a Starting Bit and Wait For ACK
		if(I2C_addressEvent(0xA0,WRITE)==AD_W_SENT_ACK_OK){			//Send an Initializer "0b1010" Specified In the Data Sheet  and an Event Type "R/W" and Wait For ACK
			if(I2C_sendData(_address)== DATA_SENT_ACK_OK){			//Send an Address In the EEPROM  To Start Writing In It
					for (LV_Index_I=0;LV_Index_I<LV_Length;){		//To Send The Whole Data String 
				if(I2C_sendData(&data[LV_Index_I])== DATA_SENT_ACK_OK){		//Send Data Byte By Byte and Wait For AcK Each Time 
						
					  LV_Index_I++;
					}
				}
				
			}
		}
	}

	I2C_stop();															//End Of Communication
	
}
/******************************************************************************************************************************************/
/**DESCRIPTION:-
 This Function is used To Read Data On External EEPROM Using I2C Communication*/
void EEPROM_Read ( uint8_t *data) {

	if(I2C_start()==EVENT_OK){															//Send a Starting Bit and Wait For ACK
		if(I2C_addressEvent(0xA0,READ)==AD_R_SENT_ACK_OK){								//Send an Initializer "0b1010" Specified In the Data Sheet  and an Event Type "R/W" and Wait For ACK
			if(I2C_receiveData(data,NACK)== DATA_RECIEVE_NACK_OK){						//Send an Address In the EEPROM  To Start Reading From It		
				I2C_stop();
			}
			
		}
	}
	
}
/**********************************************************************************************************************************************/
void EEPROM_Read_String(uint8_t * a_STR){
	uint8_t LV_Index_I=0;

	for (LV_Index_I=0;LV_Index_I<16;LV_Index_I++)
	{
		EEPROM_Read(&a_STR[LV_Index_I]);
		
	LCD_Write_Number((uint32_t)a_STR[LV_Index_I]);
	}
	LV_Index_I=16;
	

LCD_GoTo(2,0);
if (LV_Index_I>=15)
{

	for (LV_Index_I=16;LV_Index_I<20;LV_Index_I++)
	{
		EEPROM_Read(&a_STR[LV_Index_I]);
		LCD_Write_Number((uint32_t)a_STR[LV_Index_I]);
	}
}

}

/******************************************/

void EEPROM_Write_WithSize (uint8_t *data, uint8_t *_address,uint8_t LV_Length){
	
	uint8_t LV_Index_I=0;	
	
	if(I2C_start()==EVENT_OK){										//Send a Starting Bit and Wait For ACK
		if(I2C_addressEvent(0xa0,WRITE)==AD_W_SENT_ACK_OK){			//Send an Initializer "0b1010" Specified In the Data Sheet  and an Event Type "R/W" and Wait For ACK
			if(I2C_sendData(_address)== DATA_SENT_ACK_OK){			//Send an Address In the EEPROM  To Start Writing In It
				for (LV_Index_I=0;LV_Index_I<LV_Length;){		//To Send The Whole Data String
					if(I2C_sendData(&data[LV_Index_I])== DATA_SENT_ACK_OK){		//Send Data Byte By Byte and Wait For AcK Each Time
						
						LV_Index_I++;
					}
				}
				
			}
		}
	}
	
	I2C_stop();															//End Of Communication
	
}
