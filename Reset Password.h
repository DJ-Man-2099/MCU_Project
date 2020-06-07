#include <stdint.h>
#include "tm4c123gh6.h"
#include "TIVA_TIMER.h"

void reset_password(){
;}



void five_Seconds_Delay(void)
{
	Delay_ms(5000);// produce a delay of five seconds
}


void switch1_enable(){   
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R |= 0x11;	
	GPIO_PORTF_DIR_R &= ~(0x11);//set pf4 as input
    GPIO_PORTF_DEN_R |= 0x11;       
    GPIO_PORTF_PUR_R |= 0x11; //pull up for pf4
}




void reset_password_using_timer(){
	
}
