#define COM1 0xBFD003F8
#define FIFO8_FLAGS_OVERRUN 0x0001
#define MEMMAN_FREES 4090
#define MEMMAN_ADDR 0x80010000
#define MEMTOTAL 0x1000000
#define CLOCK_RATE 12000000
#define TIMER_COMPARE CLOCK_RATE/200 // 100ms
extern int serial_init();
extern char serial_is_transmit_empty();
extern char serial_is_received();
extern char serial_get_char();
extern void serial_print_char(char chr);
extern void serial_print_str(char *str);
extern void krnl_irq_enable();
extern void krnl_irq_disable();
struct FIFO8 {
	unsigned char *buf;
	int p, q, size, free, flags;
};
struct FREEINFO {
	unsigned int addr, size;
};
struct MEMMAN {
	int frees, maxfrees, lostsize, losts;
	struct FREEINFO free[MEMMAN_FREES];
};
struct TIMERCTL {
	unsigned int count, timeout;
	struct FIFO8 *fifo;
	unsigned char data;
};
extern void fifo8_init(struct FIFO8 *fifo, int size, unsigned char *buf);
extern int fifo8_put(struct FIFO8 *fifo, unsigned char data);
extern int fifo8_get(struct FIFO8 *fifo);
extern int fifo8_status(struct FIFO8 *fifo);
extern void memman_init(struct MEMMAN *man);
extern unsigned int memman_total(struct MEMMAN *man);
extern unsigned int memman_alloc(struct MEMMAN *man, unsigned int size);
extern int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size);
extern void timer_init();
extern void settimer(unsigned int timeout, struct FIFO8 *fifo, unsigned char data);
extern struct FIFO8 serialfifo;
extern struct TIMERCTL timerctl;
