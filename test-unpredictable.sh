#!/bin/sh
#
# test-unpredictable.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the unpredictable demo

echo
echo
echo "Test signed overflow for predictable behavior"
echo "Running unpredictable-ub with different compilers and optimizations"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./unpredictable-ub-gcc-O0`   "   " \
     `./unpredictable-ub-gcc-O1`   "   " `./unpredictable-ub-gcc-O2`

echo " Clang   " `./unpredictable-ub-clang-O0` "   " \
     `./unpredictable-ub-clang-O1` "   " `./unpredictable-ub-clang-O2`
echo

echo

echo
echo "Test unsigned overflow for predictable behavior"
echo "Running predictable-db with different compilers and optimizations"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./predictable-db-gcc-O0`   "   " \
     `./predictable-db-gcc-O1`   "   " `./predictable-db-gcc-O2`

echo " Clang   " `./predictable-db-clang-O0` "   " \
     `./predictable-db-clang-O1` "   " `./predictable-db-clang-O2`
echo
echo
