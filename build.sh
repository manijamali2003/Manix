#!/bin/bash
# In the name of God, the Compassionate, the Merciful
# Manix (c) 2021 Mani Jamali; Freedom at all

nasm -f elf32 boot.asm -o boot.o
gcc  -m32  -c  kernel.c  -o  kernel.o  --freestanding
ld -m  elf_i386  -T  link.ld  -o stor/boot/Manix  boot.o  kernel.o
grub-mkrescue  -o  Manix.iso  stor/
qemu-system-i386  -cdrom  Manix.iso
rm boot.o kernel.o