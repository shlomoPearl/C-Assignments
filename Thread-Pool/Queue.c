#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DynamicQueue* createQueue() {
    DynamicQueue* queue = (DynamicQueue*)malloc(sizeof(DynamicQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}


//return 1 iff queue is empty other 0
int isEmpty(DynamicQueue* queue) {
    return (queue->front == NULL);
}

int size(DynamicQueue* queue) {
    return queue->count;
}

void enqueue(DynamicQueue* queue, char* data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    strncpy(newNode->data, data, SIZE);
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->count++;
}

char* dequeue(DynamicQueue* queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue is empty.\n");
        return "";
    }
    char* data = malloc(SIZE);
    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    strncpy(data, temp->data, SIZE);
    free(temp);
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->count--;
    return data;
}

void freeQueue(DynamicQueue* queue) {
    // while (!isEmpty(queue)) {
    //     dequeue(queue);
    // }
    // free(queue);

    struct QueueNode* current = queue->front;
    while (current != NULL) {
        struct QueueNode* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(queue);
}
