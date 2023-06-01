#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 4

typedef struct Task {
    int a, b;
} Task;

Task taskQueue[256];
int taskCount = 0;

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

int stopFlag = 0; // Flag to indicate when to stop accepting new tasks

void executeTask(Task* task) {
    usleep(50000);
    int result = task->a + task->b;
    printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}

void submitTask(Task task) {
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

void* startThread(void* args) {
    while (1) {
        Task task;

        pthread_mutex_lock(&mutexQueue);
        while (taskCount == 0 && !stopFlag) {
            pthread_cond_wait(&condQueue, &mutexQueue);
        }

        if (taskCount > 0) {
            task = taskQueue[0];
            int i;
            for (i = 0; i < taskCount - 1; i++) {
                taskQueue[i] = taskQueue[i + 1];
            }
            taskCount--;
            pthread_mutex_unlock(&mutexQueue);
            executeTask(&task);
        } else {
            pthread_mutex_unlock(&mutexQueue);
            break; // Break out of the while loop if there are no tasks and stopFlag is set
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) {
            perror("Failed to create the thread");
        }
    }

    srand(time(NULL));
    for (i = 0; i < 10; i++) {
        Task t = {
            .a = rand() % 100,
            .b = rand() % 100
        };
        submitTask(t);
    }

    // Set the stopFlag to indicate no more tasks should be accepted
    stopFlag = 1;

    pthread_cond_broadcast(&condQueue); // Signal all threads to wake up

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join the thread");
        }
    }
    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
    return 0;
}
