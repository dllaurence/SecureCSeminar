#!/bin/sh
#
# test-fwrapv.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the fwrapv demo

echo
echo
echo "Test of -fwrapv on signed-overflow.c"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./signed-overflow-gcc-fwrapv-O0`   "   " \
     `./signed-overflow-gcc-fwrapv-O1`   "   " `./signed-overflow-gcc-fwrapv-O2`

echo " Clang   " `./signed-overflow-clang-fwrapv-O0` "   " \
     `./signed-overflow-clang-fwrapv-O1` "   " `./signed-overflow-clang-fwrapv-O2`
echo
echo

echo
echo
echo "Test of -fwrapv on unpredictable-ub.c"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./unpredictable-ub-gcc-fwrapv-O0`   "   " \
     `./unpredictable-ub-gcc-fwrapv-O1`   "   " `./unpredictable-ub-gcc-fwrapv-O2`

echo " Clang   " `./unpredictable-ub-clang-fwrapv-O0` "   " \
     `./unpredictable-ub-clang-fwrapv-O1` "   " `./unpredictable-ub-clang-fwrapv-O2`
echo
echo
