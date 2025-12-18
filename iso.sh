#!/bin/sh
set -e

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp build/sandero isodir/boot/sandero
cp build/user/vga_test/vga_test isodir/boot/vga_test
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "sandero" {
	multiboot2 /boot/sandero
	module2 /boot/vga_test
}
EOF
grub-mkrescue -o sandero.iso isodir
