#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <iostream>
#include<bitset>
unsigned int n[4096] = { 0 };
long long succeed = 0, fail = 0;
int sucnum = 0, failnum = 0;
void insert(unsigned a);
void index(unsigned a);
int Hash(unsigned a);


int main() {
	int i; unsigned a, b;
	for (i = 0;i < 10000;i++) {
		scanf("%d%d", &a, &b);
		if (b == 1)  insert(a);
		else index(a);
	}
	printf("%lld/%d\n", succeed, sucnum);
	printf("%lld/%d", fail, failnum);
}

void insert(unsigned a) {
	int p, up, hx, count=1;
	p = Hash(a);
	if (n[p] != 0 && n[p] != 0xffffffff) {
		if (a % 2 == 0) {
			hx = (a+1) % 4096;
		}
		else {
			hx = a % 4096;
		}  //计算增量
		while (n[p] != 0 && n[p] != 0xffffffff) {
			count++;
			p = (p + hx) % 4096;
		}
	}
	n[p] = a;
	printf("%d %d\n", count, p);
	return;
}

void index(unsigned a) {
	int p, up, hx, count = 1;
	p = Hash(a);
	if (n[p] != 0 && n[p] != a) {
		if (a % 2 == 0) {
			hx = (a+1) % 4096;
		}
		else {
			hx = a % 4096;
		}  //计算增量
		while (n[p] != 0 && n[p] != a) {
			count++;
			p = (p + hx) % 4096;
		}
	}
	if (n[p] == 0) { 
		printf("%d -1\n", count); 
		failnum++;
		fail = fail + count;
	}
	else {
		printf("%d %d\n", count, p);
		sucnum++;
		succeed = succeed + count;
		n[p] = 0xffffffff;
	}
	
}

int Hash(unsigned a) {
	unsigned long long t = 0;
	int p = 0;
	t = (unsigned long long)a * (unsigned long long)a;
	t = t >> 26;
	t = t % 4096;
	p = t;
	return p;
}