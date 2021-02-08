#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXSIZE 501
void HeapAdjustn(int n[], int s, int m);
int n[MAXSIZE] = { 0 };
int main() {
	int i, temp;
	for (i = 1;i < MAXSIZE ;i++) {
		scanf("%d,", &n[i]);
	}
	scanf("%d", &n[i]);
	for (i = (MAXSIZE-1) / 2;i >= 1;i--) {
		HeapAdjustn(n, i, MAXSIZE-1);
	}
	for (i = (MAXSIZE-1) ;i > 1;i--) {
		temp = n[i];n[i] = n[1];n[1] = temp;
		HeapAdjustn(n, 1, i-1);
	}
	printf("%d", n[1]);
	for (i = 2;i < MAXSIZE;i++) {
		printf(",%d", n[i]);
	}
}

void HeapAdjustn(int n[], int s, int m) {
	int rc = n[s], j, temp;
	for (j = 2 * s;j <=m ;j *= 2) {
		if (j < m && n[j] < n[j + 1])j++;
		if (rc > n[j]) break;
		n[s] = n[j];
		n[j] = rc;
		s = j;
	}
}