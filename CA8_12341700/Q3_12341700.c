// Question 3: Thread Synchronization Using Mutex
// Objective:I Understand race conditions and how mutex prevents inconsistent access.
// Task:
// Implement a multithreaded counter upto 1000000 times with 10 threads.
// Part 1: Without mutex (observe race condition)
// Part 2: With mutex (observe consistent count)
// Record results and explain why race conditions occur without mutex.
// WAP to accomplish the above tasks.

#include <stdio.h>
#include <pthread.h>

long counter = 0;
pthread_mutex_t lock;

void* threadFuncNoMutex(void* arg) {
    for (long i = 0; i < 100000; i++) {
        counter++;
    }
    return NULL;
}

void* threadFuncWithMutex(void* arg) {
    for (long i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main() {
    pthread_t threads[10];
    counter = 0;
    for (int i = 0; i < 10; i++)
        pthread_create(&threads[i], NULL, threadFuncNoMutex, NULL);

    for (int i = 0; i < 10; i++)
        pthread_join(threads[i], NULL);

    printf("Final counter value (no mutex): %ld (expected %ld)\n", counter, (long)10 * (long)100000);

    counter = 0;
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 10; i++)
        pthread_create(&threads[i], NULL, threadFuncWithMutex, NULL);

    for (int i = 0; i < 10; i++)
        pthread_join(threads[i], NULL);

    printf("Final counter value (with mutex): %ld (expected %ld)\n", counter, (long)10 * (long)100000);
    pthread_mutex_destroy(&lock);

    return 0;
}