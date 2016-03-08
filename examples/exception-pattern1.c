// "C Exception Pattern" example using
// Exception interface pattern 1

int foo(float *result)
{
    int err = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (err = get_stuff(&stuff)) ) {
        return err;
    }

    MoreStuff *more_stuff = NULL;
    if ( (err = get_more_stuff(...)) ) {
        goto free_stuff;
    }

    // Do work

    // ...

    // On error need to ensure all resources are released
    if (err) {
        goto finalize;
    }

    // ...

    // We don't set until completely finished so the function either
    // succeeds or does nothing at all.

    // Commit result
    *result = <final result>;

    // Release resources
finalize:
    free(more_stuff);
    more_stuff = NULL;

    // Partial tear-down
free_stuff:
    free(stuff);
    stuff = NULL;

    return err;
}
