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
