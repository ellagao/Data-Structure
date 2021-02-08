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
	LinkList headp[10];   //��ʼͷָ������headp
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
	for (i = 0; i < 10; i++) { headp[i] = NULL; }   //��ʼ����ָ��ָ��NULL
	loop:
	fscanf_s(fp1, "%d", &oper);
	switch (oper)
	{
	case 0:fclose(fp1);
		fclose(fp2);
		exit(0);
		break;  //�ر��ļ�����������
	case 1:
		fscanf_s(fp1, "%d", &num);
		CreatePolyn(headp, num, fp1);
		break;  //����
	case 2:
		fscanf_s(fp1, "%d", &num);
		PrintPolyn(headp, num, fp2);
		break;  //��ʾ
	case 3:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		CopyPolyn(headp, num1, num2);
		break;  //����
	case 4:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		AddPolyn(headp, num1, num2, num3);
		break;  //���
	case 5:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		SubtractPolyn(headp, num1, num2, num3);
		break;  //���
	case 6:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		MultiPolyn(headp, num1, num2, num3);
		break;  //���
	case 7:
		fscanf_s(fp1, "%d", &num);
		fscanf_s(fp1, "%lf", &x );
		fprintf_s(fp2, "%.4lf\n", EvaluatePolyn(headp, num, x));
		break;  //��ֵ
	case 8:
		fscanf_s(fp1, "%d", &num);
		Destroy(headp, num);
		break;  //����
	case 9:
		fscanf_s(fp1, "%d", &num);
		ClearPolyn(headp, num);
		break;  //���
	case 10:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		Differential(headp, num1, num2);
		break;  //΢��
	case 11:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		IndefiniteIntegral(headp, num1, num2);
		break;  //��������
	case 12:
		fscanf_s(fp1, "%d", &num);
		fscanf_s(fp1, "%lf%lf", &x1, &x2);
		x=DefiniteIntegral(headp, num, x2, x1);
		fprintf_s(fp2, "%.4lf\n", x);
		break; //������ x1Ϊ�������ޣ�x2Ϊ��������
	case 13:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		GCDPolyn(headp, num1, num2, num3);
		break;  //�����Լʽ
	case 14:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		LCMPolyn(headp, num1, num2, num3);
		break;  //����С����ʽ
	case 15:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		QuotientsPolyn(headp, num1, num2, num3);
		break;  //����
	case 16:
		fscanf_s(fp1, "%d%d%d", &num1, &num2, &num3);
		ModPolyn(headp, num1, num2, num3);
		break;  //ȡģ
	case 17:
		fscanf_s(fp1, "%d%d", &num1, &num2);
		fscanf_s(fp1, "%d", &num); //����
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

int GetLength(LinkList L[], int num) {    //�������ȣ���ͷ��㣩
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
			}//ð�����򽻻������ڵ�
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
				cur->coef = (cur->coef) + (nex->coef);  //ϵ���ϲ���ǰһ��
				cur->next = nex->next;
				free(nex);                              //ɾ���ͷź�һ��
				nex = cur;                              //����
				cur = pre;
			}
			else {
				pre->next = nex->next;
				free(cur);
				free(nex);                              //ɾ���ͷ�����
				cur = pre;                              //����
				if (cur->next == NULL) break;
				nex = cur->next;
			}
		}	
		if (pre != cur) pre = cur;
		cur = nex;
		nex = nex->next;
		if (nex == NULL) return;
	}
	if (cur->exp == nex->exp) {                     //����������
		if (fabs((cur->coef) + (nex->coef)) > 1e-8) {
			cur->coef = (cur->coef) + (nex->coef);  //ϵ���ϲ���ǰһ��
			cur->next = NULL;
			free(nex);                              //ɾ���ͷź�һ��
		}
		else {
			pre->next = NULL;
			free(cur);
			free(nex);                              //ɾ���ͷ�����
		}
	}
	if ((*(L + num))->next == NULL) {   //�������ʽֻ��0�������(0,0)��㣻
		(*(L + num))->next = MakeNode(0, 0);
	}
}

