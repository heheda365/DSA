#include <stdlib.h>
#include <stdio.h>
#include "binTree.h"


/*******************************�жӵ��������****************************/

#define INIT_SIZE 		100
typedef BiTNode * QueElemType;
typedef struct{
	QueElemType * data;
	int front;		// ��ͷ
	int rear;		// ��β
	int maxSize;
} CycQueue;

bool InitQueue(CycQueue * q);
int QueueLength(CycQueue * q);
bool QueueEmpty(CycQueue * q);

bool GetHead(CycQueue * q, QueElemType * e);
bool EnQueue(CycQueue * q, QueElemType e);
bool DeQueue(CycQueue * q, QueElemType * e);

//
// ��ʼ���ж�
// 
bool InitQueue(CycQueue * q){
	QueElemType * tempP;
	tempP = (QueElemType *) malloc(sizeof(QueElemType) * INIT_SIZE);
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
int QueueLength(CycQueue * q){
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
bool GetHead(CycQueue * q, QueElemType * e){
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
bool EnQueue(CycQueue * q, QueElemType e){
	QueElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// ���ѭ�������Ƿ���������������� ����һ��
	// ���ӳ�Ϊ maxSize - 1 ��Ϊ ����
	if(QueueLength(q) == q->maxSize - 1){
		q->maxSize *= 2; 		// ��������
		tempPN = (QueElemType *)malloc(sizeof(QueElemType) * q->maxSize); 
		if(NULL != tempPN){
			tempPO = q->data;
			q->data = tempPN;
			
			for(j=q->front; j < QueueLength(q); j++){
				q->data[(j + q->maxSize) % q->maxSize] = tempPO[(j+q->maxSize/2) % (q->maxSize / 2)];
			}
			free(tempPO);
			// �����β
			q->rear = (q->front + QueueLength(q)) % q->maxSize; 
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
bool DeQueue(CycQueue * q, QueElemType * e){
	if(!QueueEmpty(q)){
		*e = q->data[q->front];
		q->front = (++ q->front) % q->maxSize;
		return true;
	} else {
		return false;
	}
}
/************************************�ж�end*****************************/

/******************************ջ����غ���******************************/

typedef BiTNode * StaElemType;
typedef struct{
	StaElemType * data;
	int length;
	int maxSize;
} Stack;

bool InitStack(Stack * s);
int StackLength(Stack * s);
bool StackEmpty(Stack * s);
bool GetTop(Stack * s, StaElemType * e);
bool Push(Stack * s, StaElemType e);
bool Pop(Stack * s, StaElemType * e);

// �������Ա�
bool InitStack(Stack * s){
	StaElemType * tempP;
	tempP = (StaElemType *) malloc(sizeof(StaElemType) * INIT_SIZE);
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
int StackLength(Stack * s){
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
bool GetTop(Stack * s, StaElemType * e){
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
bool Push(Stack * s, StaElemType e){
	StaElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// �����Ƿ���������������� ����һ��
	//
	if(s->length == s->maxSize){
		s->maxSize *= 2; 		// ��������
		tempPN = (StaElemType *)malloc(sizeof(StaElemType) * s->maxSize); 
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
bool Pop(Stack * s, StaElemType * e){
	if(!StackEmpty(s)){
		*e = s->data[s->length - 1];
		s->length --;
		return true;
	} else {
		return false;
	}
}
/******************************ջ����غ���end***************************/

#define SEQ_BIN_TREE_SIZE		40
ElemType seqBinTree[SEQ_BIN_TREE_SIZE] = {
								1,
				2,								3,
		4,				5,				6,				7,
	8,		9,		10,		0,		0,		13,		0,		15,
 16,  17, 18, 19, 20, 21, 0,  23, 24, 25, 26, 27, 28, 29, 30, 31		
};
//
// ����˳�򴢴�Ķ�����������ʽ������
// binTree ָ������
//
bool createBinTree(BiTree * binTree, ElemType seqBinTree[], int size){
	BiTNode * tempP = NULL, * p = NULL;
	CycQueue q;
	int i = 0;
	int LOrR = 0;		// ���Һ��� 0�� 1��
	InitQueue(&q);		// ׼��һ������
	// sizeΪ0 ��������
	if(size <= 0){
		*binTree = NULL;
		return true;
	} else {
		// ���������
		tempP = (BiTNode *)malloc(sizeof(BiTNode));	
		if(NULL != tempP){
			// ���Ӹ����
			tempP->lchild = NULL;
			tempP->rchild = NULL;
			tempP->data = seqBinTree[0];
			*binTree = tempP;
		} else {
			return false;
		}
	}
	EnQueue(&q, *binTree);
	i = 1;
	while(i < size){
		if(seqBinTree[i] != 0){
			// �����
			tempP = (BiTNode *)malloc(sizeof(BiTNode));	
			if(NULL != tempP){
				// ���Ӹ����
				tempP->lchild = NULL;
				tempP->rchild = NULL;
				tempP->data = seqBinTree[i];
			} else {
				return false;
			}
			// ����������
		} else {
			tempP = NULL;
		}
		if(1 == i%2){
			DeQueue(&q, &p);
		}
		if(NULL != p){
			if(0 == LOrR){
				// ��������
				p->lchild = tempP;
			} else {
				// �����ҽ��
				p->rchild = tempP;
			}
		}
		EnQueue(&q, tempP);
		LOrR = !LOrR;
		i ++;
	}
	return true;
}

//
// ����Ϊ��ӡ�����Ϣ
//
void visit(BiTree t){
	printf("%d  ", t->data);
}
/*****************************�ݹ���������*****************************/
//
// �������
//
void preOrder(BiTree t){
	if(NULL != t){
		visit(t);
		preOrder(t->lchild);
		preOrder(t->rchild);
	}
}
//
// �������
//
void inOrder(BiTree t){
	if(NULL != t){
		inOrder(t->lchild);
		visit(t);
		inOrder(t->rchild);
	}
}

//
// �������
//
void postOrder(BiTree t){
	if(NULL != t){
		postOrder(t->lchild);
		postOrder(t->rchild);
		visit(t);
	}
}
/****************************�ݹ���������end***************************/

/******************************�ǵݹ��ı�������***********************/
void preOrder1(BiTree t){
	BiTree p = NULL;
	Stack s;
	p = t;
	if(NULL == p){
		return;
	}
	
	InitStack(&s);
	Push(&s, p);
	while(!StackEmpty(&s)){
		Pop(&s, &p);
		visit(p);
		if(NULL != p->rchild){
			Push(&s, p->rchild);
		}
		if(NULL != p->lchild){
			Push(&s, p->lchild);
		}
	}
}
void inOrder1(BiTree t){
	BiTree p = NULL;
	Stack s;
	p = t;
	if(NULL == p){
		return;
	}
	InitStack(&s);
	while(p || !StackEmpty(&s)){
		if(p){
			Push(&s, p);
			p = p->lchild;
		} else {
			Pop(&s, &p);
			visit(p);
			p = p->rchild;
		}
	}
}
void postOrder1(BiTree t){
	BiTree p = NULL, r = NULL;
	Stack s;
	p = t;
	if(NULL == p){
		return;
	}
	InitStack(&s);
	while(!StackEmpty(&s) || p != NULL){
		if(NULL != p){
			Push(&s, p);
			p = p->lchild;
		} else {
			GetTop(&s, &p);
			if(p->rchild && p->rchild != r){
				p = p->rchild;
				Push(&s, p);
				p = p->lchild;
			} else {
				Pop(&s, &p);
				visit(p);
				r = p;
				p = NULL;
			}
		}
	}
	
}
//void postOrder2(BiTree t){
//	BiTree p = NULL, r = NULL;
//	Stack s;
//	p = t;
//	if(NULL == p){
//		return;
//	}
//	InitStack(&s);
//	Push(&s, p);
//	while(!StackEmpty(&s)){
//		if(NULL != p->rchild){
//			Push(&s, p->rchild);
//		}
//		if(NULL != p->lchild){
//			Push(&s, p->lchild);
//			p = p->lchild;
//		} else {
//			if(NULL == p->rchild && p->rchild == r){
//				visit(p);
//				r = p;
//				Pop(&s, &p);
//			}
//		}
//	}
//	
//}
//
// ��α���
//
void levelOrder(BiTree t){
	BiTree p = NULL;
	CycQueue q;
	p = t;
	if(NULL == p){
		return;
	}
	InitQueue(&q);
	EnQueue(&q, p);
	while(!QueueEmpty(&q)){
		DeQueue(&q, &p);
		visit(p);
		if(p->lchild != NULL){
			EnQueue(&q, p->lchild);
		}
		if(p->rchild != NULL){
			EnQueue(&q, p->rchild);
		}
	}
}

/******************************�ǵݹ��ı�������end********************/

int main(void){
	BiTree t;
	createBinTree(&t, seqBinTree, SEQ_BIN_TREE_SIZE);
	
	preOrder(t);
	printf("\n");
	inOrder(t);
	printf("\n");
	postOrder(t);
	printf("\n");
	
	levelOrder(t);
	printf("\n\n");
	
	preOrder1(t);
	printf("\n");
	
	inOrder1(t);
	printf("\n");
	
	postOrder1(t);
	printf("\n");
	
	return 0;
}