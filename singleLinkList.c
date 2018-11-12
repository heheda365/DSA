#include <stdio.h>
#include <stdlib.h>
#include "singleLinkList.h"

//
// 新建一条长度为 n 带头结点的单链表
// 
bool InitList(LinkList *l, ElemType initData[], int n){
	LinkList tempP = NULL;
	LNode *p = NULL;
	int i = 0;
	tempP = (LinkList)malloc(sizeof(LNode));
	
	if(NULL == tempP){
		return false;
	} else {
		*l = tempP;
	}
	p = *l;		// 带头结点
	for(i=0; i<n; i++){
		tempP = (LinkList)malloc(sizeof(LNode));
		if(NULL == tempP){
			return false;
		} else {
			p->next = tempP;
			p = p->next;
			p->data = initData[i];
		}
	}
	p->next = NULL;
	return true;
}

//
// 打印所有结点的值
//
void PrintList(LinkList l){
	LNode *p = NULL;
	p = l;
	while(NULL != p->next){
		p = p->next;
		printf("%d  ", p->data);
	}
}

//
// 求表长
//
int Length(LinkList l){
	int n = 0;
	LNode *p = NULL;
	p = l;
	while(NULL != p->next){
		p = p->next;
		n ++;
	}
	return n;
}
//
// 在链表的第i个位置插入 e
// 插入后e为第i个元素
//
bool ListInsert(LinkList l, int i, ElemType e){
	int j = 0;
	LNode *p = NULL;
	LNode *pNew = NULL;
	pNew = (LNode *)malloc(sizeof(LNode));
	if(NULL == pNew){
		return false;
	} 
	pNew->data = e;
	p = l;
	for(j=0; j<i-1; j++){
		p = p->next;
	}
	pNew->next = p->next;
	p->next = pNew;
	return true;
}
//
//
// 删除第i个结点
//
bool ListDelete(LinkList l, int i){
	int j = 0;
	LNode *p = NULL, *p1 = NULL;
	p = l;
	if(i<1 || i > Length(l)){
		return false;
	}
	for(j=0; j<i-1; j++){
		p = p->next;
	}
	p1 = p->next;
	p->next = p->next->next;
	free(p1);
	return true;
}
int main(void){
	LinkList l = NULL;
	ElemType initD[8] = {1, 2, 3, 4, 5, 6, 8};
	
	InitList(&l, initD, 6);
	PrintList(l);
	printf("\n");
	
	printf("LinkList Length = %d\n", Length(l));
	
	
	printf("insert 8 in (3)\n");
	ListInsert(l, 3, 8);
	PrintList(l);
	printf("\n");
	
	printf("delete (3)\n");
	ListDelete(l, 3);
	PrintList(l);
	printf("\n");
	
	return 0;
}