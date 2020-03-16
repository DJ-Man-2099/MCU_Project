#include "TM4C123GH6PM.h"
#include "TIVA_TIMER.h"
#include "TIVA_LCD.h"
#include "Lock.h"
int main(){
	Setup();
	Clear();
	Start_Timer();
	while(1){
		Send_String("Hello World");
		if(Pass_is_Correct()){
			open_the_lock();
			Delay_ms(5000);
			close_the_lock();
		}
	}
}