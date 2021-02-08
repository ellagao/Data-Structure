#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXSIZE 501
int n[MAXSIZE] = { 0 };
void ShellSortA(int n[]);
void ShellInsertB(int n[], int incr);
int main() {
	int i;
	for (i = 1;i < MAXSIZE - 1;i++) {
		scanf("%d,", &n[i]);
	}
	scanf("%d", &n[i]);
	ShellSortA(n);
	printf("%d", n[1]);
	for (i = 2;i < MAXSIZE;i++) {
		printf(",%d", n[i]);
	}
}

void ShellSortA(int n[]) {
	int i;
	for (i = MAXSIZE / 2;i >= 1;i /= 2) {
		ShellInsertB(n, i);
	}
}
void ShellInsertB(int n[], int incr) {
	int i, j;
	for (i = incr + 1;i < MAXSIZE;i++) {
		if (n[i] < n[i - incr]) {
			n[0] = n[i];
			for (j = i - incr;j > 0 && n[0] < n[j];j -= incr) n[j + incr] = n[j];
			n[j + incr] = n[0];
		}
	}
}