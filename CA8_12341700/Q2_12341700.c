// Objective: Learn how two threads synchronize at a rendezvous point.

// Problem Statement:
// Thread A prints: A1 (Starting task), A2 (Ending task)
// Thread B prints: B1 (Starting task), B2 (Ending task)
// Synchronization requirements:
// A1 must happen before B2
// B1 must happen before A2
// The order of Al and B1 does not matter
// Use two semaphores: aArrived and bArrived
// Thread A signals aArrived after printing Al and waits on barrived before printing A2
// Thread B signals bArrived after printing B1 and waits on aArrived before printing B2
// WAP to demonstrate this synchronization

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t aArrived, bArrived;
void* threadA(void* arg) 
{
  printf("A1 (Starting task)\n");
  sem_post(&aArrived);
  sem_wait(&bArrived);
  printf("A2 (Ending task)\n");
  return NULL;
}
void* threadB(void* arg) 
{
  printf("B1 (Starting task)\n");
  sem_post(&bArrived);
  sem_wait(&aArrived);
  printf("B2 (Ending task)\n");
  return NULL;
}
int main()
{
  pthread_t tA, tB;
    sem_init(&aArrived, 0, 0);
    sem_init(&bArrived, 0, 0);
    pthread_create(&tA, NULL, threadA, NULL);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    sem_destroy(&aArrived);
    sem_destroy(&bArrived);
    return 0;
}
