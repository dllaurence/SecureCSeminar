#include <stdint.h>
#include <stdlib.h>


const unsigned c_size = 1000;

int main()
{
    // Create a "static" buffer that isn't really static
    int32_t static_buf1[c_size] = {0};

    // Demonstrate the run-time existence of const objects
    const unsigned *alias_c_size = &c_size;
    int32_t static_buf2[*alias_c_size] = {0};

    /* Off by one buffer overflow not caught by valgrind! */
    for (i=0;i<=e_size;i++) {
        dynamic_buf[i] = 42;
    }


    return 0;
}
