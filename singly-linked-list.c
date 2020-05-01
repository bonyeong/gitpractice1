#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);	//동적할당메모리 해제

int insertFirst(headNode* h, int key);	//list 맨 처음에 노드 추가
int insertNode(headNode* h, int key);	//노드 추가
int insertLast(headNode* h, int key);	//list 맨 마지막에 노드 추가

int deleteFirst(headNode* h);	//list 맨 처음 노드 삭제
int deleteNode(headNode* h, int key);	//노드 삭제
int deleteLast(headNode* h);	//list 맨 마지막 노드 삭제
int invertList(headNode* h);	//역순

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;	//헤드

	printf("-------- 소프트웨어학과 2019038021 구본영 ---------------");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* temp = (listNode*)malloc(sizeof(listNode));   //노드 임시 저장 위해 동적 할당
	listNode* node, *prev = NULL;   //헤드 저장할 포인터, 노드 이전값 저장할 포인터
	temp->key = key;   //입력받은 key temp노드의 데이터에 저장
	node = h->first;   // 헤드 저장


	if (node == NULL)   //헤드가 NULL이면
	{
		insertFirst(h, key);   //첫번째 노드에 저장
	}
	else
	{
		while (node != NULL)   //헤드가 NULL이 아니면
		{
			if (node->key < temp->key)   //node가 temp보다 작을 때
			{
				prev = node;   //이전 값에 node를 저장하고
				node = node->link;   //node를 node가 가리키고 있는 다음 값을 가게 한다
			}
			else if (node->key > temp->key)
			{
				temp->link = node;
				if (prev != NULL) {//prev가 NULL이 아니면
					prev->link = temp;
				}
				else {
					h->first = temp;
				}
				break;

			}
		}
		if (prev != NULL)   //prev가 NULL이 아니면
		{
			temp->link = node;   //temp의 다음에 node를 연결
			prev->link = temp;   //prev의 다음에 temp를 연결
		}
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node;
	listNode* temp = (listNode*)malloc(sizeof(listNode));

	temp->key = key;	//temp데이터 필드에 key 저장
	node = h->first;	//node에 헤드 저장

	while (node->link != NULL)	//node의 다음값이 NULL이 아닐 때까지 반복
	{
		node = node->link;	//node에 node의 다음을 넣어준다
	}

	temp->link = node->link;	//temp의 다음에 node의 다음 것(NULL)을 넣어준다.
	node->link = temp;	//node의 다음에 temp를 넣어준다.

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* node;
	node = h->first;	//헤드 저장

	h->first = node->link;	//헤드에 node의 다음 값을 가게 한다

	free(node);	//node 동적할당 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* node, *prev = 0;	//헤드저장, 노드 이전 값 저장
	node = h->first;	//node에 헤드 저장

	if (node->key == key)	//node의 데이터 값이 key와 같으면
	{
		deleteFirst(h);	//첫번째 노드를 삭제
	}
	else
	{
		while (node != NULL)	//node가 NULL이 아닌 동안 반복
		{
			if (node->key == key)	//node의 key 값이 key와 같으면
			{
				prev->link = node->link;	//prev가 가리키는 것을 node가 가리키는 것으로 바꿔줌

				free(node);	//node 동적할당 해제
				return 0;
			}
			else
			{
				prev = node;	//prev에 node를 미리 저장
				node = node->link;	//node에 node가 가리키는 걸 가져오게한다
			}
		}
		printf("찾을 수 없음\n");
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* node, *prev = NULL;	//헤드 저장, 노드 이전 값

	node = h->first;	//헤드 저장

	while (node->link != NULL)	//node가 가리키는 값이 NULL이 아닐 동안 반복
	{
		prev = node;	//node값을 prev에 미리 저장
		node = node->link;	//node를 node가 가리키는 값으로 바꿔줌
	}

	prev->link = node->link;	//prev가 가리키는 것을 node가 가리키는 것(NULL)으로 바꿔준다

	free(node);	//node 동적 할당 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* node;	//헤드 저장
	listNode *prev = NULL, *middle = NULL; // 역순 배치에 필요한 포인터
	node = h->first;	//헤드 저장

	while (node != NULL)	//node가 NULL이 아닐 때 동안 반복
	{
		prev = middle;	//prev에 middle을 저장
		middle = node;	//middle에 node를 저장
		node = node->link;	//node에 node가 가리키는 것을 넣어줌
		middle->link = prev;	//middle이 가리키는 것에 prev를 넣어줌
	}

	h->first = middle;	//헤드에 middle 값을 넣어줌

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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
