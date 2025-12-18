#!/bin/sh
export PREFIX="$PWD/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

if ! [ -f binutils-2.45.tar.xz ]; then
	wget https://ftp.gnu.org/gnu/binutils/binutils-2.45.tar.xz
fi
if ! [ -f gcc-15.2.0.tar.xz ]; then
	wget https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.xz
fi

tar xf binutils-2.45.tar.xz
tar xf gcc-15.2.0.tar.xz

mkdir build-binutils
cd build-binutils
../binutils-2.45/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
../gcc-15.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3
cd ..

rm -r binutils-2.45 gcc-15.2.0
