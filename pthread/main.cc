#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int main()
{
    printf("--------> basic usage\n");
    basic_use();

    printf("\n--------> thread local usage\n");
    thread_local_use();

    return 0;
}
