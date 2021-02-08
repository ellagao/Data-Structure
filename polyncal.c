#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
#include<string.h>
typedef struct LNode {
	double coef;
	int exp;
	struct LNode *next;
}LNode, *LinkList;
typedef struct OPTR {
	char ch;
	struct OPTR *next;
}OPTR, *OPTRhead;
typedef struct OPND {
	int m;
	struct OPND *next;
}OPND, *OPNDhead;
char precede(char a, char b);
int isOperator(char a);
OPTR *MakeNodeOPTR(char ch);
OPND *MakeNodeOPND(int m);
void yunsuan(LinkList L[], int a, int b, int num, char ch);
void PrintPolyn(LinkList L[], int num, FILE *fp2);
int GetLength(LinkList L[], int num);
LNode *MakeNode(double coef, int exp);
void Rankdownexp(LinkList L[], int num);
void Combineexp(LinkList L[], int num);
void CreatePolyn(LinkList L[], int num, FILE *fp1);
void CopyPolyn(LinkList L[],int num1, int num2);
void Destroy(LinkList L[], int num);
void ClearPolyn(LinkList L[],int num);
void AddPolyn(LinkList L[], int num1, int num2, int num3);
void SubtractPolyn(LinkList L[], int num1, int num2, int num3);
double EvaluatePolyn(LinkList L[], int num,double x);
double power(double x, int y);
void Differential(LinkList L[], int num1, int num2);
void IndefiniteIntegral(LinkList L[], int num1, int num2);
double DefiniteIntegral(LinkList L[], int num, double upperlimit, double lowerlimit);
void MultiPolyn(LinkList L[], int num1, int num2, int num3);
void QuotientsPolyn(LinkList L[], int num1, int num2, int num3);
void ModPolyn(LinkList L[], int num1, int num2, int num3);
void GCDPolyn(LinkList L[], int num1, int num2, int num3);
void LCMPolyn(LinkList L[], int num1, int num2, int num3);
void ExchangePolyn(LinkList L[], int num1, int num2);
void FastPowerPolyn(LinkList L[], int num1, int num2, int x);
void xishuguiyihua(LinkList L[], int num);
void FourAO(LinkList L[], char *str, int num);

int main() {
	int i = 0, oper = 0, num = 0, num1 = 0, num2 = 0, num3 = 0, j = 0 ; double sum = 0, x = 0, x1 = 0, x2 = 0;
	LinkList headp[10];   //初始头指针数组headp
	char str[50];
	char tr;
	FILE *fp1, *fp2;
	if ((fp1=fopen("polyn.in", "r")) == NULL) {
		printf_s("cannot open this file.\n");
		exit(0);
	}
	if ((fp2=fopen("polyn.out", "w+")) == NULL) {
		printf_s("cannot open this file.\n");
		exit(0);
	}
	for (i = 0; i < 10; i++) { headp[i] = NULL; }   //初始所有指针指向NULL
	loop:
	fscanf_s(fp1, "%d", &oper);
	switch (oper)
	{
	case 0:fclose(fp1);
		fclose(fp2);
		exit(0);
		break;  //关闭文件，结束程序
	case 1:
		fscanf_s(fp1, "%d", &num);
		CreatePolyn(headp, num, fp1);
		break;  //创建
	case 2:
		fscanf_s(fp1, "%d", &num);
		PrintPolyn(headp, num, fp2);
		break;  //显示
	case 3:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		CopyPolyn(headp, num1, num2);
		break;  //复制
	case 4:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		AddPolyn(headp, num1, num2, num3);
		break;  //求和
	case 5:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		SubtractPolyn(headp, num1, num2, num3);
		break;  //求差
	case 6:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		MultiPolyn(headp, num1, num2, num3);
		break;  //求积
	case 7:
		fscanf_s(fp1, "%d", &num);
		fscanf_s(fp1, "%lf", &x );
		fprintf_s(fp2, "%.4lf\n", EvaluatePolyn(headp, num, x));
		break;  //求值
	case 8:
		fscanf_s(fp1, "%d", &num);
		Destroy(headp, num);
		break;  //销毁
	case 9:
		fscanf_s(fp1, "%d", &num);
		ClearPolyn(headp, num);
		break;  //清空
	case 10:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		Differential(headp, num1, num2);
		break;  //微分
	case 11:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		IndefiniteIntegral(headp, num1, num2);
		break;  //不定积分
	case 12:
		fscanf_s(fp1, "%d", &num);
		fscanf_s(fp1, "%lf%lf", &x1, &x2);
		x=DefiniteIntegral(headp, num, x2, x1);
		fprintf_s(fp2, "%.4lf\n", x);
		break; //定积分 x1为积分下限，x2为积分上限
	case 13:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		GCDPolyn(headp, num1, num2, num3);
		break;  //求最大公约式
	case 14:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		LCMPolyn(headp, num1, num2, num3);
		break;  //求最小公倍式
	case 15:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		QuotientsPolyn(headp, num1, num2, num3);
		break;  //除法
	case 16:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		ModPolyn(headp, num1, num2, num3);
		break;  //取模
	case 17:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		fscanf_s(fp1, "%d", &num); //次数
		FastPowerPolyn(headp, num1, num2, num);
		break;
	case 18:
		fscanf_s(fp1, "%d", &num);
		fscanf_s(fp1, "%c", &tr);
		do
		{
			fscanf_s(fp1, "%c", &str[j]);
		} while (str[j++]!='\n');
		str[j - 1] = '#';
		str[j] = '\0';
		FourAO(headp, str, num);
		break;
	default:
		break; 
	}goto loop;	
}

