#!/bin/sh

LIB_DIR="/usr/local/lib/"
INCLUDE_DIR="/usr/local/include/"
LIB_SOURCE="build/lib/libzkzsf.a"
INCLUDE_SOURCE="build/include/zsf"

sh make-lib.sh

mv -ni $LIB_SOURCE "$LIB_DIR"
cp -Rf $INCLUDE_SOURCE "$INCLUDE_DIR"

rm -rf $INCLUDE_SOURCE
