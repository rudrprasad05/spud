all: os-image.bin

boot.o: boot.asm
	nasm -f bin boot.asm -o boot.o

kernel.o: kernel.c
	x86_64-elf-gcc -ffreestanding -c kernel.c -o kernel.o

kernel.bin: kernel.o linker.ld
	x86_64-elf-ld -o kernel.elf -T linker.ld kernel.o
	x86_64-elf-objcopy -O binary kernel.elf kernel.bin

os-image.bin: boot.o kernel.bin
	cat boot.o kernel.bin > os-image.bin

run: os-image.bin
	qemu-system-x86_64 -drive format=raw,file=os-image.bin

clean:
	rm -f *.o *.bin *.elf
