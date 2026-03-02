//Copyright 2026 TravelerEcho
#include "krnl.h"
void except_handler_others(unsigned int reg_status, unsigned int reg_cause, unsigned int reg_epc){
    unsigned int interrupt_held = (reg_cause & 0xFF00) >> 8;
    switch((reg_cause & 0x7C) >> 2){
        case 0:{
            if((interrupt_held & (1 << 4)) != 0){ // Interrupt 4
                unsigned char dat = serial_get_char();
                fifo32_put(&fifo, SERIAL_DATA0 + dat);
            }
            if((interrupt_held & (1 << 7)) != 0){ // Interrupt 7
                unsigned int compare;
                struct TIMER *timer;
                __asm__ (
                    "mfc0 %0, $11"
                    : "=r"(compare)
                );
                compare += TIMER_COMPARE;
                __asm__ (
                    "mtc0 %0, $11\n\t"
                    "nop"
                    :
                    : "r"(compare)
                );
                timerctl.count++;
                if(timerctl.next > timerctl.count){
                    break;
                }
                timer = timerctl.t0;
                for(;;){
                    if(timer->timeout > timerctl.count){
                        break;
                    }
                    timer->flags = TIMER_FLAGS_ALLOC;
                    fifo32_put(timer->fifo, timer->data);
                    timer = timer->next;
                }
                timerctl.t0 = timer;
                timerctl.next = timerctl.t0->timeout;
            }
            break;
        }
        default:{
            while(1);
        }
    }
    return;
}
