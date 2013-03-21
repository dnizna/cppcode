#include <stdio.h>
#include <stdlib.h>
#include <easy_client.h>
#include <easy_io.h>

int main()
{
    if(easy_io_create(1))
    {
        fprintf(stderr, "easy_io_create error.\n");
        return 0;
    }
    easy_io_handler_pt io_handler;
    memset(io_handler, 0, sizeof(io_handler));

    io_handler.decode = echo_decode;

    return 0;
}
