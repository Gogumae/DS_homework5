/* postfix.c
 *
 * Data Structures, Homework #5
 * School of Computer Science at Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
lparen = 0, /* ( ���� ��ȣ */
rparen = 9, /* ) ������ ��ȣ*/
times = 7, /* * ���� */
divide = 6, /* / ������ */
plus = 5, /* + ���� */
minus = 4, /* - ���� */
operand = 1 /* �ǿ����� */
} precedence;
char infixExp[MAX_EXPRESSION_SIZE]; /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE]; /* postfix�� ��ȯ�� ���� �ʿ��� ����*/
int evalStack[MAX_STACK_SIZE]; /* ����� ���� �ʿ��� ���� */
int postfixStackTop = -1; /* postfixStack�� top */
int evalStackTop = -1; /* evalStack�� top */
int evalResult = 0; /* ��� ����� ���� */
void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
char command;
do{
printf("----------------------------------------------------------------\n");
printf(" [----- [������] [2019068057] -----]\n");
printf("----------------------------------------------------------------\n");
printf(" Infix to Postfix, then Evaluation\n");
printf("----------------------------------------------------------------\n");
printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q \n");
printf("----------------------------------------------------------------\n");
printf("Command = ");
scanf(" %c", &command);
switch(command) {
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
printf("\n >>>>> Concentration!! <<<<<\n");
break;
}
}while(command != 'q' && command != 'Q');
return 1;
}

void postfixPush(char x)
{
 postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
 char x;
 if(postfixStackTop == -1)
 return '\0';
 else {
 x = postfixStack[postfixStackTop--]; 
 }
 return x;
}

void evalPush(int x)
{
 evalStack[++evalStackTop] = x;
}

int evalPop()
{
 if(evalStackTop == -1)
 return -1;
 else
 return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
 printf("Type the expression >>> ");
 scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
switch(symbol) {
case '(' : return lparen;
case ')' : return rparen;
case '+' : return plus;
case '-' : return minus;
case '/' : return divide;
case '*' : return times;
default : return operand;
}
}

precedence getPriority(char x)
{
return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
if (postfixExp == '\0')
strncpy(postfixExp, c, 1);
else
strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
/* infix ���ڿ��� ���� �ϳ����� �б����� ������ */
char *exp = infixExp;
char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
while(*exp != '\0')  //infix ���ڿ��� ���ڰ� NULL�� �ƴҶ����� (������ ������)
{
    if(getPriority(*exp) == operand)  //operand�� ������
    {
       x = *exp;
       charCat(&x);  //postfix ���ڿ��� �״�� ����
    }
    else if(getPriority(*exp) == lparen) // ( �� ������
    {
        postfixPush(*exp);  //postfix ���ÿ� ����
    }
    else if(getPriority(*exp) == rparen)  // ) �� ������
    {
        while((x = postfixPop()) != '(') {  //postfix ���ÿ��� ( �� �� �ɶ�����
        charCat(&x);  //postfix ���ڿ��� ��� ����
       }
    }
    else  //�� ��
    {
      while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))  //���� Top�� �ִ� �ͺ��� �Էµ� ���ڰ� �켱���� ������ �� ����
        {
          x = postfixPop();  //postfix ���ÿ��� ���ؼ� postfix ���ڿ��� ����
          charCat(&x);
        }
    postfixPush(*exp);  //postfix ���ÿ� Ǫ��
    }
exp++;
}
 while(postfixStackTop != -1)
{
    x = postfixPop();
    charCat(&x);
}
}

void debug()
{
printf("\n---DEBUG\n");
printf("infixExp = %s\n", infixExp);
printf("postExp = %s\n", postfixExp);
printf("eval result = %d\n", evalResult);
printf("postfixStack : ");
for(int i = 0; i < MAX_STACK_SIZE; i++)
printf("%c ", postfixStack[i]);
printf("\n");
}

void reset()
{
infixExp[0] = '\0';
postfixExp[0] = '\0';
for(int i = 0; i < MAX_STACK_SIZE; i++)
postfixStack[i] = '\0';

postfixStackTop = -1;
evalStackTop = -1;
evalResult = 0;
}

void evaluation()
{
int opr1, opr2, i;
int length = strlen(postfixExp);  //postfix ���ڿ��� ����
char symbol;
evalStackTop = -1;  //���� ���� Top
for(i = 0; i < length; i++)  //postfix ���ڿ��� ���̸�ŭ
{
symbol = postfixExp[i];
if(getToken(symbol) == operand) {  //postfix ���ڿ����� ���� ���ڰ� operand�̸�
evalPush(symbol - '0');  //���� ���ÿ� Ǫ�� (����)
}
else {  //�ƴϸ� (��ȣ)
opr2 = evalPop();  //operand�� ���ؼ� opr2�� ����
opr1 = evalPop();  //operand�� ���ؼ� opr1�� ����
switch(getToken(symbol)) {  //symbol�� �����̳Ŀ� ���� �����ؼ� ���� ���ÿ� Ǫ��
case plus: evalPush(opr1 + opr2); break;
case minus: evalPush(opr1 - opr2); break;
case times: evalPush(opr1 * opr2); break;
case divide: evalPush(opr1 / opr2); break;
default: break;
}
}
}
evalResult = evalPop();  //����� ��
}