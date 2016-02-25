/*
  example1.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

*/


#include "records.h"


// Assignment: How should we modify/re-write my_code() for security?
// Somewhere buried in our code, we need to manipulate some records.
void my_code(void)
{
    PersonalRecord *record = malloc(sizeof(PersonalRecord));

    retrieve_record(record);
    do_stuff_to_record(record);

    free(record);
}


int main(void)
{
    // Nothing to see here, just a driver to make my_code() do some work
    my_code();

    return 0;
}
