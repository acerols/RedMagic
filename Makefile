CC		= riscv64-unknown-elf-gcc
LD		= riscv64-unknown-elf-ld
QEMU = qemu-system-riscv64

ASFLAGS = -march=rv64g -mabi=lp64 -c -Iinclude/ 
CFLAGS 	= -march=rv64g -mabi=lp64 -c -Iinclude/  -O0
CFLAGS += -nostdlib -mcmodel=medany -g
#CFLAGS += -nostartfiles -nodefaultlibs -ffreestanding -fno-common 
#CFLAGS += -Wall -Werror 
LDFLAGS =  -static -nostdlib -Map=kernel.map -o
OBJECTS = objs/

KERNEL_BIN	= kernel.bin

OBJS	= kernel.o boot.o uart.o timervec.o trap.o timer.o lib.o

CPUS := 1

QEMUOPTS = -machine virt -bios none -kernel kernel.bin -m 128M -smp $(CPUS) -nographic -serial mon:stdio

all: $(KERNEL_BIN)

boot.o: boot.s
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

%.o: %.s
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(OBJECTS)$@

$(KERNEL_BIN): $(OBJS) 
	$(LD) $(LDFLAGS) $(KERNEL_BIN) -T link.ld objs/kernel.o objs/uart.o boot.o objs/timervec.o objs/trap.o objs/timer.o objs/lib.o -g
	riscv64-unknown-elf-objdump -d $(KERNEL_BIN) > $(KERNEL_BIN).dump
	
ld:
	$(LD) $(LDFLAGS) $(KERNEL_BIN) -T link.ld objs/kernel.o objs/uart.o boot.o timervec.o objs/trap.o objs/timer.o


.PHONY: all
clean:
	$(RM) kernel.o kernel.bin
	$(RM) $(OBJECTS)*.o

run: 
	$(QEMU) $(QEMUOPTS)

debug: $(KERNEL_BIN)
	sudo $(QEMU) $(QEMUOPTS) -S -gdb tcp::1000
	# open terminal and run gdb-multiarch kernel.bin
	# (gdb) target remote :1000
	# (gdb) b //breakpoint
	# (gdb) c //continue
	# (gdb) x //mem dump