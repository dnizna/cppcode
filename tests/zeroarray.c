#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int id;
  int item[0];
} type_t;

int main()
{
    type_t* p = (type_t*)malloc(sizeof(type_t) + 100 * sizeof(int));

    int* item10 = &p->item[0] + 10 * sizeof(int);
    *item10 = 1000;
    printf("%d\n", *item10);

    int i = 0;
    for(i = 0; i < 100; ++i)
      p->item[i] = i;

    printf("%d\n", p->item[9]);
 
  return 0;
}
