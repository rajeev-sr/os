#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  

sem_t forks[N];  
int eat_count[N] = {0};  

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % N;
    
    // Lower ID First Strategy: always pick lower-numbered fork first
    int first_fork = (left_fork < right_fork) ? left_fork : right_fork;
    int second_fork = (left_fork < right_fork) ? right_fork : left_fork;
    
    for(int i = 0; i < 3; i++) {
        
        printf("Philosopher %d is thinking...\n", id);
        usleep(100000);
        
       
        printf("Philosopher %d is hungry, reaching for forks %d and %d\n", 
               id, left_fork, right_fork);
        
        // Pick up lower-numbered fork first
        sem_wait(&forks[first_fork]);  
        printf("  Philosopher %d picked up fork %d (first)\n", id, first_fork);
        usleep(50000);  
        
        // Then pick up higher-numbered fork
        sem_wait(&forks[second_fork]); 
        printf("  Philosopher %d picked up fork %d (second)\n", id, second_fork);
        
       
        printf("Philosopher %d is EATING (meal #%d)\n", id, eat_count[id] + 1);
        eat_count[id]++;
        usleep(200000);
        
        
        sem_post(&forks[first_fork]);
        sem_post(&forks[second_fork]);
        printf("  Philosopher %d put down both forks\n\n", id);
    }
    
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];
    
   
    for(int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }
    
    printf("=== DINING PHILOSOPHERS - DEADLOCK FIXED (Lower ID First) ===\n");
    printf("Number of philosophers: %d\n", N);
    printf("Strategy: Always pick up lower-numbered fork first\n\n");
    
    
    for(int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    
   
    for(int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    
    for(int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    
    printf("\n========== MEAL COUNT ==========\n");
    for(int i = 0; i < N; i++) {
        printf("Philosopher %d ate %d times (expected: 3)\n", i, eat_count[i]);
    }
    
    return 0;
}

