/*
 * spi.h
 *
 * Created: 5/2/2023 2:15:38 PM
 *  Author: acer
 */ 


#ifndef SPI_H_
#define SPI_H_
//Includes
#include "../../Service/STD_TYPES.h"
#include "../MEMORYMAP.h"
#include "../DIO/DIO.h"
// Functions prototypes
void SPI_master_init(void);
void SPI_slave_init(void);
void SPI_transmit_char(char data);
uint8_t SPI_recieve_Char(void);
void SPI_transmit_string(char * string);





#endif /* SPI_H_ */