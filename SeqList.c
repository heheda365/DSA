#include <stdio.h>
#include <malloc.h>
#include "SeqList.h"

// �������Ա�
bool InitList(SeqList * l){
	ElemType * tempP;
	tempP = (ElemType *) malloc(sizeof(ElemType) * INIT_SIZE);
	if(NULL != tempP){
		l->data = tempP;
	} else {
		return false;
	}
	
	// ��ʼ��Ϊ0
	l->length = 0; 
	// ��ʼ�������Ϊ�������
	l->maxSize = INIT_SIZE;

	return true;
}

int Length(SeqList * l){
	return l->length;
}


//
// �����Ա��� �� i��λ�ò��� e
//
bool ListInsert(SeqList *l, int i, ElemType e){
	ElemType * tempPN, * tempPO;
	int j = 0;
	if(i < 1 || l->length + 1 < i){
		return false;
	}
	// 
	// �����Ƿ���������������� ����һ��
	//
	if(l->length == l->maxSize){
		l->maxSize *= 2; 		// ��������
		tempPN = (ElemType *)malloc(sizeof(ElemType) * l->maxSize); 
		if(NULL != tempPN){
			tempPO = l->data;
			l->data = tempPN;
			
			for(j=0; j < l->length; j++){
				l->data[j] = tempPO[j];
			}
			free(tempPO);
		} else {
			return false;
		}
	}
	for(j = l->length; i <= j; j --){
		l->data[j] = l->data[j - 1];
	}
	l->data[i - 1] = e;
	l->length ++;
	
	return true;
}

//
// ��˳�����ɾ���� i��λ�õ�Ԫ��
//
bool ListDelete(SeqList * l, int i){
	int j = 0;
	if(i < 1 || l->length < i){
		return false;
	}
	for(j=i-1; j < l->length - 1; j ++){
		l->data[j] = l->data[j+1];
	}
	l->length --;
	return true;
}

//
//
// ��ӡ����Ԫ��
// ��ǰ�������� ElemType Ϊ char ������
void PrintList(SeqList * l){
	int i;
	for(i=0; i < l->length; i++){
		printf("%c  ", l->data[i]);
	}
}

//
// ˳���Ԫ�س�ʼ��
//
void InitListElem(SeqList * L, ElemType a[], int n){
	int i = 0;
	for(i=0; i<n; i++){
		L->data[i] = a[i];
	}
	L->length = n;
}
//
//
// ����Ԫ������
//
void ListElemInversion(SeqList * l){
	int i = 0;
	ElemType temp = 0;
	for(i=0; i < l->length / 2; i++){
		temp = l->data[i];
		l->data[i] = l->data[l->length - i - 1];
		l->data[l->length - i - 1] = temp;
	}
}
//
// ���������ɾ���ظ�Ԫ��
// 
void ListRemoveRepetition(SeqList * l){
	int i = 0;
	int j = 0;
	for(i=1; i < l->length; i++){
		if(l->data[i] != l->data[j]){
			l->data[++j] = l->data[i];
		} 
	}
	l->length = j + 1;
}
//
// �ϲ����������
// lc = la + lb
void merge2OrderedList(SeqList * la, SeqList * lb, SeqList * lc){
	int i = 0;
	int ia = 0, ib = 0;
	
	lc->length = la->length + lb->length;
	for(i=0; ia < la->length && ib < lb->length; i++){
		if(la->data[ia] < lb->data[ib]){
			lc->data[i] = la->data[ia];
			ia ++;
		} else {
			lc->data[i] = lb->data[ib];
			ib ++;
		}
	}
	if(ia < la->length){
		while(i < lc->length){
			lc->data[i++] = la->data[ia++];
		}
	} 
	if(ib < lb->length) {
		while(i < lc->length){
			lc->data[i++] = lb->data[ib++];
		}
	}
}
int main(void){
	SeqList l;
	SeqList la, lb, lc;
	char laInit[10] = {"0224466888"};
	char lbInit[10] = {"1335577999"};
	
	char a[10] = {"123336888"};		// ���г�ʼ��ʱ��Ԫ��
	
	InitList(& l);

	InitListElem(&l, a, sizeof(a));
	
	/////////////////////////////////////////////////////
	InitList(& la);
	InitListElem(&la, laInit, sizeof(laInit)-1);
	InitList(& lb);
	InitListElem(&lb, lbInit, sizeof(lbInit)-1);
	InitList(& lc);
	////////////////////////////////////////////////////

	printf("init data\n");
	PrintList(&l);
	printf("\n");
	

	printf("insert 'A' in (1)\n");
	ListInsert(&l, 1, 'A');
	PrintList(&l);
	printf("\n");
	
	printf("insert 'B' in (5)\n");
	ListInsert(&l, 5, 'B');
	PrintList(&l);
	printf("\n");
	
	printf("delete (5)\n");
	ListDelete(&l, 5);
	PrintList(&l);
	printf("\n");
	
	printf("Inversion \n");
	ListElemInversion(&l);
	PrintList(&l);
	printf("\n");
	
	printf("Remove Repetition \n");
	ListRemoveRepetition(&l);
	PrintList(&l);
	printf("\n");
	
	printf("merge to ordered list\n");
	merge2OrderedList(&la, &lb, &lc);
	PrintList(&lc);
	printf("\n");
	
	return 0;
}
