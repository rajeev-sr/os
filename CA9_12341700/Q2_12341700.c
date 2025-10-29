#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 100

sem_t empty;  // Counts empty slots in buffer
sem_t full;   // Counts full slots in buffer
pthread_mutex_t mutex;  // Mutex for mutual exclusion
int buffer[BUFFER_SIZE];
int fill_ptr = 0;
int use_ptr = 0;
int item_counter = 0;
int items_produced = 0;  
int items_consumed = 0;  

int produce_item() {
    return item_counter++;
}

void* producer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 100000; i++) {
        int item = produce_item();
        sem_wait(&empty);  // Wait for an empty slot
        pthread_mutex_lock(&mutex);  // Lock before access shared buffer
        buffer[fill_ptr] = item;
        fill_ptr = (fill_ptr + 1) % BUFFER_SIZE;
        items_produced++;  
        printf("Producer %d produced: %d\n", id, item);
        pthread_mutex_unlock(&mutex);  // Unlock after access shared buffer
        sem_post(&full);  // Signal slot is full
        
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 100000; i++) {
        sem_wait(&full);  // Wait for a full slot
        pthread_mutex_lock(&mutex);  // Lock before accessing shared buffer
        int item = buffer[use_ptr];
        use_ptr = (use_ptr + 1) % BUFFER_SIZE;
        items_consumed++;  
        printf("Consumer %d consumed: %d\n", id, item);
        pthread_mutex_unlock(&mutex);  // Unlock after accessing shared buffer
        sem_post(&empty);  // Signal that a slot is now empty
      
    }
    return NULL;
}

int main() {
    pthread_t prod_threads[2], cons_threads[2];
    int prod_ids[2] = {1, 2};
    int cons_ids[2] = {1, 2};
    
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all slots are empty
    sem_init(&full, 0, 0);              // Initially no slots are full
    pthread_mutex_init(&mutex, NULL);  // Initialize mutex
    
    printf("Starting Producer-Consumer with Finite Buffer\n");
    
    for(int i = 0; i < 2; i++) {
        pthread_create(&prod_threads[i], NULL, producer, &prod_ids[i]);
        pthread_create(&cons_threads[i], NULL, consumer, &cons_ids[i]);
    }
    
    for(int i = 0; i < 2; i++) {
        pthread_join(prod_threads[i], NULL);
        pthread_join(cons_threads[i], NULL);
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);  // Destroy mutex
    
    printf("\n========== FINAL RESULTS ==========\n");
    printf("Total items produced: %d\n", items_produced);
    printf("Total items consumed: %d\n", items_consumed);
    printf("Final fill_ptr: %d\n", fill_ptr);
    printf("Final use_ptr: %d\n", use_ptr);
    
    
    return 0;
}

