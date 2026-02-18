//Copyright 2025 TravelerEcho
#include "krnl.h"
struct FIFO8 serialfifo;
struct FIFO8 timerfifo;
struct TIMERCTL timerctl;
int main(){
	struct MEMMAN *memman = (struct MEMMAN *) MEMMAN_ADDR;
	unsigned char serialbuf[32];
	unsigned char timerbuf[8];
	krnl_irq_disable();
	memman_init(memman);
	memman_free(memman, 0x8000FE00, 0x0200);
	memman_free(memman, 0x80050000, MEMTOTAL - 0x00050000);
	fifo8_init(&serialfifo, 32, serialbuf);
	if(serial_init() != 0){
		while(1);
	}
	serial_print_str("Serial chip initialization completed.\n");
	timer_init();
	fifo8_init(&timerfifo, 8, timerbuf);
	settimer(1000, &timerfifo, 1); // 10 sec
	unsigned int stat;
	__asm__ (
		"mfc0 %0, $12"
		: "=r"(stat)
	);
	stat &= ~0x400006;	// Clear EXL ERL
	stat |= 0x9000; // Allow interrupt 4,7
	__asm__ (
		"mtc0 %0, $12"
		:
		: "r"(stat)
	);
	while(1){
		krnl_irq_enable();
		while(fifo8_status(&serialfifo) + fifo8_status(&timerfifo) == 0);
		if(fifo8_status(&serialfifo) != 0){
			serial_print_char(fifo8_get(&serialfifo));
		} else if(fifo8_status(&timerfifo) != 0){
			unsigned int i = fifo8_get(&timerfifo);
			serial_print_str("[10 sec]\n");
		}
	}
}
