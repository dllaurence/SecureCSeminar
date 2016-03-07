#!/bin/sh
#
# test-signed-overflow.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the signed-overflow demo

echo
echo
echo "Test of signed overflow behavior."
echo "Running signed-overflow with different compilers and optimizations"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./signed-overflow-gcc-O0`   "   " \
     `./signed-overflow-gcc-O1`   "   " `./signed-overflow-gcc-O2`

echo " Clang   " `./signed-overflow-clang-O0` "   " \
     `./signed-overflow-clang-O1` "   " `./signed-overflow-clang-O2`
echo
echo
