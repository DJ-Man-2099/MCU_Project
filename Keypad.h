#include "stdint.h"
#include "tm4c123gh6pm.h"

// the following definitions are references to specific bits in GPIO ports


#define r0  *((volatile uint32_t *)0x40005020) 		//pb3
#define r1  *((volatile uint32_t *)0x40005040)		//pb4
#define r2  *((volatile uint32_t *)0x40004010)		//pa2
#define r3  *((volatile uint32_t *)0x40004020)		//pa3
#define c0  *((volatile uint32_t *)0x40004040)		//pa4
#define c1  *((volatile uint32_t *)0x40004080) 		//pa5
#define c2  *((volatile uint32_t *)0x40004100) 		//pa6
#define c3  *((volatile uint32_t *)0x40004200)		//pa7

void porTA_init()
{
	// port A
	GPIO_PORTA_LOCK_R =0X4C4F434B; //IMP TO BE AFTER RCGCGPIO
	/*DONT OPENE LOCK FOR PORT C USED FOR DEBUG AND MAY CAUSE DAMAGE TO
	THE TIVA*/
	GPIO_PORTA_CR_R = 0xFF; 	// use all pins for port A
	GPIO_PORTA_AFSEL_R = 0;		// no alternative functions
	GPIO_PORTA_PCTL_R = 0; 		// control portA
	GPIO_PORTA_AMSEL_R = 0; 	// no analog needed
	GPIO_PORTA_DIR_R = 0X0C;	// FOR INPUT  0 AND 1 FOR OUTPUT  ->10.3 InitializationandConfiguration
	GPIO_PORTA_DEN_R = 0XFF;	// digital pins 1 FOR DIGITAL
	GPIO_PORTA_PUR_R = 0X00;	// pull down  for all pins 
}

void porTB_init()
{
	// port B
	GPIO_PORTB_LOCK_R =0X4C4F434B; //IMP TO BE AFTER RCGCGPIO
	/*DONT OPENE LOCK FOR PORT C USED FOR DEBUG AND MAY CAUSE DAMAGE 
	TO THE TIVA*/
	GPIO_PORTB_CR_R =0xFF; 			// use all pins for port B
	GPIO_PORTB_AFSEL_R |=0x03;	// alternative functions at PB0 & PB1
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xffffff00)+0x00000011; 			//control portB
	GPIO_PORTB_AMSEL_R=0; 			// no analog needed
	GPIO_PORTB_DIR_R |=0X18;		// FOR INPUT  0 AND 1 FOR OUTPUT  ->10.3 InitializationandConfiguration
	GPIO_PORTB_DEN_R =0XFF;			// digital pins 1 FOR DIGITAL
	GPIO_PORTB_PUR_R = 0X00;		// pull down for all pins 
}

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