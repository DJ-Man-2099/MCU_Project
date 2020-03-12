#ifndef MrLCD
#define MrLCD

#include "TM4C123GH6PM.h"
#include <stdlib.h>
#include "TIVA_TIMER.h"

#define Data_1 GPIOD->DATA
#define Data_1_Dir GPIOD->DIR
#define Data_2 GPIOE->DATA
#define Data_2_Dir GPIOE->DIR

#define Control GPIOE->DATA
#define Control_Dir GPIOE->DIR
#define R_W 4
#define RS 5
#define EN 3

void Send_CMD(uint8_t C){
	
	Data_1 =(((C)&0x0F)|(((C)<<2)&0xC0));
	Data_2 =(((C)>>5)&0x06);
	Control &=~(1<<RS);
	Control |=(1<<EN);
	Delay_ms(10);
	Control &=~(1<<EN);
	Delay_ms(10);
}

void Setup(void){
	SYSCTL->RCGCGPIO |=(0x18);
	while((SYSCTL->PRGPIO & (0x18))==0);
	GPIOD->LOCK |=(0x4C4F434B);
	GPIOD->CR |=(0xCF);
	GPIOD->AMSEL=0;
	GPIOD->AFSEL=0;
	GPIOD->PCTL=0;
	GPIOE->LOCK |=(0x4C4F434B);
	GPIOE->CR |=(0x3E);
	GPIOE->AMSEL=0;
	GPIOE->AFSEL=0;
	GPIOE->PCTL=0;
	Control_Dir=0xFF;
	Data_1_Dir=0xFF;
	Data_2_Dir|=0x1E;
	GPIOD->DEN=0xFF;
	GPIOE->DEN=0xFF;
	Control&=~(1<<R_W);
	//////////////////////////////////
	Delay_ms(10);
	//////////////////////////////////
	Control&=~(1<<RS);
	//////////////////////////////////
	Delay_ms(10);
	//////////////////////////////////
	Data_1=(0xC0);
	Control|=(1<<EN);
	Delay_ms(10);
	Control&=~(1<<EN);
	//////////////////////////////////
	Delay_ms(10);
	//////////////////////////////////
	Data_1=(0xC0);
	Control|=(1<<EN);
	Delay_ms(10);
	Control&=~(1<<EN);
	//////////////////////////////////
	Delay_ms(10);
	//////////////////////////////////
	Data_1=(0xC0);
	Control|=(1<<EN);
	Delay_ms(10);
	Control&=~(1<<EN);
	//////////////////////////////////
	Delay_ms(10);
	//////////////////////////////////
	Data_1=(0x80);
	Control|=(1<<EN);
	Delay_ms(10);
	Control&=~(1<<EN);
	//////////////////////////////////
	Delay_ms(10);
	//////////////////////////////////
	
	Send_CMD(0x38);
	Send_CMD(0x06);
	Send_CMD(0x0c);
}

void Set_Cursor(uint8_t x,uint8_t y){
	if(y==1)
	{
		Send_CMD(0x80+(x-1));
	}
	else
	{
		Send_CMD(0xc0+(x-1));
	}
	Delay_us(100);
}

void Send_Char(uint8_t c){
	Data_1 =(((c)&0x0F)|(((c)<<2)&0xC0));
	Data_2 =(((c)>>5)&0x06);
	Control|=1<<RS;
	Control|=1<<EN;
	Delay_us(10);
	Control&=~(1<<EN);
	Delay_ms(100);
}
void Send_Char_Pos(uint8_t c ,uint8_t x ,uint8_t y){
	Set_Cursor(x,y);
	Data_1 =(((c)&0x0F)|(((c)<<2)&0xC0));
	Data_2 =(((c)>>5)&0x06);
	Control|=1<<RS;
	Control|=1<<EN;
	Delay_us(10);
	Control&=~(1<<EN);
	Delay_ms(100);
}
void Send_String(char *string){
	while(*string>0)
	{
		Send_Char(*string++);
	}
}
void Send_String_Pos(char *string ,uint8_t x ,uint8_t y){
	Set_Cursor(x,y);
	while(*string>0)
	{
		Send_Char(*string++);
	}
}

	
void Clear(){
	Send_CMD(0x01);
    Delay_ms(10);
}
#endif
