#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
typedef struct bitnode {
	int data;
	struct bitnode* lchild;
	struct bitnode* rchild;
}bitnode, * bitree;   //二叉树结点
bitree T;  //树根
typedef struct LNode {
	bitnode* elem;
	struct LNode* next;
}LNode, * queueptr;   //存放二叉树结点的队
typedef struct {
	queueptr front;
	queueptr rear;
}Linkqueue;      //队头和队尾
int pos = 0;
int ord[20000] = { 0 };
int num(char a[]) {
	int result;
	result = 0;
	pos++;
	while (*(a + pos) >= '0' && *(a + pos) <= '9') {
		result = result * 10 - '0' + *(a + pos);
		pos++;
	}
	pos++;
	return result;
}   //存数
void create(char a[], bitree* tr) {
	if (*(a + pos + 1) == '{') {
		pos++;
		(*tr)->lchild = (bitnode*)malloc(sizeof(bitnode));
		(*tr)->lchild->data = 0;
		(*tr)->lchild->lchild = NULL;
		(*tr)->lchild->rchild = NULL;
		create(a, &((*tr)->lchild));
		(*tr)->data = num(a);
		(*tr)->rchild = (bitnode*)malloc(sizeof(bitnode));
		(*tr)->rchild->data = 0;
		(*tr)->rchild->lchild = NULL;
		(*tr)->rchild->rchild = NULL;
		create(a, &((*tr)->rchild));
	}
	else {
		tr = NULL;
		pos++;
		while (*(a + pos) == '}') {
			pos++;
		}
	}
}
void preorder(bitree t) {
	if (t != NULL && t->data!=0) {
		ord[pos] = t->data;
		pos++;
		preorder(t->lchild);
		preorder(t->rchild);
	}
	else {
		return;
	}
}
void printord(int ord[]) {
	int i = 0;
	while (ord[i + 1] != 0) {
		printf("%d,", ord[i]);
		i++;
	}
	printf("%d\n", ord[i]);
}
void initqueue(Linkqueue* q) {
	(*q).front = (*q).rear = (LNode*)malloc(sizeof(LNode));
	(*q).front->next = NULL;
}
void enqueue(Linkqueue* q, bitnode* e) {
	LNode* p;
	p = (LNode*)malloc(sizeof(LNode));
	p->elem = e;
	p->next = NULL;
	(*q).rear->next = p;
	(*q).rear = p;
}
int dequeue(Linkqueue* q, bitnode** e) {
	LNode* p;
	if ((*q).front == (*q).rear)return 0;
	p = (*q).front->next;
	(*q).front->next = p->next;
	(*e) = p->elem;
	if ((*q).rear == p)(*q).rear = (*q).front;
	free(p);
	return 1;
}
int emptyqueue(Linkqueue q) {
	if (q.front == q.rear) {
		return 0;
	}
	else {
		return 1;
	}
}
void layertravel(bitree t) {
	bitnode* p;
	Linkqueue Q;
	initqueue(&Q);
	if (t != NULL&& t->data!=0) {
		enqueue(&Q, t);
	}
	while (emptyqueue(Q) == 1) {
		dequeue(&Q, &p);
		ord[pos] = p->data;
		pos++;
		if (p->lchild != NULL && p->lchild->data != 0) {
			enqueue(&Q, p->lchild);
		}
		if (p->rchild != NULL&& p->rchild->data != 0) {
			enqueue(&Q, p->rchild);
		}
	}
}
void cal(bitree t, int level[], int lev) {
	if (t != NULL && t->data != 0) {
		lev++;
		level[lev]++;
		cal(t->lchild, level, lev);
		cal(t->rchild, level, lev);
	}
}
void back(int level[]) {
	int i = 1;
	int num = 0;
	int tol = 0;
	while (level[i] != 0) {
		if (level[i] >= tol) {
			tol = level[i];
			num = i;
		}
		i++;
	}
	printf("%d\n", num);
	printf("%d\n", tol);
}
int depth(bitree t) {
	int hl, hr;
	if (t == NULL ||t->data == 0) {
		return 0;
	}
	else {
		hl = depth(t->lchild);
		hr = depth(t->rchild);
		return(hl > hr ? hl + 1 : hr + 1);
	}
}
int main() {
	char a[100010];
	int level[10000] = { 0 };
	int lev = 0;
	int dep, t;
	bitnode* p;
	gets(a);
	T = (bitnode*)malloc(sizeof(bitnode));
	T->data = 0;
	T->lchild = NULL;
	T->rchild = NULL;
	create(a, &T);
	pos = 0;
	preorder(T);
	printord(ord);
	for (t = 0;t < 20000;t++) ord[t] = 0;
	pos = 0;
	layertravel(T);
	printord(ord);
	cal(T, level, lev);
	back(level);
	dep = depth(T);
	printf("%d", dep);
	return 0;
}
