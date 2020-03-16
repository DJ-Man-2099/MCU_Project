#include <stdint.h>
#include "C:/Users/Administrator\Downloads/tm4c123gh6pm.h"
#include "tm4c123gh6pm.h"


void reset_password(){
;}

void SYSTICK_init(uint32_t delay)
{
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R=delay-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R|=0x5;
	while((NVIC_ST_CTRL_R&0x00010000)==0) {
        ;                          /* wait for COUNT flag to be 1 (wait for bit 16 to be set)*/
    }
}



void five_Seconds_Delay(void)
{
	SYSTICK_init(479999999);// produce a delay of five seconds
}


void switch1_enable(){
    SYSCTL_RCGC2_R |= 0x20;   
    GPIO_PORTF_DIR_R = 0x08; //set pf4 as input                            
    GPIO_PORTF_DEN_R = 0x18;         
    GPIO_PORTF_PUR_R = 0x10; //pull up for pf4
}




void reset_password_using_timer(){
			switch1_enable();
	while( (GPIO_PORTF_DATA_R & (1<<4) ) == 1) //while pf4 ==1 
			{
				five_Seconds_Delay();
				if( (GPIO_PORTF_DATA_R & (1<<4) ) == 1)
				{
					reset_password();
				}
			}
}



int main()
{
	
}