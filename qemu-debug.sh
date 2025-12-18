#!/bin/sh
set -e
. ./iso.sh

qemu-system-i386 -m 144 -serial file:sandero.serial -cdrom sandero.iso -s -S -daemonize
