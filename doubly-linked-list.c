#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
/* A : �̹� ���α׷��� �ʱ�ȭ �Լ��� �ش���带 ���������ͷ� �ޱ⶧���� �Լ������� �ش���� ��ü�� ������ �� �ִ�.
 * ���������ͷ� ���� �ʰ� ���������ͷ� �޴´ٸ� ���ϰ��� �Ҵ���� ������ �ּҸ� ��������������� ���������ͷ� �޾ұ⶧����
 * �ּҰ��� ���������� �ʾƵ� �ȴ�.
 */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	printf("[----- [������] [2018038031] -----]");
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

int insertLast(headNode* h, int key) {//���Ḯ��Ʈ�� �������� ��带 �����Ѵ�.
	listNode* node=(listNode*)malloc(sizeof(listNode));//�Է¹��� key�� ���� ��带 �Ҵ�޴´�.
	node->key=key;//key���� �ִ´�.
	node->rlink=NULL;//���Ḯ��Ʈ�� �������� ���ԵǱ� ������ rlink�� NULL�̴�.

	if(h->first!=NULL){//���Ḯ��Ʈ�� ��������ʴٸ� ���Ḯ��Ʈ�� �������� �����Ѵ�.
		node->llink=h->first->llink;//�Ҵ���� ����� llink�� ��������带 ����Ű���Ѵ�. ù��° ����� llink�� ������ ��带 ����Ű�� �ֱ⶧���� h->first->llink�� �����Ѵ�.
		h->first->llink->rlink=node;//����������� rlink�� �Ҵ���� ��带 ����Ű���Ѵ�.
		h->first->llink=node;//���Ḯ��Ʈ�� ù��°��尡 ���ε��� ��������带 ����Ű���Ѵ�.
	}
	else{//����ִٸ� �ص���� �����Ѵ�.
		node->llink=node;//���Ḯ��Ʈ�� ù��° ����̸� ������ ����̱� ������ llink�� �ڱ��ڽ�(���������)�� ����Ų��.
		h->first=node;//�ص���� �����Ѵ�.
	}
	return 0;
}



/**
 * list�� ������ ��� ����
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

int insertFirst(headNode* h, int key) {//���Ḯ��Ʈ�� ó���� ��带 �����Ѵ�.
	listNode* node=(listNode*)malloc(sizeof(listNode));//�Է¹��� key�� ���� ��带 �Ҵ�޴´�.
	node->key=key;//�Է¹��� key���� �Ҵ���� ��忡 �ִ´�.

	if(h->first!=NULL){//���Ḯ��Ʈ�� ��������ʴٸ� �ص���� ������ ù��° �����̿� �Ҵ���� ��带 �����Ѵ�.
		node->llink=h->first->llink;//ù��° ����� llink�� ������ ��带 ����Ų��. ������ ������ ù��° ��尡 ����Ű�� ������ ��带 �Ҵ���� ����� llink�� ����Ű���Ѵ�.
		node->rlink=h->first;//�Ҵ���� ����� rlink�� ���Ḯ��Ʈ�� ������ ù��° ��带 ����Ű���Ѵ�.
		h->first->llink=node;//������ ù��° ����� llink�� �Ҵ���� ��带 ����Ű���Ѵ�.
	}
	else{//���Ḯ��Ʈ�� ����ִٸ� �Ҵ���� ��尡 ��������尡 �ǹǷ�
		node->rlink=NULL;//rlink�� NULL�� �����
		node->llink=node;//llink�� �ڱ��ڽ�(���������)�� ����Ű�Ը����.
	}
	h->first=node;//�ص��尡 �Ҵ���� ��带 ����Ű���Ѵ�.
	return 0;
}

/**
 * list�� ù��° ��� ����
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
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
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
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


