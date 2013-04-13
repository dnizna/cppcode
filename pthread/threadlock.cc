#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "test.h"

int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);

void pthread_lock()
{
  pthread_t tidA, tidB;

  pthread_create(&tidA, NULL, &doit, NULL);
  pthread_create(&tidB, NULL, &doit, NULL);

  pthread_join(tidA, NULL);
  pthread_join(tidB, NULL);
}

void* doit(void* vptr)
{
  int i, val;
  for(i = 0; i < 100; ++i)
  {
    pthread_mutex_lock(&counter_mutex);
    val = counter;
    printf("%d: %d\n", pthread_self(), val + 1);
    counter = counter + 1;
    pthread_mutex_unlock(&counter_mutex);
  }
}