int GetLength(LinkList L[], int num) {    //求链表长度（除头结点）
	LNode *pointer = *(L + num); int i = 0;
	while (pointer->next != NULL) {
		i++;
		pointer = pointer->next;
	}
	return(i);
}

LNode *MakeNode(double coef, int exp) {
	LNode *pointer;
	pointer = (LNode *)malloc(sizeof(LNode));
	pointer->coef = coef;
	pointer->exp = exp;
	pointer->next = NULL;
	return(pointer);
}

void Rankdownexp(LinkList L[], int num) {
	LNode *pre, *cur, *nex;
	int length = 0, i ,j;
	length = GetLength(L, num);
	if (length == 1) return;
	for (i = 1; i < length; i++) {
		pre = (*(L + num));
		cur = (*(L + num))->next;
		nex = cur->next;
		for (j = 1; j <= length - i; j++) {
			if (cur->exp < nex->exp) {
				pre->next = nex;
				cur->next = nex->next;
				nex->next = cur;
				cur = nex;
				nex = cur->next;
			}//冒泡排序交换两个节点
			pre = cur;
			cur = nex;
			nex = nex->next;
		}
	}
}

void Combineexp(LinkList L[], int num) {
	LNode *pre, *cur, *nex;
	pre = (*(L + num));
	cur = pre->next;
	while (cur != NULL) {
		if (fabs(cur->coef) < 1e-8) {
			pre->next = cur->next;
			free(cur);
			cur = pre->next;
		}
		else {
			pre = cur;
			cur = cur->next;
		}	
	}
	pre = (*(L + num));
	cur = pre->next;
	if (cur == NULL || cur->next == NULL)return;
	nex = cur->next;
	while (nex->next!= NULL) {
		if (cur->exp == nex->exp) {
			if (fabs((cur->coef) + (nex->coef)) > 1e-8) {
				cur->coef = (cur->coef) + (nex->coef);  //系数合并至前一项
				cur->next = nex->next;
				free(nex);                              //删除释放后一项
				nex = cur;                              //回退
				cur = pre;
			}
			else {
				pre->next = nex->next;
				free(cur);
				free(nex);                              //删除释放两项
				cur = pre;                              //回退
				if (cur->next == NULL) break;
				nex = cur->next;
			}
		}	
		if (pre != cur) pre = cur;
		cur = nex;
		nex = nex->next;
		if (nex == NULL) return;
	}
	if (cur->exp == nex->exp) {                     //最后两个结点
		if (fabs((cur->coef) + (nex->coef)) > 1e-8) {
			cur->coef = (cur->coef) + (nex->coef);  //系数合并至前一项
			cur->next = NULL;
			free(nex);                              //删除释放后一项
		}
		else {
			pre->next = NULL;
			free(cur);
			free(nex);                              //删除释放两项
		}
	}
	if ((*(L + num))->next == NULL) {   //如果多项式只有0，则添加(0,0)结点；
		(*(L + num))->next = MakeNode(0, 0);
	}
}

