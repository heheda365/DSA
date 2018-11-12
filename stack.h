#ifndef __STACK_H__
#define __STACK_H__

typedef int bool;
//#define NULL (void *) 0

#define true 1
#define false 0
typedef int ElemType;

#define INIT_SIZE 		100

typedef struct{
	ElemType * data;
	int length;
	int maxSize;
} Stack;

bool InitStack(Stack * s);
int Length(Stack * s);
bool StackEmpty(Stack * s);
bool GetTop(Stack * s, ElemType * e);
bool Push(Stack * s, ElemType e);
bool Pop(Stack * s, ElemType * e);
void PrintList(Stack * s);


#endif

