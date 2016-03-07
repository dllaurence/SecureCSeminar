#!/bin/sh
#
# test-cub.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the cub demo

echo
echo
echo "Test of -fcatch-undefined-behavior on signed-overflow.c"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " Clang   " `./signed-overflow-clang-cub-O0` "   " \
     `./signed-overflow-clang-cub-O1` "   " `./signed-overflow-clang-cub-O2`
echo
echo

echo
echo
echo "Test of -fcatch-undefined-behavior on unpredictable-ub.c"
echo
echo "Compiler    -O0         -O1        -O2"

echo " Clang   " `./unpredictable-ub-clang-cub-O0` "   " \
     `./unpredictable-ub-clang-cub-O1` "   " `./unpredictable-ub-clang-cub-O2`
echo
echo