void CreatePolyn(LinkList L[], int num, FILE *fp1) {
	double coef = 0; int exp, i = 0;
	LNode *p, *q;
	Destroy(L, num);
	(*(L + num)) = MakeNode(0, 0); //插入头结点
	p = (*(L + num));
	fscanf_s(fp1, "%lf%d", &coef, &exp);
	while (fabs(coef) > 1e-8 || exp != 0) {
		if (fabs(coef) < 1e-8) {
			fscanf_s(fp1, "%lf%d", &coef, &exp);
			continue;
		}
		q = MakeNode(coef, exp);
		p->next = q;
		p = q;
        fscanf_s(fp1, "%lf%d", &coef, &exp); 
	}//尾插法
	Rankdownexp(L , num);
	Combineexp(L , num);
	if ((*(L + num))->next == NULL) (*(L + num))->next = MakeNode(0, 0);
}

void PrintPolyn(LinkList L[], int num, FILE *fp2) {
	LNode *p;
	if (*(L+num) == NULL) { fprintf_s(fp2, "NULL\n"); return; }   //链表不存在输出NULL
	p = (*(L + num))->next;
	if (p == NULL) { fprintf_s(fp2, "0.0000\n"); return; }  //链表存在但为空表输出0
	//输出第一项，无论系数正负，均不用在系数前加上正负号
	if (p->exp == 0) { 
		fprintf_s(fp2, "%.4lf\n", p->coef); 
		return;
	} //第一项为常数项，不用输出X
	if (p->exp == 1) { 
		fprintf_s(fp2, "%.4lfx", p->coef); 
	} //第一项为一次项，不输出指数
	else
	{
		fprintf_s(fp2, "%.4lfx^%d", p->coef, p->exp);
	}//第一项次数大于等于2，输出正常格式
	if (p->next == NULL) {
		fprintf_s(fp2, "\n");
		return;
	}//如果只有一项，换行之后return;
	p = p->next;
	while (p->next != NULL) { //不是最后一个结点，所以X的指数不可能为0
		if (p->exp == 1) {                   //X的指数为1，不输出指数
			if (p->coef > -1e-8) {
				fprintf_s(fp2, "+%.4lfx", p->coef);
			}//如果系数为正，系数前加上加号
			else
			{
				fprintf_s(fp2, "%.4lfx", p->coef);
			}//如果系数为负，直接输出系数
		}
		else{                           //X的指数大于等于2，按正常格式输出
			if (p->coef > -1e-8) {
				fprintf_s(fp2, "+%.4lfx^%d", p->coef, p->exp);
			}//如果系数为正，系数前加上加号
			else
			{
				fprintf_s(fp2, "%.4lfx^%d", p->coef, p->exp);
			}//如果系数为负，直接输出系数
		}
		p = p->next;
	}//输出除最后一个结点外的所有结点//X的指数为1，不输出指数
	if (p->exp == 0) {
		if (p->coef > -1e-8) {
			fprintf_s(fp2, "+%.4lf", p->coef);
		}//如果系数为正，系数前加上加号
		else
		{
			fprintf_s(fp2, "%.4lf", p->coef);
		}//如果系数为负，直接输出系数
		fprintf_s(fp2, "\n");
		return;
	}
	if (p->exp == 1) {
		if (p->coef > -1e-8) {
			fprintf_s(fp2, "+%.4lfx", p->coef);
		}//如果系数为正，系数前加上加号
		else
		{
			fprintf_s(fp2, "%.4lfx", p->coef);
		}//如果系数为负，直接输出系数
	}
	else {
		if (p->coef > -1e-8) {
			fprintf_s(fp2, "+%.4lfx^%d", p->coef, p->exp);
		}//如果系数为正，系数前加上加号
		else
		{
			fprintf_s(fp2, "%.4lfx^%d", p->coef, p->exp);
		}//如果系数为负，直接输出系数
	}
	fprintf_s(fp2, "\n");
	return;
}

void CopyPolyn(LinkList L[], int num1, int num2){
	double coef; int exp;
	LNode *pointer1, *pointer2;
	if (num1 == num2) return;
	else
	{
		Destroy(L, num2);
		(*(L + num2)) = MakeNode(0, 0);
		pointer2 = *(L + num2);
		pointer1 = (*(L + num1))->next;
		while (pointer1 != NULL) {
			coef = pointer1->coef;
			exp = pointer1->exp;
			pointer2->next = MakeNode(coef, exp);
			pointer1 = pointer1->next;
			pointer2 = pointer2->next;
		}
	}
}

