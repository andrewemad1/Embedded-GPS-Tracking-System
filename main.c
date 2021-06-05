#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"


void SystemInit(){}
void PORTFinit(){
  volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R|=0x20;
	delay=1;
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R=0x1F;
	GPIO_PORTF_AFSEL_R=0;
	GPIO_PORTF_PCTL_R=0;
	GPIO_PORTF_AMSEL_R=0;
	GPIO_PORTF_DIR_R=0x0E;
	GPIO_PORTF_DEN_R=0x1F;
	GPIO_PORTF_PUR_R=0x11;
}

const int R = 6371; //Radius of the earth in (kilometers)
const double PI=3.14159265358979323846; //Constant PI
double totalDis = 0; //The total distance taken by the global variable



bool FinalDestination(int distance)
{ if (distance>100)
    return true;
    else
    return false;
}

void LED_ON(int distance)
{

if(FinalDestination(distance))

    GPIO_PORTF_DATA_R |= 0x02; //red
else

GPIO_PORTF_DATA_R &=~(0x02); //turns on red LED if distance >100
}
