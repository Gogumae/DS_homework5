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
/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
lparen = 0, /* ( 왼쪽 괄호 */
rparen = 9, /* ) 오른쪽 괄호*/
times = 7, /* * 곱셈 */
divide = 6, /* / 나눗셈 */
plus = 5, /* + 덧셈 */
minus = 4, /* - 뺄셈 */
operand = 1 /* 피연산자 */
} precedence;
char infixExp[MAX_EXPRESSION_SIZE]; /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE]; /* postfix로 변환을 위해 필요한 스택*/
int evalStack[MAX_STACK_SIZE]; /* 계산을 위해 필요한 스택 */
int postfixStackTop = -1; /* postfixStack용 top */
int evalStackTop = -1; /* evalStack용 top */
int evalResult = 0; /* 계산 결과를 저장 */
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
printf(" [----- [이찬희] [2019068057] -----]\n");
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
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
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
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
/* infix 문자열의 문자 하나씩을 읽기위한 포인터 */
char *exp = infixExp;
char x; /* 문자하나를 임시로 저장하기 위한 변수 */
/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
while(*exp != '\0')  //infix 문자열의 문자가 NULL이 아닐때까지 (끝나기 전까지)
{
    if(getPriority(*exp) == operand)  //operand가 들어오면
    {
       x = *exp;
       charCat(&x);  //postfix 문자열에 그대로 전달
    }
    else if(getPriority(*exp) == lparen) // ( 가 들어오면
    {
        postfixPush(*exp);  //postfix 스택에 전달
    }
    else if(getPriority(*exp) == rparen)  // ) 가 들어오면
    {
        while((x = postfixPop()) != '(') {  //postfix 스택에서 ( 이 팝 될때까지
        charCat(&x);  //postfix 문자열에 계속 전달
       }
    }
    else  //그 외
    {
      while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))  //스택 Top에 있는 것보다 입력된 문자가 우선도가 높아질 때 까지
        {
          x = postfixPop();  //postfix 스택에서 팝해서 postfix 문자열에 전달
          charCat(&x);
        }
    postfixPush(*exp);  //postfix 스택에 푸시
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
int length = strlen(postfixExp);  //postfix 문자열의 길이
char symbol;
evalStackTop = -1;  //계산용 스택 Top
for(i = 0; i < length; i++)  //postfix 문자열의 길이만큼
{
symbol = postfixExp[i];
if(getToken(symbol) == operand) {  //postfix 문자열에서 읽은 문자가 operand이면
evalPush(symbol - '0');  //계산용 스택에 푸시 (숫자)
}
else {  //아니면 (부호)
opr2 = evalPop();  //operand를 팝해서 opr2에 저장
opr1 = evalPop();  //operand를 팝해서 opr1에 저장
switch(getToken(symbol)) {  //symbol이 무엇이냐에 따라 연산해서 계산용 스택에 푸시
case plus: evalPush(opr1 + opr2); break;
case minus: evalPush(opr1 - opr2); break;
case times: evalPush(opr1 * opr2); break;
case divide: evalPush(opr1 / opr2); break;
default: break;
}
}
}
evalResult = evalPop();  //결과를 팝
}