#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#define SIZE 1024

struct QueueNode {
    char data[SIZE];
    struct QueueNode* next;
};

typedef struct {
    struct QueueNode* front;
    struct QueueNode* rear;
    int count;
} DynamicQueue;

DynamicQueue* createQueue();
int isEmpty(DynamicQueue* queue);
int size(DynamicQueue* queue);
void enqueue(DynamicQueue* queue, char* data);
char* dequeue(DynamicQueue* queue);
void freeQueue(DynamicQueue* queue);

#endif  /* DYNAMIC_QUEUE_H */
