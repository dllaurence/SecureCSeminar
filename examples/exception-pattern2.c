/*
  exception-pattern2.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  "C Exception Pattern" example using Exception interface pattern 2
*/


float foo(int *err)
{
    int err = 0;
    float result = <some default value>;

    // Acquire resources
    Stuff *stuff = get_stuff(err);
    if (*err) {
        return result;
    }

    MoreStuff *more_stuff = get_more_stuff(err);
    if (*err) {
        goto free_stuff;
    }

    // Do work

    // ...

    // On error need to ensure all resources are released
    if (*err) {
        goto finalize;
    }

    // ...

    // We don't set until completely finished so the function either
    // succeeds or does nothing at all.

    // Commit result
    result = <final result>;

    // Release resources
finalize:
    free(more_stuff);
    more_stuff = NULL;

    // Partial tear-down
free_stuff:
    free(stuff);
    stuff = NULL;

    return result;
}
