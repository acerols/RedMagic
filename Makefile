CC		= gcc
LD		= ld

ASFLAGS = -c -Iinclude/
CFLAGS 	= -c -Iinclude/ -Wpointer-to-int-cast -fno-stack-protector
LDFLAGS = -n -o
OBJECTS = object/

KERNEL_BIN	= kernel.bin

OBJS	= kernel.o kernel_s.o memory.o section.o kstdlib.o multiboot.o terminal.o

multiboot.o: multiboot.S
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

kernel_s.o: kernel.S
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(OBJECTS)$@

$(KERNEL_BIN): $(OBJS) 
	$(LD) $(LDFLAGS) $(KERNEL_BIN) -T link.ld $(OBJECTS)*.o

os.iso: grub.cfg kernel.bin
	mkdir -p isofiles/boot/grub
	cp grub.cfg isofiles/boot/grub/
	cp kernel.bin isofiles/boot/
	grub-mkrescue -o $@ isofiles/
	$(RM) -r isofiles/

all:
	make os.iso

.PHONY: all
clean:
	$(RM) multiboot.o kernel.o kernel.bin os.iso

run: os.iso	
	qemu-system-x86_64 -drive format=raw,file=$<

debug: os.iso
	qemu-system-x86_64 -nographic -drive format=raw,file=$< -s -S