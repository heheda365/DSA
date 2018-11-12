#include <stdlib.h>
#include <stdio.h>
#include "linkQueue.h"

bool InitQueue(LinkQueue * q){
	// 带个头结点方便操作
	LQNode * p = NULL;
	p = (LQNode *)malloc(sizeof(LQNode));
	if(NULL != p){
		p->next = NULL;
		q->front = p;
		q->rear = p;
	} else {
		return false;
	}
	q->length = 0;
	return true;
}

int Length(LinkQueue * q){
	return q->length;
}

bool QueueEmpty(LinkQueue * q){
	if(Length(q) == 0){
		return true;
	} else {
		return false;
	}
}
//
// 队头
// 
bool GetHead(LinkQueue * q, ElemType * e){
	if(!QueueEmpty(q)){
		*e = q->front->data;
		return true;
	} else {
		return false;
	}
}
//
// 入列
//
bool EnQueue(LinkQueue * q, ElemType e){
	LQNode * p = NULL;
	p = (LQNode *)malloc(sizeof(LQNode));
	if(NULL != p){
		p->next = NULL;
		q->rear->next = p;
		q->rear = p;
		q->rear->data = e;
		q->length ++;
		return true;
	} else {
		return false;
	}
}
//
// 出队
//
bool DeQueue(LinkQueue * q, ElemType * e){
	LQNode *p = NULL;
	if(!QueueEmpty(q)){
		*e = q->front->next->data;
		p = q->front;
		q->front = q->front->next;
		q->length --;
		free(p);
		return true;
	} else {
		return false;
	} 
}

//
// 打印全部
//
void PrintQueue(LinkQueue * q){
	int i = 0;
	LQNode * p = NULL;
	p = q->front;
	for(i=0; i<Length(q); i++){
		printf("%d  ", p->next->data);
		p = p->next;
	}
}
int main(void){
	LinkQueue lq;
	ElemType e;
	int i;
	InitQueue(&lq);
	for(i=0; i<200; i++){
		EnQueue(&lq, i);
	} 
	PrintQueue(&lq);
	printf("\n");
	
	for(i=0; i<100; i++){
		DeQueue(&lq, &e);
	}
	PrintQueue(&lq);
	printf("\n");
	
	printf("lq length = %d", Length(&lq));
}