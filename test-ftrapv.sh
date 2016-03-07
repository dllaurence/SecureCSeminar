#!/bin/sh
#
# test-ftrapv.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the ftrapv demo

echo
echo
echo "Test of -ftrapv on signed-overflow.c"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./signed-overflow-gcc-ftrapv-O0`   "   " \
     `./signed-overflow-gcc-ftrapv-O1`   "   " `./signed-overflow-gcc-ftrapv-O2`

echo " Clang   " `./signed-overflow-clang-ftrapv-O0` "   " \
     `./signed-overflow-clang-ftrapv-O1` "   " `./signed-overflow-clang-ftrapv-O2`
echo
echo

echo
echo
echo "Test of -ftrapv on unpredictable-ub.c"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./unpredictable-ub-gcc-ftrapv-O0`   "   " \
     `./unpredictable-ub-gcc-ftrapv-O1`   "   " `./unpredictable-ub-gcc-ftrapv-O2`

echo " Clang   " `./unpredictable-ub-clang-ftrapv-O0` "   " \
     `./unpredictable-ub-clang-ftrapv-O1` "   " `./unpredictable-ub-clang-ftrapv-O2`
echo
echo
