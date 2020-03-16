#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "TIVA_TIMER.h"



void open_the_lock() {
    volatile unsigned long delay;
    int i = 0;
    GPIOB->DATA = 0X80;
    while (1) {
        for (i = 0; i < 2; i++) {
            GPIOF->DATA = 0x08;
            Delay_ms(1000);
            GPIOF->DATA = 0x00;
            Delay_ms(1000);
        }
    }
}
void close_the_lock() {
    volatile unsigned long delay;
    int i = 0;
    GPIOB->DATA = 0X00;
    while (1) {
        for (i = 0; i < 2; i++) {
            GPIOF->DATA = 0x02;
            Delay_ms(1000);
            GPIOF->DATA = 0x00;
            Delay_ms(1000);
        }
    }
}
