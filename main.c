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
//parsing UART data (GPS)
void Receive_GPS_Data(){
    while(finished==0){
        Gpsdata = UART_receivechar();
        f = 1;
       if( Gpsdata=='$' && pos_cnt == 0)   // finding GPRMC header
         pos_cnt=1;
       if( Gpsdata=='G' && pos_cnt == 1)
         pos_cnt=2;
       if( Gpsdata=='P' && pos_cnt == 2)
         pos_cnt=3;
       if( Gpsdata=='R' && pos_cnt == 3)
         pos_cnt=4;
       if( Gpsdata=='M' && pos_cnt == 4)
         pos_cnt=5;
       if( Gpsdata=='C' && pos_cnt==5 )
         pos_cnt=6;
       if(pos_cnt==6 &&  Gpsdata ==','){   // count commas in message
         commaa++;
         f=0;
       }

       if(commaa==3 && f==1){
        lat[lat_cnt++] =  Gpsdata;         // latitude
        f=0;
       }

       if(commaa==5 && f==1){
         lg[log_cnt++] =  Gpsdata;         // Longitude
         f=0;
       }

       if( Gpsdata == '*' && commaa >= 5){
				 lat[lat_cnt] ='\0';             // end of GPRMC message
         lg[log_cnt]  = '\0';
         commaa = 0;                      // end of GPRMC message
         lat_cnt = 0;
         log_cnt = 0;
         f     = 0;
         finished  = 1;

      }
    }
			finished = 0;
   pos_cnt = 0;
}
void UART_Init(void) {
    SYSCTL_RCGCUART_R |= 0x0004; //enable uart4 and Port D
    SYSCTL_RCGCGPIO_R |= 0x0008;
    UART2_CTL_R &= ~0x0001; //diable uart uartctl
    //in uart0 use it as alternate function afsel
    //pctl of uart

    UART2_IBRD_R = 104;    //or 104 
    UART2_FBRD_R = 11;   //baudrate
    UART2_LCRH_R = 0x0070;      //uartlcrh: data lengh 8bit bit5,bit6 ==1 --one stop bit bit3 ==0 -- no parity bit1,bit2 ==0 --enable fifo bit4 ==1
    UART2_CTL_R |= 0x0001;         //enable uartctl

    GPIO_PORTD_AFSEL_R |= 0xC0;
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
    GPIO_PORTD_DEN_R |= 0xC0;      //digital enable
    GPIO_PORTD_AMSEL_R &= ~0XC0;       //analog

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
