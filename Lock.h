#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "TIVA_TIMER.h"



void open_the_lock() {
    GPIOF->DATA = 0X05;
}
void close_the_lock() {
		GPIOF->DATA = 0x02;
}
