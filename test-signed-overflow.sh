#!/bin/sh

echo
echo "Compiler    -O0         -O1        -O2"
echo
echo " GCC     " `./signed-overflow-gcc-O0`   "   " \
     `./signed-overflow-gcc-O1`   "   " `./signed-overflow-gcc-O2`

echo " Clang   " `./signed-overflow-clang-O0` "   " \
     `./signed-overflow-clang-O1` "   " `./signed-overflow-clang-O2`
echo
