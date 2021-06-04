int main(){
  PORTFinit();
	LED_init();
	LEDPortD_Init();
	while(1){
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
	LED_command (1) ;
  LED_command (0x80) ;
  LED_data('A');
	}
}