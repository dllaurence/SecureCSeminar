/*
  regehr_overflow.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  
*/


#include <stdio.h>
#include <limits.h>


// Do an addition in a separate function so the compiler does not
// detect the overflow
int plus_one(int n)
{
    return n + 1;
}


int will_overflow(int a)
{
    return (a+1) < a;
}


int main(void)
{
    printf("will_overflow(INT_MAX): %d\n", will_overflow(INT_MAX));
    printf("INT_MAX + 1: %d\n", plus_one(INT_MAX));
    printf("INT_MAX + 1 == INT_MIN: %d\n", plus_one(INT_MAX) == INT_MIN);

    return 0;
}
