#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define RING_BUFFER_SIZE 8

typedef struct {
  int *data;
  int count;
  int capacity;
  int head;
  int tail;
} RingBuffer;


RingBuffer *initialize(int sz) {
  if (sz <= 0) return NULL;
  RingBuffer *rb = malloc(sizeof(RingBuffer));
  if (rb == NULL) {
    printf("Allocation failed!\n");
    return NULL;
  }
  
  rb->data = malloc(sizeof(int) * sz);
  if (rb->data == NULL) {
    printf("Allocation failed!\n");
    free(rb);
    return NULL;
  }

  rb->count = rb->head = rb->tail = 0;
  rb->capacity = sz;
  for (int i = 0; i < rb->capacity; i++) {
    rb->data[i] = 0;
  }

  return rb;
}

void destroy(RingBuffer * rb) {
  free(rb->data);
  free(rb);
}

int isFull(RingBuffer *rb) {
  return (rb->capacity == rb->count)? 1 : 0;
}

int isEmpty(RingBuffer *rb) {
  return !rb->count;
}

void push(RingBuffer *rb, int element) {
  if (isFull(rb)) {
    printf("Ring buffer is full\n");
    return;
  }
  rb->data[rb->head] = element;
  rb->head++;
  rb->count++;
  rb->head %= rb->capacity;
  printf("Element %d was added to the ring buffer\n", element);
}

void pop(RingBuffer *rb) {
  if (isEmpty(rb)) {
    printf("Ring buffer is empty\n");
    return;
  }
  int element = rb->data[rb->tail];
  rb->data[rb->tail] = 0;
  rb->tail++;
  if (rb->tail == rb->capacity) rb->tail = 0;
  rb->count--;
  printf("Element %d popped successfully\n", element);
}

void print(RingBuffer *rb) {
  if (isEmpty(rb)) {
    printf("Ring buffer is empty\n");
    return;
  }
  printf("There are %d elements in the buffer\n", rb->count);
  if (rb->tail >= rb->head) {
    for (int i = rb->tail; i < rb->capacity; i++) {
      printf("%d ", rb->data[i]);
    }
    for (int i = 0; i < rb->head; i++) {
      printf("%d ", rb->data[i]);  
    }
  }
  else {
    for (int i = rb->tail; i < rb->head; i++) {
      printf("%d ", rb->data[i]);
    }
  }
  printf("\n");
}

void print_tail(RingBuffer *rb) {
  if (isEmpty(rb)) {
    printf("Ring buffer is empty\n");
    return;
  }
  printf("The element on the tail is %d\n", rb->data[rb->tail]);
}

void print_head(RingBuffer *rb) {
  if (isEmpty(rb)) {
    printf("Ring buffer is empty\n");
    return;
  }
  printf("The element on the head is %d\n", rb->data[(rb->head - 1 + rb->capacity) % rb->capacity]);
}

int main(void) {
  // the size of the ring buffer is set to 8 by default
  int sz = RING_BUFFER_SIZE;
  RingBuffer *rb = initialize(sz);
  if (rb == NULL) {
    printf("Initialization failed!\n");
    return 0;
  }
  printf("Available operations:\n1: Push element\n2: Pop element\n3: Print elements\n");
  printf("4: Print tail\n5: Print head\n0: Exit\n");
  while (1) {
    int query = 0;
    scanf("%d", &query);
    switch(query) {
      case 1:
        int element = 0;
        scanf("%d", &element);
        push(rb, element);
        break;
      case 2:
        pop(rb);
        break;
      case 3:
        print(rb);
        break;
      case 4:
        print_tail(rb);
        break;
      case 5:
        print_head(rb);
        break;
      case 0:
        destroy(rb);
        return 0;
      default:
        printf("Unknown operation\n"); 
    }
  }
  
  return 0;
}