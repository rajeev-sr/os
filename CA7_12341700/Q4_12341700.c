#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* compute_square(void* arg){
    int num=*(int*)arg;
    int * result=malloc(sizeof(int));
    *result=num*num;
    return result;
}


int main(){
    pthread_t tid;
    int n=23;
    pthread_create(&tid,NULL,compute_square,&n);
    int* result;
    pthread_join(tid,(void**)&result);
    printf("Thread finished! \n");
    printf("Square of the number %d is : %d\n",n,*result);
    free(result);
    return 0;
}