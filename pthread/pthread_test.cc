#include <pthread.h>
#include <stdio.h>


pthread_cond_t pct;
pthread_mutex_t pmt;
int run_time = 10;
pthread_t c_t;

void* c_run(void*)
{
  int num = run_time;

  while(num--)
  {
    puts("child thread loop 100");

    pthread_cond_signal(&pct);
    pthread_cond_wait(&pct, &pmt);
  }
}


int main()
{
  int ret = 0;

  if(ret = pthread_cond_init(&pct, NULL))
  {
    printf("pthread cond init error. ret=[%d]", ret);
  }
  else if(ret = pthread_create(&c_t, NULL, c_run, NULL))
  {
    printf("ERROR ret=[%d]", ret);
  }

  int num = run_time;
  while(num--)
  {
    pthread_cond_wait(&pct, &pmt);

    puts("main thread loop 40");

    pthread_cond_signal(&pct);
  }

  return 0;
}



