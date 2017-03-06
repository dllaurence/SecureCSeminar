#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


enum {
    e_size = 1000
};


int main()
{
    printf("Running buffer overflow loop tests...\n");

    int32_t *buf = calloc(e_size, sizeof(int32_t));
    if (!buf) {
        fprintf(stderr, "Out of memory!\n");
        return 1;
    }

    // A correct loop over an array
    for (unsigned i=0;i<e_size;i++) {
        buf[i] = 42;
    }

    // Also correct
    const unsigned last = e_size - 1;
    for (unsigned i=0;i<=last;i++) {
        buf[i] = 17;
    }

    // Off by one buffer overflow
    for (unsigned i=0;i<=e_size;i++) {
        buf[i] = 11;
    }

    free(buf);
    buf = NULL;
    
    printf("Buffer overflow loop tests complete\n");

    return 0;
}
