#include <pthread.h>
#include <stdio.h>

int count=0;
void* increment_count(void* arg){
    int id=*(int*)arg;
    for(int i=0;i<1000000;i++){
        count=count+1;
    }
    return NULL;
}

int main(){
    pthread_t tid[10];
    int mid[10];
    for(int i=0;i<10;i++){
        mid[i]=i+1;
        pthread_create(&tid[i],NULL,increment_count,&mid[i]);
    }
    for(int i=0;i<10;i++){
        pthread_join(tid[i],NULL);
    }
    printf("All Threads finished! \n");
    printf("Final count value: %d\n",count);
    return 0;
}