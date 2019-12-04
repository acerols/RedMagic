CC		= gcc
LD		= ld

ASFLAGS = -c -Iinclude/
CFLAGS 	= -c -Iinclude/ -fno-stack-protector
CFLAGS += -nostdlib -nostdinc -fno-builtin -fno-stack-protector 
CFLAGS +=-nostartfiles -nodefaultlibs -ffreestanding -fno-common 
CFLAGS += -Wall -Werror 
LDFLAGS =  -Map=kernel.map -n  -o
OBJECTS = object/

KERNEL_BIN	= kernel.bin

OBJS	= kernel_s.o kstdlib.o main.o  multiboot.o io.o
OS		= os.iso

all: $(OS)

multiboot.o: multiboot.S
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

boot.o: boot.S
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(OBJECTS)$@

kernel_s.o: kernel_s.S
	$(CC) $(ASFLAGS) $< -o $(OBJECTS)$@

$(KERNEL_BIN): $(OBJS) 
	$(LD) $(LDFLAGS) $(KERNEL_BIN) -T link.ld $(OBJECTS)*.o

os.iso: grub.cfg $(KERNEL_BIN)
	mkdir -p isofiles/boot/grub
	cp grub.cfg isofiles/boot/grub/
	cp kernel.bin isofiles/boot/
	grub-mkrescue -o $@ isofiles/
	$(RM) -r isofiles/

.PHONY: all
clean:
	$(RM) multiboot.o kernel.o kernel.bin os.iso
	$(RM) $(OBJECTS)*.o

run: os.iso	
	qemu-system-x86_64 -drive format=raw,file=$<

debug: os.iso
	qemu-system-x86_64 -nographic -drive format=raw,file=$< -s -S