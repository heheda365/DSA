#ifndef __LinkQueue_H__
#define __LinkQueue_H__

typedef int bool;
//#define NULL (void *) 0

#define true 1
#define false 0

#define INIT_SIZE 		100
typedef int ElemType;

typedef struct LQNode{
	ElemType data;
	struct LQNode * next;
} LQNode;

typedef struct{
	LQNode * front;
	LQNode * rear;
	int length;
} LinkQueue;

bool InitQueue(LinkQueue * q);
int Length(LinkQueue * q);
bool QueueEmpty(LinkQueue * q);

bool GetHead(LinkQueue * q, ElemType * e);
bool EnQueue(LinkQueue * q, ElemType e);
bool DeQueue(LinkQueue * q, ElemType * e);

void PrintQueue(LinkQueue * q);

#endif

