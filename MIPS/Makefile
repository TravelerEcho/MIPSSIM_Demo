#Copyright 2025 TravelerEcho
A_OBJS	= loader.o except_asm.o asmapi.o
C_OBJS	= main.o serial.o except.o fifo8.o memman.o timer.o
C_ASM	= main.s serial.s except.s fifo8.s memman.s timer.s
MAKE	= make
GCC		= mipsel-linux-gnu-gcc
AS		= mipsel-linux-gnu-as
LD		= mipsel-linux-gnu-ld
OBJCOPY = mipsel-linux-gnu-objcopy
OBJDUMP = mipsel-linux-gnu-objdump
QEMU	= qemu-system-mipsel
LFLAGS	= -mips32 -EL -T linker.ld
AFLAGS	= -mips32 -EL -msoft-float
CFLAGS	= -fno-pic -mips32 -mno-abicalls -S -EL -Wall -ffreestanding
OFLAGS	= -O binary
QFLAGS	= -machine mipssim -cpu 4Kc -m 16M -nographic

default :
	$(MAKE) bin

boot.bin : boot.elf Makefile
	$(OBJCOPY) $(OFLAGS) boot.elf boot.bin

boot.elf : $(A_OBJS) $(C_OBJS) linker.ld Makefile
	$(LD) $(LFLAGS) -o boot.elf $(A_OBJS) $(C_OBJS)

main.s : main.c Makefile
	$(GCC) $(CFLAGS) -o main.s main.c

except.s : except.c Makefile
	$(GCC) $(CFLAGS) -o except.s except.c

fifo8.s : fifo8.c Makefile
	$(GCC) $(CFLAGS) -o fifo8.s fifo8.c

serial.s : serial.c Makefile
	$(GCC) $(CFLAGS) -o serial.s serial.c

memman.s : memman.c Makefile
	$(GCC) $(CFLAGS) -o memman.s memman.c

timer.s : timer.c Makefile
	$(GCC) $(CFLAGS) -o timer.s timer.c

%.o : %.s Makefile
	$(AS) $(AFLAGS) -o $*.o $*.s

bin :
	$(MAKE) boot.bin

run :
	$(MAKE) bin
	$(QEMU) $(QFLAGS) -bios boot.bin

dump :
	$(OBJDUMP) -d boot.elf

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.bin
	rm -f $(C_ASM)