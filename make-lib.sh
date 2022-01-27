#!/bin/sh

CC=gcc
AR=ar
OUT="libzkzsf.a"
LDFLAGS="-I/usr/local/include -L/usr/local/lib -lzkcollection"
SRC="src/"
CFILES="$(find $SRC -name '*.c')"

echo "Compiling\n"
CC -Wall -Wextra -Os -O2 -c $CFILES

echo "Creating Library $OUT\n"
AR -q $OUT *.o
rm *.o

echo "Installing library\n"
rm -rf ./build/lib
mkdir build
mkdir ./build/lib
mv "$OUT" ./build/lib/

sh extract-headers.sh

