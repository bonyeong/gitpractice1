/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("-----소프트웨어 2019038021 구본영------");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if (*h != NULL)		//헤드 노드가 NULL이 아니면, freeList를 호출해 메모리를 해제
		freeList(*h);

	//헤드노드에 대한 메모리를 할당한다.
	headNode **temp = (headNode**)malloc(sizeof(headNode));

	//이중 포인터니 포인터 일 때를 한 번 더 할당한다.
	for (int i = 0; i < sizeof(headNode); i++)
		*(temp +i)= (headNode*)malloc(sizeof(headNode));

	(*temp)->first = NULL;
	*h = *temp;

	return 1;
}

int freeList(headNode* h) {	//동적할당 해제
	listNode *prev = NULL;
	listNode *node = h->first;

	//헤드 노드 다음 노드들을 할당하는 것을 반복
	while (node != NULL)
	{
		prev = node;
		node = node->rlink;
		free(prev);
	}

	//마지막으로 헤드노드 해제
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *temp;

	node->key = key;	//node에 key를 저장
	temp = h->first;	//temp에 헤드노드 저장

	while (temp->rlink != NULL)	//temp의 다음 노드가 NULL이면 중지
	{
		temp = temp->rlink;
	}

	node->rlink = temp->rlink;	//node의 다음 노드에 temp의 다음 노드를 넣고
	temp->rlink = node;	//temp에 다음 노드에 node를 연결한다.
	node->llink = temp;//node의 이전 노드가 temp임을 명시한다.

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode *node;
	listNode *prev = 0;

	node = h->first;

	while (node->rlink != NULL)	//node의 다음 노드가 NULL이면 중지
	{
		//node를 다음 노드로 취하기 위해 prev에 node 값을 넣는다.
		prev = node;
		node = node->rlink;
	}

	//이전 노드의 다음 노드에 현재 노드의 다음 노드를 넣고 현재 노드를 해제
	prev->rlink = node->rlink;
	free(node);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode));

	node ->key = key;

	node->rlink = h->first;	//노드의 다음 노드가 헤드 노드의 값을 얻고
	h->first = node;	//헤드 노드에 노드를 넣는다.

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode *node;
	node = h->first;

	h->first = node->rlink;	//헤드 노드에 노드의 다음 값을 넣고
	free(node);	//노드는 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode *node = h->first;
	listNode *prev= NULL;	//이전 노드
	listNode *temp =NULL;


	while (node != NULL)	//node가 NULL이면 중지
	{
		prev = temp;	//이전 노드에 temp를 넣고
		temp = node;	//temp에는 node를 넣는다
		node = node->rlink;	//node에 node의 다음노드를 넣고
		temp->rlink = prev;	//temp의 다음 노드에는 이전 노드를 넣는다
	}

	h->first = temp;	//temp가 헤드노드가 됨

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;

	if (h->first == NULL)	//헤드노드가 비어있으면
	{
		insertFirst(h, key);	//insertFirst를 호출해 맨 앞에 넣어줌
		return 0;
	}

	listNode *temp = h->first;
	listNode *prev = h->first;

	while (temp != NULL)	//헤드 노드가 NULL이 되면 중지
	{
		if (temp->key >= key)	//temp의 값이 key보다 크거나 같으면
		{
			if (temp == h->first)	//temp가 헤드 노드일 때
			{
				h->first = node;	//헤드 노드에 노드를 넣어주고
				node->rlink = temp;	//노드의 다음 노드에 temp를 연결
				temp->llink = node;	//temp의 이전 노드가 노드가 됨을 명시
			}
			else
			{
				node->rlink=temp;	//노드의 다음 노드에 temp를 넣어주고
				temp->llink = node;	//temp의 이전 노드가 노드가 됨을 명시한다.
				prev->rlink = node;	//원래 temp의 이전 노드의 다음 노드가 노드가 되도록 연결
				node->llink = prev;	//노드의 이전 노드가 prev임을 명시
			}
			return 0;
		}
		prev = temp;
		temp = temp->rlink;
	}

	//마지막에 연결
	prev->rlink = node;	//temp의 이전 노드의 다음 노드에 노드를 연결
	node->llink = prev;	//노드이 이전 노드가 prev임을 명시
	//노드의 다음 노드는 이미 NULL임으로 다른 연결이 필요 없음
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode *node = h->first;
	listNode *prev = NULL;

	//key값이 헤드 노드와 같을 때
	if (key == node->key)
	{
		deleteFirst(h);	//deleteFirst호출 후 삭제
		return 0;
	}

	while (node != NULL)	//노드가 NULL이되면 중지
	{
		if (node->key == key)	//노드의 값이 key와 같으면
		{
			prev->rlink = node->rlink;	//이전 노드의 다음 노드에 노드의 다음 노드를 연결하고
			node->rlink->llink = prev;	//노드의 다음 노드의 이전 노드가 prev임을 명시
			free(node);	//노드 해제
			return 0;
		}
		else
		{
			prev = node;	//이전 노드에 노드값을 넣는다
			node = node->rlink;	//노드에 노드의 다음 노드를 넣는다.
		}
	}
	return 0;
}


