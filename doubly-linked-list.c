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
/* A : 이번 프로그램의 초기화 함수는 해더노드를 이중포인터로 받기때문에 함수내에서 해더노드 자체를 변경할 수 있다.
 * 이중포인터로 받지 않고 단일포인터로 받는다면 리턴값을 할당받은 공간의 주소를 리턴해줘야하지만 이중포인터로 받았기때문에
 * 주소값을 리턴해주지 않아도 된다.
 */
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
	headNode* headnode=NULL;

	printf("[----- [서종원] [2018038031] -----]");
	do{
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
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
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

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	if (*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first;

	if (p==NULL){
		free(h);
		return 0;
	}
	while (p->rlink != NULL) {
		p = p->rlink;
		free(p->llink);
	}
	free(p);
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
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
	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;

	if(h!=NULL){
		node->rlink=NULL;
		h->first->llink->rlink=node;
		node->llink=h->first->llink;
	}
	else{
		node->rlink=NULL;
		node->llink=node;
		h->first=node;
	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h==NULL){
		return 0;
	}
	else if(h->first->rlink==NULL){
		free(h->first);
		h->first=NULL;
	}
	else{
		h->first->llink->llink->rlink=NULL;
		free(h->first->llink);
	}
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	if(h!=NULL){
		node->llink=h->first->llink;
		h->first->llink=node;
		node->rlink=h->first;
	}
	else{
		node->rlink=NULL;
		node->llink=node;
	}

	h->first=node;
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h==NULL){
		return 0;
	}
	else if(h->first->rlink==NULL){
		free(h->first);
		h->first=NULL;
	}
	else{
		h->first->rlink->llink=h->first->llink;
		h->first=h->first->rlink;
		free(h->first);
	}

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node=(listNode*)malloc(sizeof(listNode));
	listNode* search=h->first;
	node->key=key;
	node->rlink=NULL;

	if(h==NULL){
		node->llink=node;
		h->first=node;
	}
	else{
		while(search){
			if(search->key>key){
				node->rlink=search;
				node->llink=search->llink;
				search->llink->rlink=node;
				search->llink=node;
				if(h->first->rlink==NULL)
					h->first=node;
				return 0;
			}
			search=search->rlink;
		}
		h->first->llink->rlink=node;
		node->llink=h->first->llink;
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


