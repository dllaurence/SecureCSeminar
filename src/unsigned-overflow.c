/*
  unsigned-overflow.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  Example of optimization leaving unsigned overflow alone.
*/


#include <stdio.h>
#include <limits.h>


// What does this function do?
int will_overflow(unsigned n)
{
    return (n+1) < n;
}


// Do an addition in a separate function so the compiler does not
// detect the overflow
int plus_one(unsigned n)
{
    return n + 1;
}


int main(void)
{
    int prediction = will_overflow(UINT_MAX);
    int actual = plus_one(UINT_MAX) == 0;
    if (prediction == actual) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}
