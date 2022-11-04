#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define SIZE 20
#define default -1

typedef int datatype;


typedef struct queue{
   datatype data[SIZE];
   int rear;
   int front;
}queue;

queue* init(void);
bool isfull(queue* q);
bool isempty(queue* q);
void enqueue(queue* q, datatype data);
datatype dequeue(queue* q);

int main(void){
   queue* q = init();
   assert(!isfull(q));
   assert(isempty(q));
   enqueue(q, 15);
   assert(!isfull(q));
   printf("q->rear:%d\n", q->rear);
   printf("q->data:%d\n", q->data[q->front+1]);
   assert(!isempty(q));
   assert(dequeue(q) == 15);
}

queue* init(void){
   queue* q = (queue*)malloc(sizeof(queue));
   q->front = -1;
   q->rear = -1;
   for (int i = 0; i < SIZE; i++){
      q->data[i] = default;
   }
   return q;
}

bool isfull(queue* q){
   return q->rear == q->front && q->rear != -1;
}
bool isempty(queue* q){
   return q->front == -1 && q->rear == -1;

   return q->rear == q->front && q->data[q->front] == -1;
}

void enqueue(queue* q, datatype data){
   if (isfull(q)){
      printf("full-> unable to add->\n");
      return;
   }else{
      q->data[++q->rear] = data;
      return;
   }
}

datatype dequeue(queue* q){
   if (isempty(q)){
      printf("empty unable to remove return default value\n");
      return default;
   }else{
      return q->data[++q->front];
   }
}