void Destroy(LinkList L[],int num) {
	LNode *p, *q;
	if (*(L + num) == NULL) return;
	else
	{
		p = (*(L + num));
		while (p->next != NULL) {
			q = p->next;
			free(p);
			p = q;
		}
		free(p);
		(*(L + num)) = NULL;
		return;                           
	}
}

void ClearPolyn(LinkList L[],int num){
	LNode *pre, *cur;
	pre = (*(L + num))->next;
	while (pre->next != NULL) {
		cur = pre->next;
		free(pre);
		pre = cur;
		cur = pre->next;
	}

	free(pre);
	(*(L + num))->next = MakeNode(0, 0);
}

void AddPolyn(LinkList L[], int num1, int num2, int num3) {   //num1，num2为两个加数，num3为和
	double coef; int exp;
	LNode *pointer1, *pointer2, *pointer3;//指向链表数组的指针
	LinkList headsum;//复制的头指针
	LNode *psum;//指向复制链表的指针
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	headsum = MakeNode(0, 0);
	psum = headsum;
	while (pointer1 != NULL) {    //将num1多项式复制到headsum
		coef = pointer1->coef;
		exp = pointer1->exp;
		psum->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		psum = psum ->next;
	}
	while (pointer2 != NULL) {    //将num2多项式复制到headsum
		coef = pointer2->coef;
		exp = pointer2->exp;
		psum->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		psum = psum->next;
	}
	Destroy(L, num3);
	*(L + num3) = headsum;
	Rankdownexp(L, num3);
	Combineexp(L, num3);
}

void SubtractPolyn(LinkList L[],int num1, int num2, int num3) { //num1为被减数，num2为减数，num3为差
	double coef; int exp;
	LNode *pointer1, *pointer2, *pointer3;//指向链表数组的指针
	LinkList headsum;//复制的头指针
	LNode *psum;//指向复制链表的指针
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	headsum = MakeNode(0, 0);
	psum = headsum;
	while (pointer1 != NULL) {    //将num1多项式复制到headsum
		coef = pointer1->coef;
		exp = pointer1->exp;
		psum->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		psum = psum->next;
	}
	while (pointer2 != NULL) {    //将num2多项式复制到headsum
		coef = -(pointer2->coef);
		exp = pointer2->exp;
		psum->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		psum = psum->next;
	}
	Destroy(L, num3);
	*(L + num3) = headsum;
	Rankdownexp(L, num3);
	Combineexp(L, num3);
}

double EvaluatePolyn(LinkList L[], int num, double x) {
	LNode *p;
	double sum = 0;
	p = (*(L + num))->next;
	while (p != NULL) {
		sum = sum + (p->coef)*power(x, p->exp);
		p = p->next;
	}
	return(sum);
}

double power(double x, int y) {
	int i = 0; double pow=1.0;
	for (i = 0; i < y; i++) {
		pow = pow * x;
	}
	return(pow);
}

void Differential(LinkList L[], int num1, int num2) {
	LNode *pointer1, *pointer2;//指向链表数组的指针
	double coef; int exp;
	LinkList result;//复制的头指针
	LNode *presult;//指向复制链表的指针
	pointer1 = (*(L + num1))->next;
	result = MakeNode(0, 0);
	presult = result;
	while (pointer1 != NULL && pointer1->exp != 0) {    //链表结束或者最后一个结点指数为0
		coef = (pointer1->coef)*(pointer1->exp);
		exp = pointer1->exp - 1;
		presult->next = MakeNode(coef, exp);
		presult = presult->next;
		pointer1 = pointer1->next;
	}
	Destroy(L, num2);
	(*(L + num2)) = result;
	Rankdownexp(L, num2);
	Combineexp(L, num2);
}

void IndefiniteIntegral(LinkList L[], int num1, int num2) {
	LNode *pointer1, *pointer2;
	double coef; int exp;
	if (num1 == num2) {
		pointer1 = (*(L + num1))->next;
		while (pointer1 != NULL) {    //链表结束
			pointer1->coef = (1.0 / (pointer1->exp+1.0))*(pointer1->coef);
			pointer1->exp = pointer1->exp + 1;
			pointer1 = pointer1->next;
		}
	}
	else {
		Destroy(L, num2);
		pointer1 = (*(L + num1))->next;
		(*(L + num2)) = MakeNode(0, 0);
		pointer2 = (*(L + num2));
		while (pointer1 != NULL) {    //链表结束
			coef = (1.0/(pointer1->exp+1.0))*(pointer1->coef);
			exp = pointer1->exp + 1;
			pointer2->next = MakeNode(coef, exp);
			pointer2 = pointer2->next;
			pointer1 = pointer1->next;
		}
	}
	return;
}

