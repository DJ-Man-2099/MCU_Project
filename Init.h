#include "TM4C123GH6PM.h"

void PortA(uint8_t DIR,uint32_t SP,uint32_t P_SP){
		SYSCTL->RCGCGPIO |= 0x01;
		while((SYSCTL->PRGPIO & 0x01) == 0);
    GPIOA->DIR |= DIR;
		GPIOA->LOCK |= 0X4C4F434B;
	  GPIOA->CR |= 0x00;
    GPIOA->AMSEL = 0x00;
		GPIOA->AFSEL = 0x00;
		GPIOA->PCTL = 0x00;
    GPIOA->AFSEL |= SP;
		GPIOA->PCTL |= P_SP;
    GPIOA->DEN |= 0xFF;
}

void PortB(uint8_t DIR,uint32_t SP,uint32_t P_SP){
		SYSCTL->RCGCGPIO |= 0x02;
		while((SYSCTL->PRGPIO & 0x02) == 0);
    GPIOB->DIR |= DIR;		
		GPIOB->LOCK |= 0X4C4F434B;
	  GPIOB->CR |= 0x00;
    GPIOB->AMSEL = 0x00;
    GPIOB->AFSEL = 0x00;
		GPIOB->PCTL = 0x00;
		GPIOB->AFSEL |= SP;
    GPIOB->PCTL |= P_SP;
		GPIOB->DEN |= 0xFF;
}

void PortD(uint8_t DIR,uint32_t SP,uint32_t P_SP){
		SYSCTL->RCGCGPIO |= 0x08;
		while((SYSCTL->PRGPIO & 0x08) == 0);
    GPIOD->DIR |= DIR;
		GPIOD->LOCK |= 0X4C4F434B;
	  GPIOD->CR |= 0x00;
    GPIOD->AMSEL = 0x00;
    GPIOD->AFSEL = 0x00;
		GPIOD->AFSEL |= SP;
		GPIOD->PCTL |= P_SP;
    GPIOD->DEN |= 0xFF;
}

void PortE(uint8_t DIR,uint32_t SP,uint32_t P_SP){
		SYSCTL->RCGCGPIO |= 0x10;
		while((SYSCTL->PRGPIO & 0x10) == 0);
    GPIOE->DIR |= DIR;
		GPIOE->LOCK |= 0X4C4F434B;
	  GPIOE->CR |= 0x00;
    GPIOE->AMSEL = 0x00;
    GPIOE->AFSEL = 0x00;
		GPIOE->PCTL = 0x00;
		GPIOE->AFSEL |= SP;
    GPIOE->PCTL |= P_SP;
		GPIOE->DEN |= 0xFF;
}

void PortF(uint8_t DIR,uint32_t SP,uint32_t P_SP){
		SYSCTL->RCGCGPIO |= 0x20;
		while((SYSCTL->PRGPIO & 0x20) == 0);
    GPIOF->DIR |= DIR;
		GPIOF->LOCK |= 0X4C4F434B;
	  GPIOF->CR |= 0x00;
    GPIOF->AMSEL = 0x00;
    GPIOF->AFSEL = 0x00;
		GPIOF->PCTL = 0x00;
		GPIOF->AFSEL |= SP;
    GPIOF->PCTL |= P_SP;
		GPIOF->DEN |= 0xFF;
}
