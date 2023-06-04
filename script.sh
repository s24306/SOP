gcc -m32 -ffreestanding -c kernel.c -o kernel.o
ld -melf_i386 -Tlinker.ld -nostdlib --nmagic -o kernel.elf kernel.o
objcopy -O binary kernel.elf kernel.bin
dd if=kernel.bin of=bootloader bs=512 seek=1 conv=notrunc
