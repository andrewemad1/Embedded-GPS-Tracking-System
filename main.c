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


//Function that calculates the total taken distance:

//Function to convert from degree to radian
double deg2rad(double deg){
  return (deg * PI / 180);
}

//Harvesine Formula to calculate the distance between two points
double distance(double lat1, double lon1, double lat2, double lon2){

  double theta1 = deg2rad(lat1);
  double theta2 = deg2rad(lat2);
  double delta1 = deg2rad(lat2 - lat1);
  double delta2 = deg2rad(lon2 - lon1);

  double a = sin(delta1 / 2) * sin(delta1 / 2) + cos(theta1) * cos(theta2) * sin(delta2 / 2) * sin(delta2 / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double d = R * c;

  return totalDis += d;
}


//function that turns on the LED when the distance exceeds 100 meters.
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
void PortDB_Init(){
	// Initializing Clock and wait until get stablized
	SYSCTL_RCGCGPIO_R |= 0x02;
	SYSCTL_RCGCGPIO_R |= 0x10;
		// Initializing Port B  E pins
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_AMSEL_R = 0;
	GPIO_PORTB_AMSEL_R = 0;
	GPIO_PORTE_DIR_R =0x07;
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTE_DEN_R |= 0x07;
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTB_AFSEL_R |= 0x00;
	GPIO_PORTE_AFSEL_R |= 0x00;
	GPIO_PORTB_PCTL_R =0;
	GPIO_PORTE_PCTL_R =0;

}
//LCD TESTING 
int main (){
  PortEB_Init();
   LCD_init();
  	LCD_displayString("Andrew");
  	while(1){


  	}




}
