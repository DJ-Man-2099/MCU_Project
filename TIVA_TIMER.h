#ifndef T_imer
#define T_imer

#include "TM4C123GH6PM.h"
#include <stdlib.h>

void Start_Timer(void){
	SysTick->CTRL=0;
	SysTick->LOAD=0x00FFFFFF;
	SysTick->VAL=0;
	SysTick->CTRL=0x00000005;
}
void Count(uint32_t delay){
	SysTick->LOAD=delay-1;
	while((SysTick->CTRL & 1<<SysTick_CTRL_COUNTFLAG_Pos)==0);
}
void Delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
		Count(60000);
	}
}
void Delay_us(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
		Count(60);
	}
}

#endif
