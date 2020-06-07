#include "stdint.h"
#include "TM4C123GH6PM.h"

// the following definitions are references to specific bits in GPIO ports
// where r's are connected to the rows of the keypad, while c's are the columns
///////////////////////////////////////////////////////////////
#define r0  *((volatile uint32_t *)0x40005020) 		//pb3 input to keypad
#define r1  *((volatile uint32_t *)0x40005040)		//pb4 input
#define r2  *((volatile uint32_t *)0x40004010)		//pa2 input
#define r3  *((volatile uint32_t *)0x40004020)		//pa3 input
#define c0  *((volatile uint32_t *)0x40004040)		//pa4 output from keypad
#define c1  *((volatile uint32_t *)0x40004080) 		//pa5 output
#define c2  *((volatile uint32_t *)0x40004100) 		//pa6 output
#define c3  *((volatile uint32_t *)0x40004200)		//pa7 output
/////////////////////////////////////////////////////////////////




// port A initialization	
///////////////////////////////////////////

void porTA_init()
{
	SYSCTL->RCGCGPIO |= 0x01;  // clock for port A and B// 00000011
	while((SYSCTL->PRGPIO & 0x01) == 0);
	GPIOA->LOCK =0X4C4F434B; //IMP TO BE AFTER RCGCGPIO
	/*DONT OPEN LOCK FOR PORT C USED FOR DEBUG AND MAY COUSE DAMAGE 
	THE TIVA*/
	GPIOA->CR =0xfd; // use all pins for port A
	GPIOA->AFSEL =0;	//no alternatives 
	GPIOA->PCTL =0; 	//control portA
	GPIOA->AMSEL=0; 	//no analog needed
	GPIOA->DIR=0X0d;	// FOR INPUT  0 AND 1 FOR OUTPUT  ->10.3 InitializationandConfiguration
	GPIOA->DEN =0XFF;	//digital pins 1 FOR DIGITAL
	GPIOA->PUR = 0X00;//pul up for all pins 
}
///////////////////////////////////////////////


// port B initialization
//////////////////////////////////////////////
void porTB_init()
{
	SYSCTL->RCGCGPIO |= 0x02;  // clock for port A and B// 00000011
	while((SYSCTL->PRGPIO & 0x02) == 0);
	GPIOB->LOCK =0X4C4F434B; //IMP TO BE AFTER RCGCGPIO
	/*DONT OPEN LOCK FOR PORT C USED FOR DEBUG AND MAY COUSE DAMAGE 
	THE TIVA*/
	GPIOB->CR =0xff; // use all pins for port B
	GPIOB->AFSEL =0;	//no alternatives 
	GPIOB->PCTL =0; 	//control portA
	GPIOB->AMSEL=0; 	//no analog needed
	GPIOB->DIR=0Xff;	// FOR INPUT  0 AND 1 FOR OUTPUT  ->10.3 InitializationandConfiguration
	GPIOB->DEN =0XFF;	//digital pins 1 FOR DIGITAL
	GPIOB->PUR = 0X00;//pul up for all pins 
}
///////////////////////////////////////////////

	
// Keypad Code	
// check which keypad row is being pressed after determining the column
////////////////////////////////////////////////////////////////
int check(){
	r0=0x08; r1=0; r2=0; r3=0;		//high voltage on row 0, else is grounded
	if ((c0|c1|c2|c3)!=0)		return 1;
	
	r0=0; r1=0x10; r2=0; r3=0;		// high on row 1
	if ((c0|c1|c2|c3)!=0)		return 2;
	
	
	r0=0; r1=0; r2=0x04; r3=0;		// high on row 2
	if ((c0|c1|c2|c3)!=0)		return 3;
	
	r0=0; r1=0; r2=0; r3=0x08;		// high on row 3
	if ((c0|c1|c2|c3)!=0)		return 4;
	return 0;				// default output in case no button is pressed
}
///////////////////////////////////////////////////////////////////


// return keypad char that's being pressed
///////////////////////////////////////////////////////////////
char getfromkeybad(){
		
		r0=0x08; r1=0x10; r2=0x04; r3=0x08;	//apply high voltage on all rows

		if ((c0|c1|c2|c3)!=0){ 		// check if any button is pressed
			int index;
			if(c0&0x10){		// case 1: column 0
				index=check();	// check which row
				switch (index){
				case 1:return '1';	
				case 2:return '4';	
				case 3:return '7';	
				case 4:return 'm';		// change password
				default: return 'x';	// in case no button is pressed			
				}
			}
			
			else if(c1&0x20){		// case 2: column 1
				index=check();
				switch (index){
				case 1:return '2';
				case 2:return '5';
				case 3:return '8';
				case 4:return '0';
				default: return 'x';
				}
			}
			
			else if(c2&0x40){		// case 3: column 2
				index=check();
				switch (index){
				case 1:return '3';			
				case 2:return '6';		
				case 3:return '9';		
				case 4:return 'c';		// clear entire password
				default: return 'x';
				}
			}
			
			else if(c3&0x80){
				index=check();			// case 4: column 3
				switch (index){	
				case 1:return 't';	// start
				case 2:return 'p';	// stop
				case 3:return 'h';	// clear the last bit
				case 4:return 'e';	// enter password
				default: return 'x';
				}
			}
		}
		return 'x';			// default output if no button is pressed
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

