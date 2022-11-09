#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define SIZE 20
#define DEFAULT -1

typedef int datatype;

typedef struct queue{
   datatype data[SIZE];
   int end;
   int front;
}queue;

queue* queue_init(void);
void queue_enqueue(queue* q, datatype data);
datatype queue_dequeue(queue* q);
int queue_size(queue* q);
bool queue_free(queue* q);
void _inc(int* p);

int main(void){
   queue* q = queue_init();
   assert(queue_size(q) == 0);
   queue_enqueue(q, 15);
   assert(queue_size(q) == 1);
   queue_enqueue(q, 25);
   assert(queue_size(q) == 2);
   queue_enqueue(q, 35);
   assert(queue_size(q) == 3);
   assert(queue_dequeue(q) == 15);
   assert(queue_size(q) == 2);
   assert(queue_dequeue(q) == 25);
   assert(queue_size(q) == 1);
   assert(queue_dequeue(q) == 35);
   assert(queue_size(q) == 0);
   
 /* assertion below should test the _inc function**/
   for (int i = 0; i < SIZE; i++){
      queue_enqueue(q, i);
   }
   for (int i = 0; i < SIZE / 2; i++){
      assert(queue_dequeue(q) == i);
   }
   
   for (int i = 0; i < SIZE / 2; i++){
      queue_enqueue(q, i * 2);
   }
   
   for (int i = 0; i < SIZE / 2; i++){
      assert(queue_dequeue(q) == i + SIZE / 2);
   }
   
   for (int i = 0; i < SIZE / 2; i++){
      assert(queue_dequeue(q) == i * 2);
   }
   
   
}

queue* queue_init(void){
   queue* q = (queue*)malloc(sizeof(queue));
   q->front = 0;
   q->end = 0;
   for (int i = 0; i < SIZE; i++){
      q->data[i] = DEFAULT;
   }
   return q;
}

void queue_enqueue(queue* q, datatype data){
   if (q->end == q->front && q->data[0] != DEFAULT){
      printf("full-> unable to add->\n");
      return;
   }else{
      q->data[q->end] = data;
      _inc(&q->end);
      return;
   }
}

datatype queue_dequeue(queue* q){
   if (q->end == q->front && q->data[0] == DEFAULT){
      printf("empty unable to remove return default value\n");
      return DEFAULT;
   }else{
      datatype data = q->data[q->front];
      q->data[q->front] = DEFAULT;
      _inc(&q->front);
      return data;
   }
}

int queue_size(queue* q){
   if(!q){
      return -1;
   }else if (q->end >= q->front){
      return q->end - q->front;
   }else{
      return q->front - q->end + SIZE;
   }
}

bool queue_free(queue* q){
   free(q);
   return true;
}

void _inc(int* p){
   *p = (*p + 1) % SIZE;
}
