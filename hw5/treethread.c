#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

void* thread (void *vargp){
  int count = *((int*)vargp);
  if (count == 1){
    printf("Hello, world\n");
    return NULL;
  }
  count--;
  pthread_t tids[2];
  pthread_create(&tids[0], NULL, thread, &count);
  pthread_create(&tids[1], NULL, thread, &count);
  
  pthread_join(tids[0], NULL);
  pthread_join(tids[1], NULL);
  
  printf("Hello, world\n");
  return NULL;
}

int main(int argc, char* argv[]){
  if (argc != 2){
    printf("Wrong number of arguments!");
    exit(1);
  }

  int max = atoi(argv[1]);
  if (max <= 0){
    printf("The command line argument should be positive!");
    exit(1);
  }
  else if (max == 1){
    printf("Hello, world\n");
    return 0;
  }

  max--;
  pthread_t tids[2];
  pthread_create(&tids[0], NULL, thread, &max);
  pthread_create(&tids[1], NULL, thread, &max);

  pthread_join(tids[0], NULL);
  pthread_join(tids[1], NULL);

  printf("Hello, world\n");
  return 0;
}
