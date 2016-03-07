/*
  unpredictable-ub.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  Example of optimization creating different results from equivalent
  code when the code has undefined behavior.
*/


#include <stdio.h>
#include <limits.h>


// What does this function do?
int will_overflow(int a)
{
    return (a+1) == INT_MIN;
}


// Do an addition in a separate function so the compiler does not
// detect the overflow
int plus_one(int n)
{
    return n + 1;
}


int main(void)
{
    int prediction = will_overflow(INT_MAX);
    int actual = plus_one(INT_MAX) == INT_MIN;
    if (prediction == actual) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}
