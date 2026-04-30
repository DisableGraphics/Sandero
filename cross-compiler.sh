#!/bin/sh
export PREFIX="$PWD/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

export BINUTILS_VERSION="2.45"
export GCC_VERSION="15.2.0"

if ! [ -f "binutils-${BINUTILS_VERSION}.tar.xz" ]; then
	wget "https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.xz"
fi
if ! [ -f "gcc-${GCC_VERSION}.tar.xz" ]; then
	wget "https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.xz"
fi

tar xf "binutils-${BINUTILS_VERSION}.tar.xz"
tar xf "gcc-${GCC_VERSION}.tar.xz"

mkdir build-binutils
cd build-binutils
"../binutils-${BINUTILS_VERSION}/configure" --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
"../gcc-${GCC_VERSION}/configure" --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3
cd ..

rm -r "binutils-${BINUTILS_VERSION}" "gcc-${GCC_VERSION}"
