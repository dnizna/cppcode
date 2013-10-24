#include <pthread.h>
#include <stdio.h>

pthread_cond_t pct_a, pct_b, pct_c;
pthread_mutex_t pm;
pthread_t pa, pb, pc;

void* run_a(void*)
{
  while(true)
  {
    puts("A");
    pthread_cond_signal(&pct_b);
    pthread_cond_wait(&pct_a, &pm);
  }
}

void* run_b(void*)
{
  while(true)
  {
    pthread_cond_wait(&pct_b, &pm);
    puts("B");
    pthread_cond_signal(&pct_c);
  }
}

void* run_c(void*)
{
  while(true)
  {
    pthread_cond_wait(&pct_c, &pm);
    puts("C");
    pthread_cond_signal(&pct_a);
  }
}


int main()
{
  pthread_cond_init(&pct_a, NULL);
  pthread_cond_init(&pct_b, NULL);
  pthread_cond_init(&pct_c, NULL);
  pthread_create(&pa, NULL, run_a, NULL);
  pthread_create(&pb, NULL, run_b, NULL);
  pthread_create(&pc, NULL, run_c, NULL);

  pthread_join(pa, NULL);
  return 0;
}
