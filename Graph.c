#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 200000000
	int arcs[9970][9970];   //初始邻接矩阵
	int vexnum;                            //顶点数
	int adjnum;                            //边数
	int S[9970];
	int D[9970];

int main() {
	int i, j, m, n, t, v, min, w, vj, k, max, maxpos;
	for (i = 0;i < 9970;i++) {
		for (j = 0;j < 9970;j++) {
			arcs[i][j] = MAX;
		}
		S[i] = 0;
		D[i] = MAX;
	}
	scanf("%d", &vexnum);
	scanf("%d", &adjnum);
	for (i = 0;i < adjnum;i++) {
		scanf("%d%d%d", &m, &n, &t);
		arcs[m][n] = t;
		arcs[n][m] = t;
	}
	for (v = 0;v < vexnum;v++) {
		D[v] = arcs[0][v];
	}
	D[0] = 0;
	S[0] = 1;
	for (i = 1;i < vexnum;i++) {
		min = MAX;
		for (w = 0;w < vexnum;w++) {
			if (S[w] == 0 && D[w] < min) {
				min = D[w];
				vj = w;
			}
		}
		S[vj] = 1;
		for (w = 0;w < vexnum;w++) {
			if (S[w] == 0 && (min + arcs[vj][w]) < D[w]) {
				D[w] = min + arcs[vj][w];
			}
		}
	}
	max = 0;
	maxpos = -1;
	for (i = 0;i < vexnum;i++) {
		if (D[i] > max) {
			max = D[i];
			maxpos = i;
		}
	}
	printf("%d\n", maxpos);
	printf("%d", max);
}