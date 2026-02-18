#include "krnl.h"

void timer_init(){
    __asm__ ("mtc0 %0, $11" :: "r"(TIMER_COMPARE)); // CP0 Compare
    __asm__ ("nop");
    __asm__ ("mtc0 $zero, $9"); // CP0 Count
    __asm__ ("nop");
	timerctl.count = 0;
	timerctl.timeout = 0;
    return;
}

void settimer(unsigned int timeout, struct FIFO8 *fifo, unsigned char data){
    unsigned int reg_status;
    __asm__ (
        "mfc0 %0, $12"
        : "=r"(reg_status)
    );
    krnl_irq_disable();
    timerctl.timeout = timeout;
    timerctl.fifo = fifo;
    timerctl.data = data;
    __asm__ (
        "mtc0 %0, $12"
        :
        : "r"(reg_status)
    );  // Resume
    return;
}