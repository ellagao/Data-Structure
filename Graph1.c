#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int AdjMatrix[1500][1500] = { 0 };     //初始邻接矩阵
int MidMatrix[1500][1500] = { 0 };     //中间过程矩阵
int vexs[1500] = { 0 };                //初始节点表
int midvexs[1500] = { 0 };             //中间节点表
int vexnum;                            //顶点数
int infectnum;                         //被感染节点数
int infect[1500] = { 0 };              //被感染节点表
int final[1500] = { 0 };               //最终被感染节点数
int count(int pos);
void DFSTraverse();
void DFS(int v);
int main() {
	int i = 0, j = 0, pos = 0, temp;
	int min, minpos;
	scanf("%d", &vexnum);
	for (i = 0;i < vexnum;i++) {
		for (j = 0;j < vexnum;j++) {
			scanf("%d", &AdjMatrix[i][j]);
		}
	}
	scanf("%d", &infectnum);
	for (i = 0;i < infectnum;i++) {
		scanf("%d", &pos);
		vexs[pos] = 1;   //该节点被感染，用1表示
		infect[i] = pos;
	}
	for (i = 0;i < infectnum-1;i++) {
		min = infect[i];
		minpos = i;
		for (j = i + 1;j < infectnum;j++) {
			if (infect[j] < min) {
				minpos = j;
				min = infect[j];
			}
		}
		if (minpos != i) {
			temp = infect[i];
			infect[i] = infect[minpos];
			infect[minpos] = temp;
		}
	}
	for (i = 0;i < infectnum;i++) {
		final[i] = count(infect[i]);
	}
	min = count(-1);
	minpos = -1;
	for (i = 0;i < infectnum;i++) {
		if (final[i] < min) {
			minpos = infect[i]; 
			min = final[i];
		}
	}
	printf("%d", minpos);
}

int count(int pos) {
	int i, j, sum;
	for (i = 0;i < 1500;i++) {
		for (j = 0;j < 1500;j++) {
			MidMatrix[i][j] = AdjMatrix[i][j];
		}
	}
	if (pos != -1){
		for (i = 0;i < 1500;i++) MidMatrix[pos][i] = 0;
		for (i = 0;i < 1500;i++) MidMatrix[i][pos] = 0;
		MidMatrix[pos][pos] = 1; //复制邻接矩阵
	}  //pos==-1表示原图
	for (i = 0;i < 1500;i++) midvexs[i] = vexs[i];
	DFSTraverse();
	sum = 0;
	for (i = 0;i < 1500;i++) {
		if (midvexs[i] == 1) sum = sum + 1;
	}
	return(sum);
}

void DFSTraverse() {
	int v = 0;
	for (v = 0;v < vexnum;v++) {
		if (midvexs[v] == 1) {
			DFS(v);
		}
	}
}

void DFS(int v) {
	int w;
	for (w = 0;w < vexnum;w++) {
		if (MidMatrix[v][w] != 0 && midvexs[w] == 0) {
			midvexs[w] = 1;
			DFS(w);
		}
	}
}