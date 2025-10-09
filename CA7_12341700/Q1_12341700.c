#include <pthread.h>
#include <stdio.h>

int global_var;

void* var_id(void* arg){
    int thread_local_var;
    int id=*(int*)arg;
    printf("Thread id : %d \nGlobal variable at address: %p \nThread local variable at address: %p\n",id,(void*)&global_var,(void*)&thread_local_var);
    return NULL;
}

int main(){
    pthread_t tid1;
    pthread_t tid2;
    int id1=23;
    int id2=45;
    int main_local_var;
    printf("Main :\nGlobal variable at address: %p \nMain local variable at address: %p \n",(void*)&global_var,(void*)&main_local_var);
    pthread_create(&tid1,NULL,var_id,&id1);
    pthread_create(&tid2,NULL,var_id,&id2);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}