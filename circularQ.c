/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  School of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("-------------------------------------------------------\n");
		printf(" [----- [이찬희] [2019068057] -----]\n");
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){   //front와 rear가 같으면 Queue가 비어있다는 뜻
		printf("Circular Queue is empty!");
		return 1;  //1을 리턴해서 deQueue 함수의 if문의 코드를 실행시킨다
	}
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
    if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {  //rear의 다음 칸이 front와 같으면 Queue가 꽉 차있다는 뜻
	printf("Circular Queue is full!");
	return 1;  //1을 리턴해서 enQueue 함수의 if문의 코드를 실행시킨다
	}
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) {  //Queue가 꽉 차있으면 새로 넣을 수 없다
        return;
    }
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;  //rear를 1칸 이동시킨다. rear의 범위는 0부터 3이기 때문에, rear에 1을 더해 4가 되면 0으로 만들기 위해 %연산을 한다
		cQ->queue[cQ->rear] = item;  //rear의 칸에 입력한 item을 넣는다
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) {  //Queue가 비어있으면 내용을 뺄 수 없다
        return;
    }
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;  //front를 1칸 이동시킨다. rear와 마찬가지로 %연산을 통해 범위 안에서 움직이게 한다
		*item = cQ->queue[cQ->front]; //item이 있던 주소에 front칸에 있던 내용을 넣는다
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
