#include "TM4C123GH6PM.h"
#include "TIVA_TIMER.h"
#include "TIVA_LCD.h"
int main(){
	Setup();
	Clear();
	Start_Timer();
	while(1){
		Send_String("Hello World");
	}
}