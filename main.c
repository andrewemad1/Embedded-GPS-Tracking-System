#include "stdio.h"
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include <string.h>
#include <Math.h>
#include "lcd.h"
#include <stdbool.h>


char distancat[100];
int j;
int a;

const int R = 6371; //Radius of earth in (km)
const double PI=3.14159265358979323846;
double lat1,lat2;
double lon1,lon2;
double	lati1;
double long1 ;
double findis=0;  //Global Variable holding the total distance taken

int Gpsdata;
unsigned int finished =0;
unsigned int pos_cnt=0;
unsigned int lat_cnt=0;
unsigned int log_cnt=0;
unsigned int f    =0;
unsigned int commaa=0; //Counting the number of commas to parse the char array
char lat[20];          //char array latitude
char lg[20];           //char array longitude

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
char UART_receivechar ()
{
//Check if FIFO not empty to receive data from UART
while ((UART2_FR_R&	0x10) !=0);
return (char) UART2_DR_R;
}
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
void func1(float x){

if(x>=100)  GPIO_PORTF_DATA_R|=0x02 ;
else   GPIO_PORTF_DATA_R &=~0x02;
}

void PortEB_Init(){
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
	PORTFinit();
  PortEB_Init();
   LCD_init();
  	LCD_displayString("Andrew");
  	while(1){
   /*
if((GPIO_PORTF_DATA_R&0x11)==0x10){    // blue light
	GPIO_PORTF_DATA_R=0x04;
	}
	else if((GPIO_PORTF_DATA_R&0x11)==0x01){ // green light
	GPIO_PORTF_DATA_R=0x08;
	}
	else if((GPIO_PORTF_DATA_R&0x11)==0x00){ // Red light
	GPIO_PORTF_DATA_R=0x02;
	}
	else GPIO_PORTF_DATA_R=0;      // No light
*/
func1(200);

  	}




}
