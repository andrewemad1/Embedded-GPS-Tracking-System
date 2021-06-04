#include "stdint.h"
#include <Math.h>

#include "tm4c123gh6pm.h"
const int R = 6371; //Radius of earth in (km)
const double PI=3.14159265358979323846;
double totalDis = 0; //Global Variable holding the total distance taken

double deg2rad(double deg){
  return (deg * PI / 180);
}

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


int func1(float x){

if(x>=100)   return 1;
else return 0;	


}





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




/*void PortB_Init(){
	// Initializing Clock and wait until get stablized
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R & 0x02) == 0);
	
	// Initializing Port B pins
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0x1F;
	GPIO_PORTB_AMSEL_R &= ~0x1F;
	GPIO_PORTB_PCTL_R |= 0x11;
	GPIO_PORTB_DIR_R |= 0x1E;
	GPIO_PORTB_DIR_R &= ~0x01;
	GPIO_PORTB_AFSEL_R |= 0x03;
	GPIO_PORTB_DEN_R |= 0x1F;
}*/
// sha8al kol al clock lkolo

/*void LCDPortB_Init(){
	// Initializing Clock and wait until get stablized
	SYSCTL_RCGCGPIO_R |= 0x02;
	
	// Initializing Port D pins
	GPIO_PORTB_AMSEL_R &= ~0xFF;
	GPIO_PORTB_PCTL_R = 0x00000000; 
	GPIO_PORTB_DIR_R|= 0xFF;
	GPIO_PORTB_AFSEL_R =0;
	GPIO_PORTB_DEN_R |= 0xFF;
}*/

int main(){
  PORTFinit();
	
	while(1)
		{
	if((GPIO_PORTF_DATA_R&0x11)==0x10){    //nawar blue 
	GPIO_PORTF_DATA_R=0x04;
	}
	else if((GPIO_PORTF_DATA_R&0x11)==0x01){ //nawar green
	GPIO_PORTF_DATA_R=0x08;
	}
	else if((GPIO_PORTF_DATA_R&0x11)==0x00){ //nawar red 
	GPIO_PORTF_DATA_R=0x02;
	}
	else GPIO_PORTF_DATA_R=0;      // matnwarsh
 
	
	}
}