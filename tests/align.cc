#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define align(d, a) (((d) + (a - 1 ) ) & (~ (a - 1)))

struct test
{
    int a;
    char b;
    long c;
};

int main()
{
    printf("%d\n", align(0, 512));
    printf("%d %d\n", sizeof(test), align(sizeof(test), 15));
    printf("%d %d %d\n", offsetof(test, a), offsetof(test, b), offsetof(test, c));
    typeof(((test*)0)->a) x = 100;
    printf("xxxx %d\n", x);

    test  haha;
    typeof(((test*)0)) y = &haha;
    y->a = 1; y->b = 'c'; y->c = 111;
    printf("%d %c %ld\n", y->a, y->b, y->c);

    test* p_test = (test*)((char*)&y->c - offsetof(test, c));
    printf("%d %c %ld\n", y->a, y->b, y->c);
    
    return 0;
}
