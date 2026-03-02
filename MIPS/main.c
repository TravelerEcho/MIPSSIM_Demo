//Copyright 2026 TravelerEcho
#include "krnl.h"
struct FIFO32 fifo;
struct TIMERCTL timerctl;
int main(){
	struct MEMMAN *memman = (struct MEMMAN *) MEMMAN_ADDR;
	struct FILEINFO *finfo = (struct FILEINFO *) (ADR_DISKIMG + 0x002600);
	int fifobuf[128];
	unsigned int stat, cursor_x = 0;
	unsigned char escencode = 0;
	char cmdbuf[256] = { 0 }, s[20];
	memman_init(memman);
	memman_free(memman, 0x80000600, 0x200);
	memman_free(memman, 0x80168800, MEMTOTAL - 0x00168800);
	fifo32_init(&fifo, 32, fifobuf);
	if(serial_init() != 0){
		while(1);
	}
	counter_init();
	__asm__ (
		"mfc0 %0, $12"
		: "=r"(stat)
	);
	stat &= ~0x400006;	// Clear EXL ERL
	stat |= 0x9001; // Allow interrupt 4,7 & Allow interrupts
	__asm__ (
		"mtc0 %0, $12"
		:
		: "r"(stat)
	);
	serial_print_str("[System] System started.\r\n>");
	while(1){
		if(fifo32_status(&fifo) != 0){
			unsigned int i = fifo32_get(&fifo);
			if(SERIAL_DATA0 <= i && i <= 255 + SERIAL_DATA0){ // Serial
				i -= SERIAL_DATA0;
				if(escencode != 0){
					escencode++;
					if(escencode >= 3){
						escencode = 0;
					}
				}else if(i == '\r'){
					serial_print_str("\r\n");
					if(strcmp(cmdbuf, "mem") == 0){
						serial_print_str("total   ");
						memset(s, 0, sizeof(s));
						uint_to_str_safe(MEMTOTAL / (1024 * 1024), s, sizeof(s));
						serial_print_str(s);
						serial_print_str(" MB\r\nfree    ");
						memset(s, 0, sizeof(s));
						uint_to_str_safe(memman_total(memman) / 1024, s, sizeof(s));
						serial_print_str(s);
						serial_print_str(" KB\r\n");

					}else if(strcmp(cmdbuf, "dir") == 0){
						for(unsigned char x = 0; x < 224; x++){
							if(finfo[x].name[0] == 0x00){
								break;
							}
							if(finfo[x].name[0] != 0xe5){
								if((finfo[x].type & 0x18) == 0){
									memset(s, 0, sizeof(s));
									for(unsigned char y = 0; y < 8; y++){
										s[y] = finfo[x].name[y];
									}
									if(finfo[x].ext[0] != 0x20){
										s[8] = '.';
									}else{
										s[8] = ' ';
									}
									s[9] = finfo[x].ext[0];
									s[10] = finfo[x].ext[1];
									s[11] = finfo[x].ext[2];
									s[12] = '\0';
									serial_print_str(s);
									serial_print_str("  ");
									memset(s, 0, sizeof(s));
									uint_to_str_safe(finfo[x].size, s, sizeof(s));
									serial_print_str(s);
									serial_print_str(" Bytes\r\n");
								}
							}
						}
					}else if(cmdbuf[0] != 0){
						serial_print_str("Bad command.\r\n");
					}
					serial_print_str(">");
					memset(cmdbuf, 0, sizeof(cmdbuf));
					cursor_x = 0;
				}else if(i == '\x7f' || i == '\b'){
					if(cursor_x > 0){
						serial_print_str("\b \b");
						cursor_x--;
						cmdbuf[cursor_x] = 0;
					}
				}else if(i == '\x1b' && escencode == 0){
					escencode = 1;
				}else{
					serial_print_char(i);
					cmdbuf[cursor_x] = i;
					cursor_x++;
				}
			}
			__asm__ (
				"mfc0 %0, $12"
				: "=r"(stat)
			);
			stat |= 1;
			__asm__ (
				"mtc0 %0, $12"
				:
				: "r"(stat)
			); // Enable interrupts
		}
	}
}

void* memset(void* ptr, unsigned char value, unsigned int num){
	unsigned char* p= (unsigned char*)ptr;
	for(unsigned int i = 0; i < num; i++){
		p[i] = value;
	}
	return ptr;
}

unsigned int strcmp(const char* str1, const char* str2){
	while(*str1 && (*str1 == *str2)){
		str1++;
		str2++;
	}
	return *(unsigned char*)str1 - *(unsigned char*)str2;
}
unsigned int uint_to_str_safe(unsigned int num, char *str, unsigned int size){
    if (str == 0 || size == 0) {
        return 1;
    }
    if (num == 0) {
        if (size < 2) {
            return 1;
        }
        str[0] = '0';
        str[1] = '\0';
        return 0;
    }
    unsigned int temp = num;
    int digit_count = 0;
    while (temp > 0) {
        digit_count++;
        temp /= 10;
    }
    if (size < (unsigned int)(digit_count + 1)) {
        return 1;
    }
    str[digit_count] = '\0';
    temp = num;
    for (int i = digit_count - 1; i >= 0; i--) {
        str[i] = '0' + (temp % 10);
        temp /= 10;
    }
    return 0;
}
