//Copyright 2026 TravelerEcho
#define COM1 0xBFD003F8
#define FIFO8_FLAGS_OVERRUN 0x0001
#define MEMMAN_FREES 4090
#define MEMMAN_ADDR 0x80010000
#define MEMTOTAL 16 * 1024 * 1024
#define CLOCK_RATE 12000000
#define MAX_TIMER 500
#define TIMER_COMPARE CLOCK_RATE/200 // 100ms
#define TIMER_FLAGS_ALLOC 1
#define TIMER_FLAGS_USING 2
#define SERIAL_DATA0 2048
#define ADR_DISKIMG 0x80000800
extern unsigned int uint_to_str_safe(unsigned int num, char *str, unsigned int size);
extern void* memset(void* ptr, unsigned char value, unsigned int num);
extern unsigned int strcmp(const char* str1, const char* str2);
extern int serial_init();
extern char serial_is_transmit_empty();
extern char serial_is_received();
extern char serial_get_char();
extern void serial_print_char(char chr);
extern void serial_print_str(char *str);
struct FIFO32 {
	int *buf;
	int p, q, size, free, flags;
};
struct FREEINFO {
	unsigned int addr, size;
};
struct MEMMAN {
	int frees, maxfrees, lostsize, losts;
	struct FREEINFO free[MEMMAN_FREES];
};
struct TIMER {
	struct TIMER *next;
	unsigned int timeout, flags;
	struct FIFO32 *fifo;
	int data;
};
struct TIMERCTL {
	unsigned int count, next;
	struct TIMER *t0;
	struct TIMER timers0[MAX_TIMER];
};
struct FILEINFO {
	unsigned char name[8], ext[3], type;
	char reserved[10];
	unsigned short time, data, clustno;
	unsigned int size;
};
extern void fifo32_init(struct FIFO32 *fifo, int size, int *buf);
extern int fifo32_put(struct FIFO32 *fifo, int data);
extern int fifo32_get(struct FIFO32 *fifo);
extern int fifo32_status(struct FIFO32 *fifo);
extern void memman_init(struct MEMMAN *man);
extern unsigned int memman_total(struct MEMMAN *man);
extern unsigned int memman_alloc(struct MEMMAN *man, unsigned int size);
extern int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size);
extern void counter_init();
extern struct TIMER *timer_alloc();
extern void timer_free(struct TIMER *timer);
extern void timer_init(struct TIMER *timer, struct FIFO32 *fifo, unsigned char data);
extern void timer_settime(struct TIMER *timer, unsigned int timeout);
extern struct TIMERCTL timerctl;
extern struct FIFO32 fifo;