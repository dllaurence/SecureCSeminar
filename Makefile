# Minimal makefile for Secure C/C++ training seminar.
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.


CFLAGS=-O3 -Wall -Werror


ALL = exercise1

.PHONY: all
all: $(ALL)

exercise1: exercise1.o records.o
exercise1.o: records.h
records.o: records.h


.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(ALL)


.PHONY: spotless
spotless: clean
	rm -rf *~
