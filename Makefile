# Minimal makefile for Secure C/C++ training seminar.
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.


ALL = exercise1 \
      unsigned-overflow-gcc-O1 unsigned-overflow-gcc-O2 \
      unsigned-overflow-clang-O1 unsigned-overflow-clang-O2 \
      exception-leak exception-try exception-auto
.PHONY: all
all: $(ALL)

# signed-overflow demo
SIGNED_OVERFLOW = \
      signed-overflow-gcc-O0 \
      signed-overflow-gcc-O1 \
      signed-overflow-gcc-O2 \
      signed-overflow-gcc-O0.s \
      signed-overflow-gcc-O1.s \
      signed-overflow-gcc-O2.s \
      signed-overflow-clang-O0 \
      signed-overflow-clang-O1 \
      signed-overflow-clang-O2 \
      signed-overflow-clang-O0.s \
      signed-overflow-clang-O1.s \
      signed-overflow-clang-O2.s \
      unsigned-overflow-gcc-O1 \
      unsigned-overflow-gcc-O2 \
      unsigned-overflow-clang-O1 \
      unsigned-overflow-clang-O2
.PHONY: signed-overflow
signed-overflow: $(SIGNED_OVERFLOW)


######################################################################
# Source Locations
#
######################################################################


SRC_DIRS = ./src
VPATH = $(SRC_DIRS)


######################################################################
# Dependencies
#
######################################################################



exercise1: exercise1.o records.o
exercise1.o: records.h
records.o: records.h


unsigned-overflow-gcc-O1: unsigned-overflow.c
	gcc -O1 $< -o $@


unsigned-overflow-gcc-O2: unsigned-overflow.c
	gcc -O2 $< -o $@


unsigned-overflow-clang-O1: unsigned-overflow.c
	clang -O1 $< -o $@


unsigned-overflow-clang-O2: unsigned-overflow.c
	clang -O2 $< -o $@


exception-leak: exception-leak.cc
	g++ -O2 $< -o $@


exception-try: exception-try.cc
	g++ -O2 $< -o $@


exception-auto: exception-auto.cc
	g++ -O2 $< -o $@


######################################################################
# Rules
#
######################################################################


# Rules to compile assembly files with various compilers and optimization
# levels.
%-gcc-O0.s : %.c
	gcc -O0 -S $< -o $@

%-gcc-O1.s : %.c
	gcc -O1 -S $< -o $@

%-gcc-O2.s : %.c
	gcc -O2 -S $< -o $@

%-clang-O0.s : %.c
	clang -O0 -S $< -o $@

%-clang-O1.s : %.c
	clang -O1 -S $< -o $@

%-clang-O2.s : %.c
	clang -O2 -S $< -o $@


######################################################################
# Convenience Targets
#
######################################################################


.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(ALL) $(SIGNED_OVERFLOW)


.PHONY: spotless
spotless: clean
	rm -rf *~
	rm -rf $(SRC_DIRS)/*~
