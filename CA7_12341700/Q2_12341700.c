#include <pthread.h>
#include <stdio.h>

void* print_id(void* arg){
    int id=*(int*)arg;
    printf("thread %d running\n",id);
    return NULL;
}

int main(){
    pthread_t tid[10];
    int mid[10];
    for(int i=0;i<10;i++){
        mid[i]=i+1;
        pthread_create(&tid[i],NULL,print_id,&mid[i]);
    }
    for(int i=0;i<10;i++){
        pthread_join(tid[i],NULL);
    }
    printf("All Threads finished! \n");
    return 0;
}