#include<stdio.h>
#include<string.h>
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
int yunsuan(int a, int b, char ch);

int main() {
	char str[50];
	int i = 0, result;
	gets(str);
	while (str[i] != '\0') {
		i++;
	}
	str[i++] = '#';
	str[i] = '\0';
	result=FourAO(str);
	printf_s("%d\n", result);
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
		if (b == '(' ) return('<');
		else return('>');
	case '/':
		if (b == '(') return('<');
		else return('>');
	case '(':
		if (b == '#') return('\0');  //´íÎó
		if (b == ')') return('=');
		else  return('<');
	case ')':
		if (b == '(') return('\0');  //´íÎó
		else  return('>');
	case '#':
		if (b == '#') return('=');
		if (b == ')') return('\0');  //´íÎó
		else  return('<');
	default:
		return('\0');
	}
}

int isOperator(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')' || a == '#') return(1);
	else return 0;
}

int FourAO(char *str) {
	OPTRhead OPTRStack;
	OPNDhead OPNDStack;
	int i = 0, a, b;
	char ch1, ch2, judge;
	OPTR *ptr;
	OPND *pnd;
	OPTRStack = MakeNodeOPTR('#');
	OPNDStack = NULL;         // Initialization
	loop1:
	ch1 = str[i++];
	if (ch1 == '#' && (OPTRStack->ch=='#')){
		return(OPNDStack->m);
	}
	if (!isOperator(ch1)) {
		pnd = MakeNodeOPND(ch1-'0');
		pnd->next = OPNDStack;
		OPNDStack = pnd;
		goto loop1;
	}                    //Push ²Ù×÷Êı
	else {
		loop2:
		ch2 = OPTRStack->ch; //GetTop OPTRSatck
		judge = precede(ch2, ch1);
		switch (judge)
		{
		case '<':
			ptr = MakeNodeOPTR(ch1);
			ptr->next = OPTRStack;
			OPTRStack = ptr;   //Push ÔËËã·û
			goto loop1;
		case '=':
			if(ch2=='#') return(OPNDStack->m);
			ptr = OPTRStack;
			OPTRStack = OPTRStack->next;
			free(ptr);   //ÍÑÀ¨ºÅ Pop
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
			a = yunsuan(a, b, ch2);
			pnd = MakeNodeOPND(a);
			pnd->next = OPNDStack;
			OPNDStack = pnd;  //Push ²Ù×÷Êı
			goto loop2;
		default:
			break;
		}
	}
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

int yunsuan(int a, int b, char ch) {
	switch (ch)
	{
	case '+':
		return(a + b);
	case '-':
		return(a - b);
	case '*':
		return(a * b);
	case '/':
		return(a / b);
	default:
		break;
	}
}
