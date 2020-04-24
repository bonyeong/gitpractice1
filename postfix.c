/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음*/
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호*/
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈*/
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)	//postfixStack에 값을 넣어주는 함수
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()	//postfixStack 값을 삭제하는 함수
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}


void evalPush(int x)	//evalStack에 값을 삽입하는 함수
{
	evalStack[++evalStackTop] = x;
}

int evalPop()	//evalStack에 값을 삭제하는 함수
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)	//받은 문자를 맞는 숫자로 return 해준다.
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)	//우선순위
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장한다.
 */
void toPostfix()	//중위표기를 후위 표기로 바꿔준다
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저n장하기 위한 변수 */
	precedence token;
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		token = getToken(*exp);	//문자열 분리

		x = *exp;

		if (token == operand)	//token이 피연산자이면
			charCat(&x);		//바로 처리

		else if (token == rparen)	//token이 오른쪽 괄호이면
		{
			while (postfixStack[postfixStackTop-1] != lparen)	//왼쪽 괄호 나오기 전까지 반복
			{
				x = postfixPop();	//x에 postfixPop에서 받은 반환값을 대입
				charCat(&x);
			}
			postfixPop();	//왼쪽 괄호를 없애주기 위해 한번 더 쓴다
		}
		else
		{
			if (postfixStackTop == -1)	//연산자를 첫번째 스택이 비었을 때 가장 먼저 넣어주기 위한 조건
				postfixPush(x);
			else
			{
				while (getPriority(postfixStack[postfixStackTop]) >= getPriority(x))	//우선 순위를 구하기 위한 조건
				{
					x = postfixPop();
					charCat(&x);
				}
				postfixPush(x);
			}
		}
		exp++;
	}

	while ((x = postfixPop()) != 0)
	{
		charCat(&x);
		postfixPop();
	}
	printf("\n");

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()	//후위표기로 값을 계산
{
	precedence token;
	char x;
	int op1, op2;
	char *p = postfixExp;

	while (p != NULL)
	{
		token = getToken(*p);
		x = *p;

		if (token == operand)
			evalPush(x - '0');
		else
		{
			op2 = evalPop();
			op1 = evalPop();

			switch (x)
			{
			case plus:
				evalPush(op1 + op2);
				break;
			case minus:
				evalPush(op1 - op2);
				break;
			case times:
				evalPush(op1*op2);
				break;
			case divide:
				evalPush(op1 / op2);
				break;
			}
		}
		p++;
	}
	evalResult = evalStack[evalStackTop];
}

int main()
{
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;
}


