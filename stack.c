#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// �������Ա�
bool InitStack(Stack * s){
	ElemType * tempP;
	tempP = (ElemType *) malloc(sizeof(ElemType) * INIT_SIZE);
	if(NULL != tempP){
		s->data = tempP;
	} else {
		return false;
	}
	
	// ��ʼ��Ϊ0
	s->length = 0; 
	// ��ʼ�������Ϊ�������
	s->maxSize = INIT_SIZE;

	return true;
}
//
// ջ��Ԫ�س���
//
int Length(Stack * s){
	return s->length;
}
//
// �ж��Ƿ�Ϊ��ջ
//
bool StackEmpty(Stack * s){
	if(s->length <= 0){
		return true;
	} else {
		return false;
	}
}
//
// ��ȡջ��Ԫ��
//
bool GetTop(Stack * s, ElemType * e){
	if(!StackEmpty(s)){
		*e = s->data[s->length - 1];
		return true;
	} else {
		return false;
	}
}

//
// ��ջ
//
bool Push(Stack * s, ElemType e){
	ElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// �����Ƿ���������������� ����һ��
	//
	if(s->length == s->maxSize){
		s->maxSize *= 2; 		// ��������
		tempPN = (ElemType *)malloc(sizeof(ElemType) * s->maxSize); 
		if(NULL != tempPN){
			tempPO = s->data;
			s->data = tempPN;
			
			for(j=0; j < s->length; j++){
				s->data[j] = tempPO[j];
			}
			free(tempPO);
		} else {
			return false;
		}
	}
	
	s->data[s->length] = e;
	s->length ++;
	
	return true;
}

//
// ��ջ
//
bool Pop(Stack * s, ElemType * e){
	if(!StackEmpty(s)){
		*e = s->data[s->length - 1];
		s->length --;
		return true;
	} else {
		return false;
	}
}

//
// ��ӡ��������Ԫ��
//
void PrintList(Stack * s){
	int i;
	for(i=0; i < s->length; i++){
		printf("%d  ", s->data[i]);
	}
}

int main(void){
	Stack s;
	ElemType a = 0;
	int i = 0;
	InitStack(&s);
	for(i=0; i<200; i++){
		Push(&s, i);
	}
	PrintList(&s);
	printf("\n");
	printf("s.maxSize = %d", s.maxSize);
	printf("\n");
	
	Pop(&s, &a);
	PrintList(&s);
	printf("\n");
	printf("a = %d \n", a);

	return 0;
}
