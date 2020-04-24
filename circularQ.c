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
int isEmpty(QueueType *cQ);	//큐가 비었음을 확인
int isFull(QueueType *cQ);	//큐가 다 찼음을 확인
void enQueue(QueueType *cQ, element item);		//큐에 삽입
void deQueue(QueueType *cQ, element* item);	//큐에서 삭제
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();	//Q생성을 위한 호출
	element data;

	char command;

	printf("소프트웨어학과 2019038021 구본영");

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();	//원소 생성
			enQueue(cQ, data);	//큐에 삽입
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);	//삭제
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);	//디버그
			break;
		case 'q': case 'Q':
			freeQueue(cQ);	//동적할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));	//큐를 동적 할당한다
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()	//큐에 들어갈 원소 입력
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)	//큐가 다 비었음을 확인
{
	printf("다 비었음");
	return 0;
}

/* complete the function */
int isFull(QueueType *cQ)	//큐가 다 찼음을 확인
{
	printf("다 찼음");
	cQ->rear = MAX_QUEUE_SIZE-1;	//front와 rear가 겹치지 않도록 도와줌
	return 0;
}

/* complete the function */
void enQueue(QueueType *cQ, element item)	//큐에 원소 삽입
{
		cQ->rear = (cQ->rear + 1) % (MAX_QUEUE_SIZE);	//rear의 값을 한칸 뒤로 옮겨주고
		cQ->queue[cQ->rear] = item;	//그 자리에 새로운 원소를 넣는다.
		if (cQ->front == cQ->rear)	//front와 rear값이 같으면
			isFull(cQ);				//is Full호출
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)	//큐에 원소 삭제
{
	if (cQ->front == cQ->rear)	//front와 rear가 같으면
		isEmpty(cQ);			//isEmpty 호출

	cQ->queue[cQ->front] =0;	//front를 NULL값으로 바꿔주고
	cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	//front의 위치를 바꿔준다

}


void printQ(QueueType *cQ)	//큐 프린트
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)	//큐 디버그
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

int freeQueue(QueueType *cQ)	//큐 동적 해제
{
	if (cQ == NULL)
		return 1;

	free(cQ);
	return 0;
}
