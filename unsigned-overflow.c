/*
  regehr_overflow.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  
*/


#include <stdio.h>
#include <limits.h>


// Do an addition in a separate function so the compiler does not
// detect the overflow
unsigned plus_one(unsigned n)
{
    return n + 1;
}


unsigned will_overflow(unsigned a)
{
    return (a+1) < a;
}


int main(void)
{
    printf("will_overflow(UINT_MAX): %u\n", will_overflow(UINT_MAX));
    printf("UINT_MAX + 1: %u\n", plus_one(UINT_MAX));
    printf("UINT_MAX + 1 == 0: %d\n", plus_one(UINT_MAX) == 0);

    return 0;
}
