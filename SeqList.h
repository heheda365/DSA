#ifndef __SEQLIST_H__
#define __SEQLIST_H__
typedef int bool;
#define NULL (void *) 0

#define true 1
#define false 0

#define INIT_SIZE 		100
typedef char ElemType;
typedef struct{
	ElemType * data;
	int length;
	int maxSize;
} SeqList;

bool InitList(SeqList * l);
int Length(SeqList * l);
int localeElem(SeqList * l, ElemType e);
ElemType GetElem(SeqList * l, int i);
bool ListInsert(SeqList *l, int i, ElemType e);
bool ListDelete(SeqList * l, int i);
void PrintList(SeqList * l);
bool Empty(SeqList * l);
bool DestoryList(SeqList * l);

#endif