double DefiniteIntegral(LinkList L[], int num, double upperlimit, double lowerlimit) {
	double sumup = 0, sumlow = 0;
	double coef; int exp;
	LinkList mid[1];
	LNode *pointer1, *p1;
	pointer1 = (*(L + num))->next;
	*(mid) = MakeNode(0, 0);
	p1 = (*(mid));
	while (pointer1 != NULL) {    //将num多项式复制到mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	IndefiniteIntegral(mid,0,0);
	sumup = EvaluatePolyn(mid, 0, upperlimit);
	sumlow = EvaluatePolyn(mid, 0, lowerlimit);
	Destroy(mid, 0);
	return(sumup - sumlow);
}

void MultiPolyn(LinkList L[], int num1, int num2, int num3) {  //num1,num2为乘数，num3为积的位置
	double coef; int exp;
	LNode *pointer1, *pointer2, *pointer3;//指向链表数组的指针
	LinkList headproduct;//结果的头指针
	LNode *pproduct;//指向结果链表的指针
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	headproduct = MakeNode(0, 0);
	pproduct = headproduct;
	while (pointer1 != NULL) {
		while (pointer2 != NULL) {
			coef = (pointer1->coef)*(pointer2->coef);
			exp = (pointer1->exp) + (pointer2->exp);
			pproduct->next = MakeNode(coef, exp);
			pproduct = pproduct->next;
			pointer2 = pointer2->next;
		}
		pointer2 = (*(L + num2))->next;
		pointer1 = pointer1->next;
	}
	Destroy(L, num3);  //释放空间
	*(L + num3) = headproduct;
	Rankdownexp(L, num3);
	Combineexp(L, num3);
	if ((*(L + num3))->next == NULL) (*(L + num3))->next = MakeNode(0, 0);
}

void QuotientsPolyn(LinkList L[], int num1, int num2, int num3) { //num1为被除数，num2为除数，num3为商,除去模
	double coef,coefmid; int exp,expmid;
	LinkList head1, head2, head3,headmid;//headmid代表中间过程中用于运算的链表
	LinkList *head_mid;//指向上面四个头结点的指针
	LNode *pointer1, *pointer2, *pointer3;
	LNode *p1, *p2, *p3, *mid;//mid代表中间过程
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	head1 = MakeNode(0, 0);
	head2 = MakeNode(0, 0);
	head3 = MakeNode(0, 0);
	p1 = head1;
	p2 = head2;
	p3 = head3;
	while (pointer1 != NULL) {    //将num1多项式复制到head1
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //将num2多项式复制到head2
		coef = pointer2->coef;
		exp = pointer2->exp;
		p2->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		p2 = p2->next;
	}
	while (fabs((*(L + num1))->next->coef)>1e-8 && (*(L + num1))->next->exp >= head2->next->exp) {  //直到被除式的最高次数小于除式时跳出循环
		pointer1 = (*(L + num1))->next;
		p2 = head2->next;
		exp = ((*(L + num1))->next->exp) - (head2->next->exp);
		coef = ((*(L + num1))->next->coef) / (head2->next->coef);
		p3->next = MakeNode(coef, exp);  //head3存储商
		p3 = p3->next;	
		coef = -coef;
		headmid = MakeNode(0, 0);//给headmid装头结点
		mid = headmid;
		while (p2 != NULL) {
			coefmid = coef * (p2->coef);
			expmid = exp + (p2->exp);
			mid->next = MakeNode(coefmid,expmid);
			p2 = p2 ->next;
			mid = mid->next;
		}
		while (pointer1->next != NULL) {
			pointer1 = pointer1->next;
		}   //找到num1列的尾结点
		pointer1->next = headmid->next;
		Rankdownexp(L,num1);
		Combineexp(L,num1);
	}
	if (head3->next == NULL) head3->next = MakeNode(0, 0);
	Destroy(L, num1);
	Destroy(L, num2);
	Destroy(L, num3); //释放空间
	(*(L + num1)) = head1;
	(*(L + num2)) = head2;
	(*(L + num3)) = head3;
}

void ModPolyn(LinkList L[], int num1, int num2, int num3) { //num1为被除数，num2为除数，num3为模,除去商
	double coef, coefmid; int exp, expmid;
	LinkList head1, head2, head3, headmid;//headmid代表中间过程中用于运算的链表
	LinkList *head_mid;//指向上面四个头结点的指针
	LNode *pointer1, *pointer2, *pointer3;
	LNode *p1, *p2, *p3, *mid;//mid代表中间过程
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	head1 = MakeNode(0, 0);
	head2 = MakeNode(0, 0);
	head3 = MakeNode(0, 0);
	p1 = head1;
	p2 = head2;
	p3 = head3;
	while (pointer1 != NULL) {    //将num1多项式复制到head1
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //将num2多项式复制到head2
		coef = pointer2->coef;
		exp = pointer2->exp;
		p2->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		p2 = p2->next;
	}
	while (fabs((*(L + num1))->next->coef)>1e-8 && (*(L + num1))->next->exp >= head2->next->exp) {  //直到被除式的最高次数小于除式时跳出循环
		pointer1 = (*(L + num1))->next;
		p2 = head2->next;
		exp = ((*(L + num1))->next->exp) - (head2->next->exp);
		coef = ((*(L + num1))->next->coef) / (head2->next->coef);
		p3->next = MakeNode(coef, exp);  //head3存储商
		p3 = p3->next;
		coef = -coef;
		headmid = MakeNode(0, 0);//给headmid装头结点
		mid = headmid;
		while (p2 != NULL) {
			coefmid = coef * (p2->coef);
			expmid = exp + (p2->exp);
			mid->next = MakeNode(coefmid, expmid);
			p2 = p2->next;
			mid = mid->next;
		}
		while (pointer1->next != NULL) {
			pointer1 = pointer1->next;
		}   //找到num1列的尾结点
		pointer1->next = headmid->next;
		Rankdownexp(L, num1);
		Combineexp(L, num1);
	}
	head3 = (*(L + num1));
	if (head3->next == NULL) head3->next = MakeNode(0, 0);
	(*(L + num1)) = head1;
	(*(L + num2)) = head2;
	(*(L + num3)) = head3;
}

void GCDPolyn(LinkList L[], int num1, int num2, int num3) {
	double coef; int exp;
	LinkList mid[4];
	LNode *pointer1, *pointer2, *pointer3;
	LNode *p1, *p2, *p3, *p4, *pre, *cur;
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	*(mid) = MakeNode(0, 0);
	*(mid + 1) = MakeNode(0, 0);
	*(mid + 2) = MakeNode(0, 0);  //mid[2]存储商
	*(mid + 3) = MakeNode(0, 0);  //mid[3]存储余数
	p1 = *(mid);
	p2 = *(mid + 1);
	p3 = *(mid + 2);
	p4 = *(mid + 3);
	while (pointer1 != NULL) {    //将num1多项式复制到mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //将num2多项式复制到mid[1]
		coef = pointer2->coef;
		exp = pointer2->exp;
		p2->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		p2 = p2->next;
	}
	xishuguiyihua(mid, 0);
	xishuguiyihua(mid, 1);
	ExchangePolyn(mid, 0, 1);
	QuotientsPolyn(mid, 0, 1, 2);
	ModPolyn(mid, 0, 1, 3);
	xishuguiyihua(mid, 2);
	xishuguiyihua(mid, 3);
	while(fabs((*(mid+3))->next->coef) >=1e-8){
		Destroy(mid, 0);
		(*(mid)) = (*(mid + 1));
		(*(mid + 1)) = (*(mid + 3));   //下一个循环的被除式和除式为上一个循环的除式和余式
		*(mid + 3) = MakeNode(0, 0);  //mid[3]存储余数
		p1 = *(mid);
		p2 = *(mid + 1);
		p3 = *(mid + 2);
		p4 = *(mid + 3);
		ExchangePolyn(mid, 0, 1);
		QuotientsPolyn(mid, 0, 1, 2);
		ModPolyn(mid, 0, 1, 3);
		xishuguiyihua(mid, 2);
		xishuguiyihua(mid, 3);
	}
	Destroy(L, num3);
	*(L + num3) = *(mid + 1);
	xishuguiyihua(L, num3);
	Destroy(mid, 0);
	Destroy(mid, 2);
	Destroy(mid, 3);
}

void LCMPolyn(LinkList L[], int num1, int num2, int num3) {
	double coef; int exp;
	LinkList mid[4];
	LNode *pointer1, *pointer2, *pointer3;
	LNode *p1, *p2, *p3, *p4, *pre, *cur;
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	*(mid) = MakeNode(0, 0);
	*(mid + 1) = MakeNode(0, 0);
	*(mid + 2) = MakeNode(0, 0);  //mid[2]存储商
	*(mid + 3) = MakeNode(0, 0);  //mid[3]存储余数
	p1 = *(mid);
	p2 = *(mid + 1);
	p3 = *(mid + 2);
	p4 = *(mid + 3);
	while (pointer1 != NULL) {    //将num1多项式复制到mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //将num2多项式复制到mid[1]
		coef = pointer2->coef;
		exp = pointer2->exp;
		p2->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		p2 = p2->next;
	}
	GCDPolyn(mid, 0, 1, 2);
	MultiPolyn(mid, 0, 1, 0);
	QuotientsPolyn(mid, 0, 2, 3);
	Destroy(L, num3);
	(*(L + num3)) = *(mid + 3);
	xishuguiyihua(L, num3);
	Destroy(mid, 0);
	Destroy(mid, 1);
	Destroy(mid, 2);   //释放空间
}

void ExchangePolyn(LinkList L[], int num1, int num2) {
	LNode *pointer1, *pointer2, *p1;
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	while (pointer2!=NULL) {
		if (pointer1->exp == pointer2->exp) {
			if (pointer1->coef < pointer2->coef) {
				p1 = *(L + num1);
				*(L + num1) = *(L + num2);
				*(L + num2) = p1;
				return;
			}
			if (pointer1->coef > pointer2->coef) {
				return;
			}
			if (pointer1->coef == pointer2->coef) {
				pointer1 = pointer1->next;
				pointer2 = pointer2->next;
				continue;
			}
		}
		if (pointer1->exp > pointer2->exp) {
			return;
		}
		if (pointer1->exp < pointer2->exp) {
			p1 = *(L + num1);
			*(L + num1) = *(L + num2);
			*(L + num2) = p1;
			return;
		}
	}
}

void FastPowerPolyn(LinkList L[], int num1, int num2, int x) {
	double coef; int exp, i = 0;
	int e[5];
	LinkList mid[6];
	LNode *pointer1, *pointer2;
	LNode *p1, *p2, *p3, *p4, *p5, *p6, *pre, *cur;
	pointer1 = (*(L + num1))->next;
	*(mid) = MakeNode(0, 0); //a^(2^0)
	*(mid + 1) = MakeNode(0, 0); //a^(2^1)
	*(mid + 2) = MakeNode(0, 0); //a^(2^2)
	*(mid + 3) = MakeNode(0, 0); //a^(2^3)
	*(mid + 4) = MakeNode(0, 0); //a^(2^4)
	*(mid + 5) = MakeNode(0, 0); 
	(*(mid + 5))->next = MakeNode(1, 0);  //product
	p1 = *(mid);
	p2 = *(mid + 1);
	p3 = *(mid + 2);
	p4 = *(mid + 3);
	p5 = *(mid + 4);
	p6 = *(mid + 5);
	while (pointer1 != NULL) {    //将num1多项式复制到mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	//将x从十进制转化为二进制
	while (i < 5) {
		e[i] = x % 2;
		x = x / 2;
		i = i + 1;
	}
	MultiPolyn(mid, 0, 0, 1);
	MultiPolyn(mid, 1, 1, 2);
	MultiPolyn(mid, 2, 2, 3);
	MultiPolyn(mid, 3, 3, 4);
	for (i = 0; i < 5; i++) {
		if (e[i] == 1) {
			MultiPolyn(mid, i, 5, 5);
		}
	}
	Destroy(L, num2);
	(*(L + num2)) = (*(mid + 5));
	for (i = 0; i < 5; i++) {
		pre = (*(mid + i));
		cur = pre->next;
		while (cur != NULL) {
			free(pre);
			pre = cur;
			cur = cur->next;
		}
		free(pre);  //消去被除式，释放空间
	}
}

void xishuguiyihua(LinkList L[], int num) {
	LNode *p;
	double coef = 0;
	if (*(L + num) == NULL) return;
	if ((*(L + num))->next == NULL) return;
	p = (*(L + num))->next;
	coef = p->coef;
	while (p != NULL) {
		p->coef = (p->coef) / coef;
		p = p->next;
	}
	return;
}

char precede(char a, char b) {
	switch (a)
	{
	case '+':
		if (b == '+' || b == '-' || b == '#' || b == ')') return('>');
		else return('<');
	case '-':
		if (b == '+' || b == '-' || b == '#' || b == ')') return('>');
		else return('<');
	case '*':
		if (b == '(') return('<');
		else return('>');
	case '/':
		if (b == '(') return('<');
		else return('>');
	case '(':
		if (b == '#') return('\0');  //错误
		if (b == ')') return('=');
		else  return('<');
	case ')':
		if (b == '(') return('\0');  //错误
		else  return('>');
	case '#':
		if (b == '#') return('=');
		if (b == ')') return('\0');  //错误
		else  return('<');
	default:
		return('\0');
	}
}

int isOperator(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')' || a == '#') return(1);
	else return 0;
}

void FourAO(LinkList L[], char *str, int num) {
	double coef; int exp;
	LinkList mid[11];
	LNode *pointer;
	LNode *p;
	OPTRhead OPTRStack;
	OPNDhead OPNDStack;
	int i = 0, a, b;
	char ch1, ch2, judge;
	OPTR *ptr;
	OPND *pnd;
	OPTRStack = MakeNodeOPTR('#');
	OPNDStack = NULL;         // Initialization
	for (i = 0; i < 10; i++) {
		if ((*(L + i)) == NULL) {
			(*(mid + i)) = NULL;
			continue;
		} 
		pointer = (*(L+i))->next;
		*(mid+i) = MakeNode(0, 0);
		p = *(mid+i);
		while (pointer != NULL) {    //将L[i]多项式复制到mid[i]
			coef = pointer->coef;
			exp = pointer->exp;
			p->next = MakeNode(coef, exp);
			pointer = pointer->next;
			p = p->next;

		}
	}
	*(mid + i) = MakeNode(0, 0);
	i = 0;
loop1:
	ch1 = str[i++];
	if (ch1 == '#' && (OPTRStack->ch == '#')) {
		return;
	}
	if (!isOperator(ch1)) {
		pnd = MakeNodeOPND(ch1 - '0');
		pnd->next = OPNDStack;
		OPNDStack = pnd;
		goto loop1;
	}                    //Push 操作数
	else {
	loop2:
		ch2 = OPTRStack->ch; //GetTop OPTRSatck
		judge = precede(ch2, ch1);
		switch (judge)
		{
		case '<':
			ptr = MakeNodeOPTR(ch1);
			ptr->next = OPTRStack;
			OPTRStack = ptr;   //Push 运算符
			goto loop1;
		case '=':
			if (ch2 == '#') goto loop3;
			ptr = OPTRStack;
			OPTRStack = OPTRStack->next;
			free(ptr);   //脱括号 Pop
			goto loop1;
		case '>':
			b = OPNDStack->m;
			pnd = OPNDStack;
			OPNDStack = OPNDStack->next;
			free(pnd);   //Pop(OPNDStack, b)
			a = OPNDStack->m;
			pnd = OPNDStack;
			OPNDStack = OPNDStack->next;
			free(pnd);   //Pop(OPNDStack, a)
			ptr = OPTRStack;
			OPTRStack = OPTRStack->next;
			free(ptr);   //Pop(OPTR,ch2)
			yunsuan(mid, a, b, 10, ch2);
			pnd = MakeNodeOPND(10);
			pnd->next = OPNDStack;
			OPNDStack = pnd;  //Push 操作数
			goto loop2;
		default:
			break;
		}
	}
loop3:
	Destroy(L, num);
	*(L + num) = *(mid + 10);
	for (i = 0; i < 10; i++) {
		Destroy(mid, i);
	}
	return;
}

OPTR *MakeNodeOPTR(char ch) {
	OPTR *p;
	p = (OPTR *)malloc(sizeof(OPTR));
	p->ch = ch;
	p->next = NULL;
	return(p);
}

OPND *MakeNodeOPND(int m) {
	OPND *p;
	p = (OPND *)malloc(sizeof(OPND));
	p->m = m;
	p->next = NULL;
	return(p);
}

void yunsuan(LinkList L[], int a, int b, int num, char ch) {
	switch (ch)
	{
	case '+':
		AddPolyn(L, a, b, num);
		return;
	case '-':
		SubtractPolyn(L, a, b, num);
		return;
	case '*':
		MultiPolyn(L, a, b, num);
		return;
	case '/':
		QuotientsPolyn(L, a, b, num);
		return;
	default:
		break;
	}
}
