#include <stdlib.h>
#include <stdio.h>
#include "cycleQueue.h"

//
// ��ʼ���ж�
// 
bool InitQueue(CycQueue * q){
	ElemType * tempP;
	tempP = (ElemType *) malloc(sizeof(ElemType) * INIT_SIZE);
	if(NULL != tempP){
		q->data = tempP;
	} else {
		return false;
	}
	
	// ��ʼ��ͷ ��β
	q->front = 0; 
	q->rear = 0;
	// ��ʼ�������Ϊ�������
	q->maxSize = INIT_SIZE;

	return true;
}
//
// ��ӳ�
//
int Length(CycQueue * q){
	return (q->maxSize + q->rear - q->front) % q->maxSize;
}
//
// �ж϶��Ƿ�Ϊ��
//
bool QueueEmpty(CycQueue * q){
	if(q->front == q->rear){
		return true;
	} else {
		return false;
	}
}

//
// ��ȡ��ͷԪ��
//
bool GetHead(CycQueue * q, ElemType * e){
	if(!QueueEmpty(q)){
		*e = q->data[q->front];
		return true;
	} else {
		return false;
	}
}
//
// ���
//
bool EnQueue(CycQueue * q, ElemType e){
	ElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// ���ѭ�������Ƿ���������������� ����һ��
	// ���ӳ�Ϊ maxSize - 1 ��Ϊ ����
	if(Length(q) == q->maxSize - 1){
		q->maxSize *= 2; 		// ��������
		tempPN = (ElemType *)malloc(sizeof(ElemType) * q->maxSize); 
		if(NULL != tempPN){
			tempPO = q->data;
			q->data = tempPN;
			
			for(j=q->front; j < Length(q); j++){
				q->data[(j + q->maxSize) % q->maxSize] = tempPO[(j+q->maxSize/2) % (q->maxSize / 2)];
			}
			free(tempPO);
			// �����β
			q->rear = (q->front + Length(q)) % q->maxSize; 
		} else {
			return false;
		}
	}
	q->data[q->rear] = e;
	q->rear ++;
	q->rear = q->rear % q->maxSize;

	return true;
}
//
// ����
//
bool DeQueue(CycQueue * q, ElemType * e){
	if(!QueueEmpty(q)){
		*e = q->data[q->front];
		q->front = (++ q->front) % q->maxSize;
		return true;
	} else {
		return false;
	}
}

//
// ��ӡȫ��
//
void PrintQueue(CycQueue * q){
	int i = 0;
	for(i=0; i<Length(q); i++){
		printf("%d  ", q->data[(q->front + i) % q->maxSize]);
	}
}

int main(void){
	CycQueue q;
	int i = 0;
	ElemType e = 0;
	InitQueue(&q);
	
	for(i=0; i<1000; i++){
		EnQueue(&q, i);
	} 
	PrintQueue(&q);
	printf("\n");

	for(i=0; i<500; i++){
		DeQueue(&q, &e);
	}
	PrintQueue(&q);
	printf("\n");

	printf("q.maxSize = %d \n", q.maxSize);

	return 0;
}