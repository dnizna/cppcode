#include <stdio.h>
#include <stdlib.h>
#include <easy_client.h>
#include <easy_io.h>

int main()
{
    if(easy_io_create(1))
    {
        fprintf(stderr, "easy_io_create error.\n");
    }
    return 0;
}
