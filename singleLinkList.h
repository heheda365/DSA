#ifndef __SINGLELINKLIST_H
#define __SINGLELINKLIST_H

typedef int bool;
//#define NULL (void *) 0

#define true 1
#define false 0
typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

bool InitList(LinkList * l, ElemType initData[], int n);
int Length(LinkList l);
int localeElem(LinkList l, ElemType e);
ElemType GetElem(LinkList l, int i);
bool ListInsert(LinkList l, int i, ElemType e);
bool ListDelete(LinkList l, int i);
void PrintList(LinkList l);
bool Empty(LinkList l);
bool DestoryList(LinkList l);

#endif


