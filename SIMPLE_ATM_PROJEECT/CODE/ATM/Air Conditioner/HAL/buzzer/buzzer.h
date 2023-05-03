/*
 * buzzer.h
 *
 * Created: 4/26/2023 8:26:30 AM
 *  Author: Nada
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

// Includes
#include "../../MCAL/dio/DIO.h"

// Functions prototypes
/************************************************buzzer_init**********************************************************************************/
/* Description:
Function used to initialize the buzzer connected pin as output
*********************************************************************************************************************************************/
void buzzer_init(void);
/************************************************buzzer_On**********************************************************************************/
/* Description:
Function used to put high voltage in buzzer pin
*******************************************************************************************************************************************/
void buzzer_On(void);
/************************************************buzzer_Off*******************************************************************************/
/* Description:
Function used to put low voltage in buzzer pin
******************************************************************************************************************************************/
void buzzer_Off(void);




#endif /* BUZZER_H_ */