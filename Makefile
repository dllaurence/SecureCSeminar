# Minimal makefile for Secure C/C++ training seminar.
#
# Copyright Dustin Laurence, 2016.  This file may be used and/or
# redistributed for any purpose in any form.


######################################################################
# Targets
#
######################################################################


.PHONY: default
default: all

# signed-overflow demo
SIGNED_OVERFLOW = \
      signed-overflow-gcc-O0 \
      signed-overflow-gcc-O1 \
      signed-overflow-gcc-O2 \
      signed-overflow-clang-O0 \
      signed-overflow-clang-O1 \
      signed-overflow-clang-O2 \
      signed-overflow-gcc-O0.s \
      signed-overflow-gcc-O1.s \
      signed-overflow-gcc-O2.s \
      signed-overflow-clang-O0.s \
      signed-overflow-clang-O1.s \
      signed-overflow-clang-O2.s
.PHONY: signed-overflow
signed-overflow: $(SIGNED_OVERFLOW)

# unsigned-overflow demo
UNSIGNED_OVERFLOW = \
      unsigned-overflow-gcc-O0 \
      unsigned-overflow-gcc-O1 \
      unsigned-overflow-gcc-O2 \
      unsigned-overflow-clang-O0 \
      unsigned-overflow-clang-O1 \
      unsigned-overflow-clang-O2
.PHONY: unsigned-overflow
unsigned-overflow: $(UNSIGNED_OVERFLOW)

# unpredictable demo
UNPREDICTABLE = \
      unpredictable-ub-gcc-O0 \
      unpredictable-ub-gcc-O1 \
      unpredictable-ub-gcc-O2 \
      unpredictable-ub-clang-O0 \
      unpredictable-ub-clang-O1 \
      unpredictable-ub-clang-O2 \
      predictable-db-gcc-O0 \
      predictable-db-gcc-O1 \
      predictable-db-gcc-O2 \
      predictable-db-clang-O0 \
      predictable-db-clang-O1 \
      predictable-db-clang-O2
.PHONY: unpredictable
unpredictable: $(UNPREDICTABLE)

# -ftrapv demo
.PHONY: ftrapv
FTRAPV = \
         signed-overflow-gcc-ftrapv-O0 \
         signed-overflow-gcc-ftrapv-O1 \
         signed-overflow-gcc-ftrapv-O2 \
         signed-overflow-clang-ftrapv-O0 \
         signed-overflow-clang-ftrapv-O1 \
         signed-overflow-clang-ftrapv-O2 \
         unpredictable-ub-gcc-ftrapv-O0 \
         unpredictable-ub-gcc-ftrapv-O1 \
         unpredictable-ub-gcc-ftrapv-O2 \
         unpredictable-ub-clang-ftrapv-O0 \
         unpredictable-ub-clang-ftrapv-O1 \
         unpredictable-ub-clang-ftrapv-O2
ftrapv: $(FTRAPV)

# -fsanitize=undefined demo
.PHONY: sanitize-undefined
SANITIZE_UNDEFINED = \
         signed-overflow-clang-sanitize-undefined-O0 \
         signed-overflow-clang-sanitize-undefined-O1 \
         signed-overflow-clang-sanitize-undefined-O2 \
         unpredictable-ub-clang-sanitize-undefined-O0 \
         unpredictable-ub-clang-sanitize-undefined-O1 \
         unpredictable-ub-clang-sanitize-undefined-O2
sanitize-undefined: $(SANITIZE_UNDEFINED)

# -fwrapv demo
.PHONY: fwrapv
FWRAPV = \
         signed-overflow-gcc-fwrapv-O0 \
         signed-overflow-gcc-fwrapv-O1 \
         signed-overflow-gcc-fwrapv-O2 \
         signed-overflow-clang-fwrapv-O0 \
         signed-overflow-clang-fwrapv-O1 \
         signed-overflow-clang-fwrapv-O2 \
         unpredictable-ub-gcc-fwrapv-O0 \
         unpredictable-ub-gcc-fwrapv-O1 \
         unpredictable-ub-gcc-fwrapv-O2 \
         unpredictable-ub-clang-fwrapv-O0 \
         unpredictable-ub-clang-fwrapv-O1 \
         unpredictable-ub-clang-fwrapv-O2
fwrapv: $(FWRAPV)

EXCEPTION = exception-leak exception-try exception-auto
.PHONY: exception
exception: $(EXCEPTION)

ALL = $(SIGNED_OVERFLOW) $(UNSIGNED_OVERFLOW) $(UNPREDICTABLE) \
      $(FTRAPV) $(SANITIZE_UNDEFINED) $(FWRAPV) $(EXCEPTION)
.PHONY: all
all: $(ALL)


######################################################################
# Source Locations
#
######################################################################


SRC_DIRS = ./src
VPATH = $(SRC_DIRS)


######################################################################
# Build Variables
#
######################################################################


# Actually only used for the exception demo
CXXFLAGS = -O2


######################################################################
# Rules
#
######################################################################


# Rules to compile assembly files with various compilers and flags.
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

# Test -ftrapv
%-gcc-ftrapv-O0 : %.c
	gcc -O0 -ftrapv $< -o $@

%-gcc-ftrapv-O1 : %.c
	gcc -O1 -ftrapv $< -o $@

%-gcc-ftrapv-O2 : %.c
	gcc -O2 -ftrapv $< -o $@

%-clang-ftrapv-O0 : %.c
	clang -O0 -ftrapv $< -o $@

%-clang-ftrapv-O1 : %.c
	clang -O1 -ftrapv $< -o $@

%-clang-ftrapv-O2 : %.c
	clang -O2 -ftrapv $< -o $@

# Test -fsanitize=undefined
%-clang-sanitize-undefined-O0 : %.c
	clang -O0 -fsanitize=undefined $< -o $@

%-clang-sanitize-undefined-O1 : %.c
	clang -O1 -fsanitize=undefined $< -o $@

%-clang-sanitize-undefined-O2 : %.c
	clang -O2 -fsanitize=undefined $< -o $@

# Test -fwrapv
%-gcc-fwrapv-O0 : %.c
	gcc -O0 -fwrapv $< -o $@

%-gcc-fwrapv-O1 : %.c
	gcc -O1 -fwrapv $< -o $@

%-gcc-fwrapv-O2 : %.c
	gcc -O2 -fwrapv $< -o $@

%-clang-fwrapv-O0 : %.c
	clang -O0 -fwrapv $< -o $@

%-clang-fwrapv-O1 : %.c
	clang -O1 -fwrapv $< -o $@

%-clang-fwrapv-O2 : %.c
	clang -O2 -fwrapv $< -o $@

######################################################################
# Convenience Targets
#
######################################################################


.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(ALL)


.PHONY: spotless
spotless: clean
	rm -rf *~
	rm -rf $(SRC_DIRS)/*~
