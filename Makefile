CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
LLVMPATH = /opt/homebrew/opt/llvm/bin
CLANGFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72+nosimd

all: clean kernel8.img

boot.o: boot.S
	clang --target=aarch64-elf $(CLANGFLAGS) -c boot.S -o boot.o

%.o: %.c
	clang --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	ld.lld -m aarch64elf -nostdlib boot.o $(OFILES) -T link.ld -o kernel8.elf
	llvm-objcopy-10  -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true

qemu: kernel8.img
	/home/bkmn/dev/qemu-patch-raspberry4/build/qemu-system-aarch64 -M raspi4b -nographic -serial mon:stdio -kernel -m 4G kernel8.elf