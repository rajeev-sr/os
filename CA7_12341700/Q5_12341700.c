#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void* square(void* arg){
    int num = *(int*)arg;
    int* result = malloc(sizeof(int));
    *result = num * num;
    printf("Thread %d return %d\n", num, *result);
    return (void*)result;
}
int main(){
    pthread_t tids[5];
    int args[5];
    for(int i = 0; i < 5; i++){
        args[i] = i + 1;
        pthread_create(&tids[i], NULL, square, (void*)&args[i]);
    }
    int* results[5];
    int sum = 0;
    for(int i = 0; i < 5; i++){
        pthread_join(tids[i], (void**)&results[i]);
        sum += *results[i];
        free(results[i]);
    }
    printf("Sum of squares: %d\n", sum);
    return 0;
}