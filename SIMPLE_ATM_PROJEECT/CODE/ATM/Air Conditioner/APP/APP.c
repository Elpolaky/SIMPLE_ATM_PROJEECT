#include "APP.h"

/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
*****************************************************************************************************************************/

/***********************************************************************************************************************
                                   FUNCTION IMPLMENTATION
****************************************************************************************************************************/
void app_Init(void){
	
	KEYPAD_init();
	LCD_INIT();
	buzzer_init();
	TIMER_0_init(NORMAL_MODE);
	DIO_INITPIN(BUTTON_PIN,INPLUP);
	DIO_INITPIN(pinb3,OUTPUT);
	
	
}

uint8_t Button_1(){
	TIMER_2_INT();
	
	
} 

void app_Start(void){
	uint8_t bell[8] = {0x04, 0x0E ,0x0E ,0x0E ,0x1f ,0x00 ,0x04 ,0x00};  //HEX Array for the Bell Shape//
	uint8_t pan [] = "898937615436851123";
	float dailyMax = 5000.0; 
	float transAmount = 1000.0; 
	uint8_t approved_flag = 0 ;
	LCD_Clear();
	
	if(isValidAccount(pan) == SERVER_OK){
		
		if(isBlockedAccount()==SERVER_OK){
		
			if (transAmount<= dailyMax)
			{
				if(isAmountAvailable(&transAmount) == SERVER_OK){
					
					approved_flag = 1 ;
					
				}else{
					
					LCD_GoTo(1,3);
					LCD_Write_String("INSUFFICIENT ");
					LCD_GoTo(2,5);
					LCD_Write_String(" FUND !!");
					TIMER_0_DELAY_MS(DELAY_VALUE);
					
				}// end of balance check
				
			}else{
				
					LCD_GoTo(1,4);
					LCD_Write_String("MAX LIMIT");
					LCD_GoTo(2,1);
					LCD_Write_String(" IS EXCEEDED ");
					LCD_GoTo(2,15);
					LCD_Create_Charecter(bell,2);
					TIMER_0_DELAY_MS(DELAY_VALUE);
					
			}// end of amount check
		
		}else{
			
			buzzer_On();
			LCD_GoTo(1,4);
			LCD_Write_String("THIS IS");
			LCD_GoTo(2,1);
			LCD_Write_String("A STOLEN CARD !!");
			
			TIMER_0_DELAY_MS(DELAY_VALUE);
		} //  end of blocked check
		
	}
	else{
		buzzer_On();
		LCD_GoTo(1,4);
		LCD_Write_String("THIS IS");
		LCD_GoTo(2,1);
		LCD_Write_String("A FRAUD CARD !!");
		TIMER_0_DELAY_MS(DELAY_VALUE);
		
	}
	
	
	if ( approved_flag)
	{
		buzzer_Off();
		p_account->balance -= transAmount ;
		LCD_Clear();
		LCD_GoTo(1,4);
		LCD_Write_String("APPROVED ");
		LCD_GoTo(2,3);
		LCD_Write_String("TRANSACTION ");
		TIMER_0_DELAY_MS(DELAY_VALUE);
		
		LCD_Clear();
		LCD_GoTo(1,4);
		LCD_Write_String("REMAINING");
		LCD_GoTo(2,0);
		LCD_Write_String("BALANCE :");
		LCD_Write_Number(p_account->balance);
		LCD_Write_String(".00");
		TIMER_0_DELAY_MS(DELAY_VALUE);

		
		LCD_Clear();
		LCD_GoTo(1,4);
		LCD_Write_String("EJECTING ");
		LCD_GoTo(2,6);
		LCD_Write_String("CARD ");
		TIMER_0_DELAY_MS(DELAY_VALUE);

	}
	
	
}



/************************************************************************************************************/





