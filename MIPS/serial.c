#include "krnl.h"
int serial_init() {
	*(unsigned char*)(COM1 + 1)=0x00;	// Disable all interrupts
	*(unsigned char*)(COM1 + 3)=0x80; 	// Enable DLAB
	__asm__  ("nop"); 					// Delay
	*(unsigned char*)COM1=0x01;		// 115200 bauds (lo)
	*(unsigned char*)(COM1 + 1)=0x00;	// 115200 bauds (hi)
	*(unsigned char*)(COM1 + 3)=0x03; 	// 8 bits, no parity, one stop bit
	*(unsigned char*)(COM1 + 2)=0xC7;	// Enable FIFO, clear them, with 14-byte threshold
	*(unsigned char*)(COM1 + 4)=0x1E; 	// Set in loopback mode, then test the serial chip
	*(unsigned char*)COM1=0xAE; 		// Test serial chip (send byte 0xAE and check if serial returns same byte)

	if(*(unsigned char*)COM1 != 0xAE){
		return 1;						// Failed
	}

	*(unsigned char*)(COM1 + 4)=0x0F;	// (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	*(unsigned char*)(COM1 + 1)=0x01;	// Enable Received Data Available interrupt
	return 0;							// Succeeded
}

char serial_is_transmit_empty(){
	return *(unsigned char*)(COM1+5) & 0x20;
}

char serial_is_received(){
	return *(unsigned char*)(COM1+5) & 1;
}

char serial_get_char(){
	while(serial_is_received() == 0);
	return *(unsigned char*)COM1;
}

void serial_print_char(char chr){
	while(serial_is_transmit_empty() == 0);
	*(unsigned char*)COM1 = chr;
	return;
}

void serial_print_str(char *str){
	for(; *str != 0; str++){
		serial_print_char(*str);
	}
	return;
}
