


#ifndef EEPROM_H_
#define EEPROM_H_
/*******************************************
				INCLUDES
********************************************/
#include "../../MCAL/twi/twi.h"
#include "../lcd/LCD.h"
#define EEPROM_ADD1		0x00
#include <util/delay.h>
//#define F_CPU   1000000u
/*********************************************
				PROTOTYPES
**********************************************/
void EEPROM_Write (uint8_t *data, uint8_t* _addres);
void EEPROM_Read (uint8_t *data) ;
void EEPROM_Read_String(uint8_t * a_STR);
void EEPROM_Write_WithSize (uint8_t *data, uint8_t *_address,uint8_t LV_Length);
void EEPROM_Read_String_With_size(uint8_t * a_STR, uint8_t a_Length);
#endif /* EEPROM_H_ */