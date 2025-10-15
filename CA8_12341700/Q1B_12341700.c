//Add one more thread "threadC" which should execute only after threadB has done its execution. Note You will need one more sem_t variable

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semB, semC;


void* threadA(void* arg) 
{
  printf("Hello from A\n");
  sem_post(&semB);
  return NULL;
}
void* threadB(void* arg) 
{
  sem_wait(&semB);
  printf("Hello from B\n");
  sem_post(&semC);
  return NULL;
}
void* threadC(void* arg) 
{
  sem_wait(&semC);
  printf("Hello from C\n");
  return NULL;
}
int main()
{
  pthread_t tA, tB, tC;
  
  sem_init(&semB, 0, 0);
  sem_init(&semC, 0, 0);
  
  pthread_create(&tA, NULL, threadA, NULL);
  pthread_create(&tB, NULL, threadB, NULL);
  pthread_create(&tC, NULL, threadC, NULL);

  pthread_join(tA, NULL);
  pthread_join(tB, NULL);
  pthread_join(tC, NULL);
  
  sem_destroy(&semB);
  sem_destroy(&semC);
  return 0;
}
