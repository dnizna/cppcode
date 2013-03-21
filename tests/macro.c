#include <stdio.h>

#define  var_to_string(a)  #a

#define join(a,b,c) a##_##b##_##c

typedef struct
{
    int x;
    int y;
    int z;
} join(x,y,z);

int main()
{ 
    printf("%s\n", var_to_string(a));

    join(x,y,z) test;
    test.x = 100, test.y = 200, test.z = 300;
    printf("%d %d %d\n", test.x, test.y, test.z);

    return 0;
}
