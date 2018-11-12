#ifndef __CYCLEQUEUE_H__
#define __CYCLEQUEUE_H__

typedef int bool;
//#define NULL (void *) 0

#define true 1
#define false 0

#define INIT_SIZE 		100
typedef int ElemType;
typedef struct{
	ElemType * data;
	int front;		// ∂”Õ∑
	int rear;		// ∂”Œ≤
	int maxSize;
} CycQueue;

bool InitQueue(CycQueue * q);
int Length(CycQueue * q);
bool QueueEmpty(CycQueue * q);

bool GetHead(CycQueue * q, ElemType * e);
bool EnQueue(CycQueue * q, ElemType e);
bool DeQueue(CycQueue * q, ElemType * e);

void PrintQueue(CycQueue * q);



#endif

