#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXSIZE 500
void Quicksort(int n[], int low, int high);
int Partion(int n[], int low, int high);
int n[MAXSIZE] = { 0 };
int main() {
	int i;
	for (i = 0;i < MAXSIZE-1;i++) {
		scanf("%d,", &n[i]);
	}
	scanf("%d", &n[i]);
	Quicksort(n,0,MAXSIZE-1);
	printf("%d", n[0]);
	for (i = 1;i < MAXSIZE;i++) {
		printf(",%d", n[i]);
	}
}

void Quicksort(int n[],int low,int high) {
	int pivotloc = 0;
	if (low < high) {
		pivotloc = Partion(n, low, high);
		Quicksort(n, low, pivotloc - 1);
		Quicksort(n, pivotloc + 1, high);
	}
}

int Partion(int n[], int low, int high) {
	int pivotkey = n[low];
	int i = low, temp;
	int j = high;
	while (i<j)
	{
		while (j > i&& n[j] >= pivotkey) {
			j--;
		}
		temp = n[i];n[i] = n[j];n[j] = temp;
		while (i < j&& n[i] <= pivotkey) {
			i++;
		}
		temp = n[i];n[i] = n[j];n[j] = temp;
	}
	return i;
}