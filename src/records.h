#ifndef RECORDS_H
#define RECORDS_H

/*
  records.h

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  Just stubs standing in for real code.
*/


#include <stdlib.h>
#include <inttypes.h>


// Data that the module operates on
typedef struct {
    uint64_t id;

    char first[21];
    char last[31];

    char social[10];

    // ... lots of other fields

} PersonalRecord;


// These stubs represent functions from some other module we may or may not
// have the source for.  The details are unknown for purposes of this exercise,
// but presumably something clever and amazing.

    // Not what the code would do, but we have to keep the compiler happy by
    // returning something.

int do_stuff_to_record(PersonalRecord *record);

int retrieve_record(PersonalRecord *record);


#endif
