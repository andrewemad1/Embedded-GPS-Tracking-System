#include "lcd.h"
#include <stdlib.h>
#include "tm4c123gh6pm.h"

//Added delay function for the LCD
void _delay_ms(int n)
{
	int x , y;
	for(x = 0; x < n ; x++){
		for(y = 0 ; y < 3180;y++)
		{}

	}
}

void _delay_us(int n)
{
 int i,j;
 for(i=0;i<n;i++){
	for(j=0;j<3;j++){}

	}
}




void LCD_init(void)
{
	/* Configure the control pins(E,RS,RW) as output pins */
	_delay_ms(20);
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	_delay_us(50);
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	_delay_us(50);
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
	_delay_ms(2);
}
void LCD_displayString(const char* Str)
{
	uint8 i = 0;
	while (Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
		_delay_ms(1);
	}
}
//LCD commands
//clear display



void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}
