#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "codec.h"
#include "Queue.h"

#define THREAD_NUM  sysconf(_SC_NPROCESSORS_ONLN)
#define ENCRYPT 1
#define DECRYPT 0

int finish = 0;
int key = 2;
int e_d_flag;

pthread_mutex_t mutex_queue;
pthread_cond_t cond_queue;
DynamicQueue* queue;

void executeTask(char* data) {
    if(e_d_flag){
        encrypt(data, key);
    } else{
        decrypt(data, key);
    }
    printf("%s\n",data);
    // free(data);
}

void submitTask(char* data) {
    char* data_copy = strdup(data);
    pthread_mutex_lock(&mutex_queue);
    // printf("%s\n", data);
    enqueue(queue, data_copy);
    pthread_mutex_unlock(&mutex_queue);
    pthread_cond_signal(&cond_queue);
}

void* startThread(void* args) {
    while (1) {
        pthread_mutex_lock(&mutex_queue);
        while (isEmpty(queue) && !finish) {
            pthread_cond_wait(&cond_queue, &mutex_queue);
        } 
        if(size(queue) > 0){
            char* data = dequeue(queue);      
            pthread_mutex_unlock(&mutex_queue);
            executeTask(data);
            free(data);
        }else{
            pthread_mutex_unlock(&mutex_queue);
            break; // Break out of the while loop if there are no tasks and stopFlag is set
        }
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutex_queue, NULL);
    pthread_cond_init(&cond_queue, NULL);

    char* flag = argv[2];
    int isEncryption = strcmp(flag, "-e") == 0;
    int isDecryption = strcmp(flag, "-d") == 0;

    if (!isEncryption && !isDecryption) {
        printf("%s\n", flag);
        printf("Invalid key. Please use '-e' for encryption or '-d' for decryption.\n");
        return 1;
    }else if(isEncryption){
        e_d_flag = ENCRYPT;
    }else{
        e_d_flag = DECRYPT;
    }

    queue = createQueue();

    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) {
            perror("Failed to create the thread");
        }
    }

    char data[SIZE];
    size_t bytesRead;
    
    while ((bytesRead = fread(data, sizeof(char), sizeof(data), stdin)) > 0) {
        submitTask(data);
        // fwrite(data, sizeof(char), bytesRead, stdout);
        // printf("\n");
    }
    finish = 1;
    pthread_cond_broadcast(&cond_queue);
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join the thread");
        }
    }
    pthread_mutex_destroy(&mutex_queue);
    pthread_cond_destroy(&cond_queue);
    freeQueue(queue);
    return 0;
}