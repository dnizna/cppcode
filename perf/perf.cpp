#include <stdio.h>
#include <stdlib.h>


void a()
{
  int x = 0;
  for(int i = 0; i < 100000; ++i)
  x += i;
}

void b()
{
  int x = 0;
  for(int i = 0; i < 100; ++i)
  x += i;
}
 
int main()
{
  a();
  b();

  return 0;
}
