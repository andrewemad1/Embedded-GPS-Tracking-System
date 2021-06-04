#include "stdio.h"
#include <stdlib.h>
#include<string.h>
#include<string.h>
#include <Math.h>

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
const double PI=3.14159265358979323846; //Cont PI
double totalDis = 0; //The total distance taken by the global variable

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
