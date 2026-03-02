#include "krnl.h"

void counter_init(){
    unsigned int i;
    struct TIMER *t;
    __asm__ ("mtc0 %0, $11" :: "r"(TIMER_COMPARE)); // CP0 Compare
    __asm__ ("nop");
    __asm__ ("mtc0 $zero, $9"); // CP0 Count
    __asm__ ("nop");
	timerctl.count = 0;
    for(i = 0; i < MAX_TIMER; i++){
        timerctl.timers0[i].flags = 0; // Not in use
    }
    t = timer_alloc();
    t->timeout = 0xffffffff;
    t->flags = TIMER_FLAGS_USING;
    t->next = 0;
    timerctl.t0 = t;
    timerctl.next = 0xffffffff;
    return;
}

struct TIMER *timer_alloc(){
    unsigned int i;
    for(i = 0; i < MAX_TIMER; i++){
        if(timerctl.timers0[i].flags == 0){
            timerctl.timers0[i].flags = TIMER_FLAGS_ALLOC;
            return &timerctl.timers0[i];
        }
    }
    return 0; // Not found
}

void timer_free(struct TIMER *timer){
    timer->flags = 0;
    return;
}

void timer_init(struct TIMER *timer, struct FIFO32 *fifo, unsigned char data){
    timer->fifo = fifo;
    timer->data = data;
    return;
}

void timer_settime(struct TIMER *timer, unsigned int timeout){
    unsigned int stat;//, i, j;
    struct TIMER *t, *s;
    timer->timeout = timeout + timerctl.count;
    timer->flags = TIMER_FLAGS_USING;
    __asm__ (
        "mfc0 %0, $12"
        : "=r"(stat)
    );
    __asm__ ("nop");
    __asm__ (
        "mtc0 %0, $12"
        :
        : "r"(stat & 0xFFFFFFFE)
    );
    t = timerctl.t0;
    if(timer->timeout <= t->timeout){
        timerctl.t0 = timer;
        timer->next = t;
        timerctl.next = timer->timeout;
        goto resume;
    }
    for(;;){
        s = t;
        t = t->next;
        if(timer->timeout <= t->timeout){
            s->next = timer;
            timer->next = t;
resume:
            __asm__ (
                "mtc0 %0, $12"
                :
                : "r"(stat)
            );
            return;
        }
    }
}