#include "app.h"

void CARD_PROGRAMMING_MODE(void)
{
	//Entering Pan
	uint8_t LV_PANSTR[16]={0};
	LCD_GoTo(1,0);
	LCD_Write_String("PLESE ENTER");
	LCD_GoTo(2,0);
	LCD_Write_String("CARD PAN:-");
	
	//Virtual Takes Data and Saves It in String
	
	
	
	//Entering PIN
	//uint8_t LV_PINSTR_1[4]={0},LV_PINSTR_1[4]={0};
	LCD_GoTo(1,0);
	LCD_Write_String("PLESE ENTER");
	LCD_GoTo(2,0);
	LCD_Write_String("NEW PIN:-");
	
	
	//Virtual Takes Data and Saves It in String
	
	
	
	//CHECKS VALIDATY OF DATA

	

}

void CARD_USER_MODE(void)
{
	
	
	
}