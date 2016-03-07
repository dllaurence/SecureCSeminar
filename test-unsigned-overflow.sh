#!/bin/sh
#
# test-unsigned-overflow.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the unsigned-overflow demo

echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./unsigned-overflow-gcc-O0`   "   " \
     `./unsigned-overflow-gcc-O1`   "   " `./unsigned-overflow-gcc-O2`

echo " Clang   " `./unsigned-overflow-clang-O0` "   " \
     `./unsigned-overflow-clang-O1` "   " `./unsigned-overflow-clang-O2`
echo
