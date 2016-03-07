#!/bin/sh
#
# test-sanitize-undefined.sh
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.
#
# Test driver for the sanitize-undefined demo

echo
echo
echo "Test of -fsanitize=undefined on signed-overflow.c"
echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " Clang   " `./signed-overflow-clang-sanitize-undefined-O0` "   " \
     `./signed-overflow-clang-sanitize-undefined-O1` "   " `./signed-overflow-clang-sanitize-undefined-O2`
echo
echo

echo
echo
echo "Test of -fsanitize=undefined on unpredictable-ub.c"
echo
echo "Compiler    -O0         -O1        -O2"

echo " Clang   " `./unpredictable-ub-clang-sanitize-undefined-O0` "   " \
     `./unpredictable-ub-clang-sanitize-undefined-O1` "   " `./unpredictable-ub-clang-sanitize-undefined-O2`
echo
echo