void CreatePolyn(LinkList L[], int num, FILE *fp1) {
	double coef = 0; int exp, i = 0;
	LNode *p, *q;
	Destroy(L, num);
	(*(L + num)) = MakeNode(0, 0); //����ͷ���
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
	}//β�巨
	Rankdownexp(L , num);
	Combineexp(L , num);
	if ((*(L + num))->next == NULL) (*(L + num))->next = MakeNode(0, 0);
}

void PrintPolyn(LinkList L[], int num, FILE *fp2) {
	LNode *p;
	if (*(L+num) == NULL) { fprintf_s(fp2, "NULL\n"); return; }   //�����������NULL
	p = (*(L + num))->next;
	if (p == NULL) { fprintf_s(fp2, "0.0000\n"); return; }  //������ڵ�Ϊ�ձ����0
	//�����һ�����ϵ����������������ϵ��ǰ����������
	if (p->exp == 0) { 
		fprintf_s(fp2, "%.4lf\n", p->coef); 
		return;
	} //��һ��Ϊ������������X
	if (p->exp == 1) { 
		fprintf_s(fp2, "%.4lfx", p->coef); 
	} //��һ��Ϊһ��������ָ��
	else
	{
		fprintf_s(fp2, "%.4lfx^%d", p->coef, p->exp);
	}//��һ��������ڵ���2�����������ʽ
	if (p->next == NULL) {
		fprintf_s(fp2, "\n");
		return;
	}//���ֻ��һ�����֮��return;
	p = p->next;
	while (p->next != NULL) { //�������һ����㣬����X��ָ��������Ϊ0
		if (p->exp == 1) {                   //X��ָ��Ϊ1�������ָ��
			if (p->coef > -1e-8) {
				fprintf_s(fp2, "+%.4lfx", p->coef);
			}//���ϵ��Ϊ����ϵ��ǰ���ϼӺ�
			else
			{
				fprintf_s(fp2, "%.4lfx", p->coef);
			}//���ϵ��Ϊ����ֱ�����ϵ��
		}
		else{                           //X��ָ�����ڵ���2����������ʽ���
			if (p->coef > -1e-8) {
				fprintf_s(fp2, "+%.4lfx^%d", p->coef, p->exp);
			}//���ϵ��Ϊ����ϵ��ǰ���ϼӺ�
			else
			{
				fprintf_s(fp2, "%.4lfx^%d", p->coef, p->exp);
			}//���ϵ��Ϊ����ֱ�����ϵ��
		}
		p = p->next;
	}//��������һ�����������н��//X��ָ��Ϊ1�������ָ��
	if (p->exp == 0) {
		if (p->coef > -1e-8) {
			fprintf_s(fp2, "+%.4lf", p->coef);
		}//���ϵ��Ϊ����ϵ��ǰ���ϼӺ�
		else
		{
			fprintf_s(fp2, "%.4lf", p->coef);
		}//���ϵ��Ϊ����ֱ�����ϵ��
		fprintf_s(fp2, "\n");
		return;
	}
	if (p->exp == 1) {
		if (p->coef > -1e-8) {
			fprintf_s(fp2, "+%.4lfx", p->coef);
		}//���ϵ��Ϊ����ϵ��ǰ���ϼӺ�
		else
		{
			fprintf_s(fp2, "%.4lfx", p->coef);
		}//���ϵ��Ϊ����ֱ�����ϵ��
	}
	else {
		if (p->coef > -1e-8) {
			fprintf_s(fp2, "+%.4lfx^%d", p->coef, p->exp);
		}//���ϵ��Ϊ����ϵ��ǰ���ϼӺ�
		else
		{
			fprintf_s(fp2, "%.4lfx^%d", p->coef, p->exp);
		}//���ϵ��Ϊ����ֱ�����ϵ��
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

void AddPolyn(LinkList L[], int num1, int num2, int num3) {   //num1��num2Ϊ����������num3Ϊ��
	double coef; int exp;
	LNode *pointer1, *pointer2, *pointer3;//ָ�����������ָ��
	LinkList headsum;//���Ƶ�ͷָ��
	LNode *psum;//ָ���������ָ��
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	headsum = MakeNode(0, 0);
	psum = headsum;
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�headsum
		coef = pointer1->coef;
		exp = pointer1->exp;
		psum->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		psum = psum ->next;
	}
	while (pointer2 != NULL) {    //��num2����ʽ���Ƶ�headsum
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

void SubtractPolyn(LinkList L[],int num1, int num2, int num3) { //num1Ϊ��������num2Ϊ������num3Ϊ��
	double coef; int exp;
	LNode *pointer1, *pointer2, *pointer3;//ָ�����������ָ��
	LinkList headsum;//���Ƶ�ͷָ��
	LNode *psum;//ָ���������ָ��
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	headsum = MakeNode(0, 0);
	psum = headsum;
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�headsum
		coef = pointer1->coef;
		exp = pointer1->exp;
		psum->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		psum = psum->next;
	}
	while (pointer2 != NULL) {    //��num2����ʽ���Ƶ�headsum
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
	LNode *pointer1, *pointer2;//ָ�����������ָ��
	double coef; int exp;
	LinkList result;//���Ƶ�ͷָ��
	LNode *presult;//ָ���������ָ��
	pointer1 = (*(L + num1))->next;
	result = MakeNode(0, 0);
	presult = result;
	while (pointer1 != NULL && pointer1->exp != 0) {    //��������������һ�����ָ��Ϊ0
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
		while (pointer1 != NULL) {    //�������
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
		while (pointer1 != NULL) {    //�������
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
	while (pointer1 != NULL) {    //��num����ʽ���Ƶ�mid[0]
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

void MultiPolyn(LinkList L[], int num1, int num2, int num3) {  //num1,num2Ϊ������num3Ϊ����λ��
	double coef; int exp;
	LNode *pointer1, *pointer2, *pointer3;//ָ�����������ָ��
	LinkList headproduct;//�����ͷָ��
	LNode *pproduct;//ָ���������ָ��
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
	Destroy(L, num3);  //�ͷſռ�
	*(L + num3) = headproduct;
	Rankdownexp(L, num3);
	Combineexp(L, num3);
	if ((*(L + num3))->next == NULL) (*(L + num3))->next = MakeNode(0, 0);
}

void QuotientsPolyn(LinkList L[], int num1, int num2, int num3) { //num1Ϊ��������num2Ϊ������num3Ϊ��,��ȥģ
	double coef,coefmid; int exp,expmid;
	LinkList head1, head2, head3,headmid;//headmid�����м�������������������
	LinkList *head_mid;//ָ�������ĸ�ͷ����ָ��
	LNode *pointer1, *pointer2, *pointer3;
	LNode *p1, *p2, *p3, *mid;//mid�����м����
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	head1 = MakeNode(0, 0);
	head2 = MakeNode(0, 0);
	head3 = MakeNode(0, 0);
	p1 = head1;
	p2 = head2;
	p3 = head3;
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�head1
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //��num2����ʽ���Ƶ�head2
		coef = pointer2->coef;
		exp = pointer2->exp;
		p2->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		p2 = p2->next;
	}
	while (fabs((*(L + num1))->next->coef)>1e-8 && (*(L + num1))->next->exp >= head2->next->exp) {  //ֱ������ʽ����ߴ���С�ڳ�ʽʱ����ѭ��
		pointer1 = (*(L + num1))->next;
		p2 = head2->next;
		exp = ((*(L + num1))->next->exp) - (head2->next->exp);
		coef = ((*(L + num1))->next->coef) / (head2->next->coef);
		p3->next = MakeNode(coef, exp);  //head3�洢��
		p3 = p3->next;	
		coef = -coef;
		headmid = MakeNode(0, 0);//��headmidװͷ���
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
		}   //�ҵ�num1�е�β���
		pointer1->next = headmid->next;
		Rankdownexp(L,num1);
		Combineexp(L,num1);
	}
	if (head3->next == NULL) head3->next = MakeNode(0, 0);
	Destroy(L, num1);
	Destroy(L, num2);
	Destroy(L, num3); //�ͷſռ�
	(*(L + num1)) = head1;
	(*(L + num2)) = head2;
	(*(L + num3)) = head3;
}

void ModPolyn(LinkList L[], int num1, int num2, int num3) { //num1Ϊ��������num2Ϊ������num3Ϊģ,��ȥ��
	double coef, coefmid; int exp, expmid;
	LinkList head1, head2, head3, headmid;//headmid�����м�������������������
	LinkList *head_mid;//ָ�������ĸ�ͷ����ָ��
	LNode *pointer1, *pointer2, *pointer3;
	LNode *p1, *p2, *p3, *mid;//mid�����м����
	pointer1 = (*(L + num1))->next;
	pointer2 = (*(L + num2))->next;
	head1 = MakeNode(0, 0);
	head2 = MakeNode(0, 0);
	head3 = MakeNode(0, 0);
	p1 = head1;
	p2 = head2;
	p3 = head3;
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�head1
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //��num2����ʽ���Ƶ�head2
		coef = pointer2->coef;
		exp = pointer2->exp;
		p2->next = MakeNode(coef, exp);
		pointer2 = pointer2->next;
		p2 = p2->next;
	}
	while (fabs((*(L + num1))->next->coef)>1e-8 && (*(L + num1))->next->exp >= head2->next->exp) {  //ֱ������ʽ����ߴ���С�ڳ�ʽʱ����ѭ��
		pointer1 = (*(L + num1))->next;
		p2 = head2->next;
		exp = ((*(L + num1))->next->exp) - (head2->next->exp);
		coef = ((*(L + num1))->next->coef) / (head2->next->coef);
		p3->next = MakeNode(coef, exp);  //head3�洢��
		p3 = p3->next;
		coef = -coef;
		headmid = MakeNode(0, 0);//��headmidװͷ���
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
		}   //�ҵ�num1�е�β���
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
	*(mid + 2) = MakeNode(0, 0);  //mid[2]�洢��
	*(mid + 3) = MakeNode(0, 0);  //mid[3]�洢����
	p1 = *(mid);
	p2 = *(mid + 1);
	p3 = *(mid + 2);
	p4 = *(mid + 3);
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //��num2����ʽ���Ƶ�mid[1]
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
		(*(mid + 1)) = (*(mid + 3));   //��һ��ѭ���ı���ʽ�ͳ�ʽΪ��һ��ѭ���ĳ�ʽ����ʽ
		*(mid + 3) = MakeNode(0, 0);  //mid[3]�洢����
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
	*(mid + 2) = MakeNode(0, 0);  //mid[2]�洢��
	*(mid + 3) = MakeNode(0, 0);  //mid[3]�洢����
	p1 = *(mid);
	p2 = *(mid + 1);
	p3 = *(mid + 2);
	p4 = *(mid + 3);
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	while (pointer2 != NULL) {    //��num2����ʽ���Ƶ�mid[1]
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
	Destroy(mid, 2);   //�ͷſռ�
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
	while (pointer1 != NULL) {    //��num1����ʽ���Ƶ�mid[0]
		coef = pointer1->coef;
		exp = pointer1->exp;
		p1->next = MakeNode(coef, exp);
		pointer1 = pointer1->next;
		p1 = p1->next;
	}
	//��x��ʮ����ת��Ϊ������
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
		free(pre);  //��ȥ����ʽ���ͷſռ�
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
		if (b == '#') return('\0');  //����
		if (b == ')') return('=');
		else  return('<');
	case ')':
		if (b == '(') return('\0');  //����
		else  return('>');
	case '#':
		if (b == '#') return('=');
		if (b == ')') return('\0');  //����
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
		while (pointer != NULL) {    //��L[i]����ʽ���Ƶ�mid[i]
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
	}                    //Push ������
	else {
	loop2:
		ch2 = OPTRStack->ch; //GetTop OPTRSatck
		judge = precede(ch2, ch1);
		switch (judge)
		{
		case '<':
			ptr = MakeNodeOPTR(ch1);
			ptr->next = OPTRStack;
			OPTRStack = ptr;   //Push �����
			goto loop1;
		case '=':
			if (ch2 == '#') goto loop3;
			ptr = OPTRStack;
			OPTRStack = OPTRStack->next;
			free(ptr);   //������ Pop
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
			OPNDStack = pnd;  //Push ������
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
