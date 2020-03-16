#include "stdint.h"
#include "tm4c123gh6pm.h"

// Bluetooth Code	
// Init & Get Functions
////////////////////////////////////////////////////////////////
void BTSendChar(char c)
{
	while( (UART1_FR_R & 0x20) != 0); //Wait till FIFO is not full
	UART1_DR_R = c;
}
void BTInit()
{
	SYSCTL_RCGCUART_R |= 0x0002;	//activate UART
	SYSCTL_RCGCGPIO_R |= 0x0002;	//activate Port B
	UART1_CTL_R &= ~0x0001;				//disable UART
	
	UART1_IBRD_R = 104;						// Integer+Fraction = CLK/(16*Desired_BD)
	UART1_FBRD_R = 21;						// = floor(Fraction*64 + 0.5)
	
	UART1_LCRH_R = 0x0070;				// edit this after learning about el BT Module UART details
	UART1_CTL_R = 0x0301;
	
	GPIO_PORTB_AFSEL_R |= 0x03;
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
	GPIO_PORTB_DEN_R |= 0x03;			//Digital I/O on PBI-0
	GPIO_PORTB_AMSEL_R &= ~0x03;	//No Analog on PB1-0
}

char BTGetChar()
{
	if((UART1_FR_R & 0x20) != 0)
		return 'x';
	
	char c;
	c = UART1_DR_R;
	BTSendChar(c);
	return c;
}

void BTSendString(char* str)
{
	while(*str != '\0')
		BTSendChar(*str++);
}
///////////////////////////////////////////////////////////////////
	