#ifndef __BINTREE_H_
#define __BINTREE_H_

typedef int bool;
//#define NULL (void *) 0

#define true 1
#define false 0
typedef int ElemType;

typedef struct BiTNode{
	ElemType data;
	struct BiTNode * lchild, * rchild;
} BiTNode, * BiTree;

bool createBinTree(BiTree * binTree, ElemType seqBinTree[], int size);
#endif

