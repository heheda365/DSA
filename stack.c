#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// 创建线性表
bool InitStack(Stack * s){
	ElemType * tempP;
	tempP = (ElemType *) malloc(sizeof(ElemType) * INIT_SIZE);
	if(NULL != tempP){
		s->data = tempP;
	} else {
		return false;
	}
	
	// 初始表长为0
	s->length = 0; 
	// 初始最大容量为最大容量
	s->maxSize = INIT_SIZE;

	return true;
}
//
// 栈中元素长度
//
int Length(Stack * s){
	return s->length;
}
//
// 判断是否为空栈
//
bool StackEmpty(Stack * s){
	if(s->length <= 0){
		return true;
	} else {
		return false;
	}
}
//
// 获取栈顶元素
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
// 入栈
//
bool Push(Stack * s, ElemType e){
	ElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// 检查表是否已满，如果已满， 扩大一倍
	//
	if(s->length == s->maxSize){
		s->maxSize *= 2; 		// 容量扩倍
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
// 出栈
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
// 打印找中所有元素
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
