#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef long ELEM;

#define QUEUE_SIZE 100

ELEM queue[QUEUE_SIZE];
int front;
int rear;

#define next(a) (((a) + 1) % QUEUE_SIZE)

void error (char *s) {
  fprintf(stderr, s);
  exit(1);
}

void init () {
  front = 0;
  rear = 0;
}

int empty () {
  return front == rear;
}

void enqueue(ELEM x) {
  if (next(rear) == front) {
    error("couldn't enqueue params because of full\n");
  }

  queue[rear] = x;
  rear = next(rear);
}

ELEM dequeue() {
  ELEM x;
  if (empty()) {
    error("queue is empty, can not dequeue\n");
  }

  x = queue[front];
  front = next(front);
  return x;
}
