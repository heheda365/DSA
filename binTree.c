#include <stdlib.h>
#include <stdio.h>
#include "binTree.h"


/*******************************列队的相关内容****************************/

#define INIT_SIZE 		100
typedef BiTNode * QueElemType;
typedef struct{
	QueElemType * data;
	int front;		// 队头
	int rear;		// 队尾
	int maxSize;
} CycQueue;

bool InitQueue(CycQueue * q);
int QueueLength(CycQueue * q);
bool QueueEmpty(CycQueue * q);

bool GetHead(CycQueue * q, QueElemType * e);
bool EnQueue(CycQueue * q, QueElemType e);
bool DeQueue(CycQueue * q, QueElemType * e);

//
// 初始化列队
// 
bool InitQueue(CycQueue * q){
	QueElemType * tempP;
	tempP = (QueElemType *) malloc(sizeof(QueElemType) * INIT_SIZE);
	if(NULL != tempP){
		q->data = tempP;
	} else {
		return false;
	}
	
	// 初始队头 队尾
	q->front = 0; 
	q->rear = 0;
	// 初始最大容量为最大容量
	q->maxSize = INIT_SIZE;

	return true;
}
//
// 求队长
//
int QueueLength(CycQueue * q){
	return (q->maxSize + q->rear - q->front) % q->maxSize;
}
//
// 判断队是否为空
//
bool QueueEmpty(CycQueue * q){
	if(q->front == q->rear){
		return true;
	} else {
		return false;
	}
}

//
// 获取队头元素
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
// 入队
//
bool EnQueue(CycQueue * q, QueElemType e){
	QueElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// 检查循环队列是否已满，如果已满， 扩大一倍
	// 当队长为 maxSize - 1 判为 队满
	if(QueueLength(q) == q->maxSize - 1){
		q->maxSize *= 2; 		// 容量扩倍
		tempPN = (QueElemType *)malloc(sizeof(QueElemType) * q->maxSize); 
		if(NULL != tempPN){
			tempPO = q->data;
			q->data = tempPN;
			
			for(j=q->front; j < QueueLength(q); j++){
				q->data[(j + q->maxSize) % q->maxSize] = tempPO[(j+q->maxSize/2) % (q->maxSize / 2)];
			}
			free(tempPO);
			// 计算队尾
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
// 出队
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
/************************************列队end*****************************/

/******************************栈的相关函数******************************/

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

// 创建线性表
bool InitStack(Stack * s){
	StaElemType * tempP;
	tempP = (StaElemType *) malloc(sizeof(StaElemType) * INIT_SIZE);
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
int StackLength(Stack * s){
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
bool GetTop(Stack * s, StaElemType * e){
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
bool Push(Stack * s, StaElemType e){
	StaElemType * tempPN, * tempPO;
	int j = 0;
	// 
	// 检查表是否已满，如果已满， 扩大一倍
	//
	if(s->length == s->maxSize){
		s->maxSize *= 2; 		// 容量扩倍
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
// 出栈
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
/******************************栈的相关函数end***************************/

#define SEQ_BIN_TREE_SIZE		40
ElemType seqBinTree[SEQ_BIN_TREE_SIZE] = {
								1,
				2,								3,
		4,				5,				6,				7,
	8,		9,		10,		0,		0,		13,		0,		15,
 16,  17, 18, 19, 20, 21, 0,  23, 24, 25, 26, 27, 28, 29, 30, 31		
};
//
// 根据顺序储存的二叉树创建链式二叉树
// binTree 指向根结点
//
bool createBinTree(BiTree * binTree, ElemType seqBinTree[], int size){
	BiTNode * tempP = NULL, * p = NULL;
	CycQueue q;
	int i = 0;
	int LOrR = 0;		// 左右孩子 0左 1右
	InitQueue(&q);		// 准备一个队列
	// size为0 创建空树
	if(size <= 0){
		*binTree = NULL;
		return true;
	} else {
		// 创建根结点
		tempP = (BiTNode *)malloc(sizeof(BiTNode));	
		if(NULL != tempP){
			// 连接根结点
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
			// 建结点
			tempP = (BiTNode *)malloc(sizeof(BiTNode));	
			if(NULL != tempP){
				// 连接根结点
				tempP->lchild = NULL;
				tempP->rchild = NULL;
				tempP->data = seqBinTree[i];
			} else {
				return false;
			}
			// 创建结点完成
		} else {
			tempP = NULL;
		}
		if(1 == i%2){
			DeQueue(&q, &p);
		}
		if(NULL != p){
			if(0 == LOrR){
				// 加入左结点
				p->lchild = tempP;
			} else {
				// 加入右结点
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
// 初定为打印结点信息
//
void visit(BiTree t){
	printf("%d  ", t->data);
}
/*****************************递归版遍历函数*****************************/
//
// 先序遍历
//
void preOrder(BiTree t){
	if(NULL != t){
		visit(t);
		preOrder(t->lchild);
		preOrder(t->rchild);
	}
}
//
// 中序遍历
//
void inOrder(BiTree t){
	if(NULL != t){
		inOrder(t->lchild);
		visit(t);
		inOrder(t->rchild);
	}
}

//
// 后序遍历
//
void postOrder(BiTree t){
	if(NULL != t){
		postOrder(t->lchild);
		postOrder(t->rchild);
		visit(t);
	}
}
/****************************递归版遍历函数end***************************/

/******************************非递归版的遍历函数***********************/
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
// 层次遍历
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

/******************************非递归版的遍历函数end********************/

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