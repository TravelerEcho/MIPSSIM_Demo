#Copyright 2026 TravelerEcho
A_OBJS	= except_asm.o
C_OBJS	= main.o timer.o fifo32.o serial.o except.o memman.o
C_ASM	= main.s timer.s fifo32.s serial.s except.s memman.s
MAKE	= make
GCC		= mipsel-none-elf-gcc
AS		= mipsel-none-elf-as
LD		= mipsel-none-elf-ld
EDIMG	= edimg
OBJCOPY = mipsel-none-elf-objcopy
OBJDUMP = mipsel-none-elf-objdump
QEMU	= qemu-system-mipsel
LFLAGS	= -mips32 -EL
AFLAGS	= -mips32 -EL -msoft-float
CFLAGS	= -mips32 -mno-abicalls -S -EL -Wall -ffreestanding -fno-pic
OFLAGS	= -O binary
QFLAGS	= -machine mipssim -cpu 4Kc -m 16M -nographic

default :
	$(MAKE) img

boot.img : krnl.bin loader.bin Makefile
	$(EDIMG) imgin:fdimg0at.tek \
		wbinimg src:loader.bin len:512 from:0 to:0 \
		copy from:krnl.bin to:@: \
		copy from:Makefile to:@: \
		imgout:boot.img

loader.elf : loader.o loadlink.ld Makefile
	$(LD) $(LFLAGS) -T loadlink.ld -o loader.elf loader.o

loader.bin : loader.elf Makefile
	$(OBJCOPY) $(OFLAGS) -j .text loader.elf loader.bin

krnl.bin : krnl.elf Makefile
	$(OBJCOPY) $(OFLAGS) krnl.elf krnl.bin

krnl.elf : $(A_OBJS) $(C_OBJS) linker.ld Makefile
	$(LD) $(LFLAGS) -T linker.ld -o krnl.elf $(A_OBJS) $(C_OBJS)

main.s : main.c Makefile
	$(GCC) $(CFLAGS) -o main.s main.c

except.s : except.c Makefile
	$(GCC) $(CFLAGS) -o except.s except.c

fifo32.s : fifo32.c Makefile
	$(GCC) $(CFLAGS) -o fifo32.s fifo32.c

serial.s : serial.c Makefile
	$(GCC) $(CFLAGS) -o serial.s serial.c

memman.s : memman.c Makefile
	$(GCC) $(CFLAGS) -o memman.s memman.c

timer.s : timer.c Makefile
	$(GCC) $(CFLAGS) -o timer.s timer.c

%.o : %.s Makefile
	$(AS) $(AFLAGS) -o $*.o $*.s

img :
	$(MAKE) boot.img

run :
	$(MAKE) img
	$(QEMU) $(QFLAGS) -bios boot.img

dump :
	$(OBJDUMP) -d loader.o

clean :
	del *.o
	del *.elf
	del *.bin
	del *.img
	del $(C_ASM)