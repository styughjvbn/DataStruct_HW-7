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

int deleteLast(headNode* h) {//���Ḯ��Ʈ�� ������ ��带 �����Ѵ�.
	if(h->first==NULL){//���Ḯ��Ʈ�� ����ٸ� �Լ��� �����Ѵ�.
		return 0;
	}
	else if(h->first->rlink==NULL){//���Ḯ��Ʈ�� ��尡 1�����̶��
		free(h->first);//ù��° ��带 ��������
		h->first=NULL;//���Ḯ��Ʈ�� ����ٴ°��� ǥ���Ѵ�.
	}
	else{//���Ḯ��Ʈ�� ��尡 2���̻��̶��
		h->first->llink=h->first->llink->llink;//ù��° ����� llink�� �׻� ��������带 ����Ű�Ƿ� ���� ���������(h->first->llink)�� �����(->llink)�� ����Ű���Ѵ�.
		free(h->first->llink->rlink);//���� ��������带 �����Ѵ�.
		h->first->llink->rlink=NULL;//���������(h->first->llink)�� rlink�� NULL�� �����.
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

int deleteFirst(headNode* h) {//���Ḯ��Ʈ�� ù��° ��带 �����Ѵ�.
	if(h->first==NULL){//���� ���Ḯ��Ʈ�� ����ٸ� �Լ��� �����Ѵ�.
		return 0;
	}
	else if(h->first->rlink==NULL){//���Ḯ��Ʈ�� ��尡 �Ѱ� ���̶��
		free(h->first);//ù��° ��带 �����ϰ�
		h->first=NULL;//���Ḯ��Ʈ�� ����ٴ� ���� ǥ���Ѵ�.
	}
	else{//���Ḯ��Ʈ�� 2���̻��� ��尡 �ִٸ�
		h->first->llink->rlink=h->first;//����������� rlink�� ������ ù��°����� �ּҸ� �ӽ÷� ����Ű���Ѵ�.
		h->first->rlink->llink=h->first->llink;//���Ḯ��Ʈ�� ù��° ���� �׻� ������ ��带 ����Ų��. ù��° ��尡 ������ �Ŀ� ù��° ��尡 �� �ι�° ����� llink�� ��������带 ����Ű�Ը����.
		h->first=h->first->rlink;//�ص��尡 �ι�° ��带 ����Ű�Ը����.
		free(h->first->llink->rlink);//��������带 �̿��Ͽ� ������ ù��° ��忡 �����Ͽ� �����Ѵ�.
		h->first->llink->rlink=NULL;//����������� rlink�� �ٽ� NULL�� �����.
	}

	return 0;
}
/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* fore=h->first;//�ռ� ��带 ����ϴ� �����ʹ�
	listNode* prev=NULL;////�� ��带 ����ϴ� �����ʹ�
	if(h->first==NULL||h->first->rlink==NULL)//���Ḯ��Ʈ�� ����ų� ��尡 �Ѱ���� �Լ��� �����Ѵ�.
		return 0;
	else{
		h->first->llink->llink=h->first;//����������� llink�� ù��°��带 ����Ű���Ѵ�. �������ġ�� �ȴٸ� ��������尡 ù��° ��尡 �ǰ� ù��° ��尡 ��������尡 �Ǳ⶧���̴�.
		h->first=h->first->llink;//�ص��尡 ������ ��带 ����Ű���Ѵ�. �������� �ٲ�� ��������尡 ù��° ��尡 �Ǳ⶧���̴�.
		while(fore->rlink!=NULL){//��������� ������ ������ ����� ��ũ�� �������� ���ġ�Ѵ�.
			prev=fore;//�ռ����� ���� ����带 �����Ѵ�.
			fore=fore->rlink;//�ռ� ���� �̵��Ѵ�.
			prev->rlink=prev->llink;//�� ����� rlink�� ���� ��带 ����Ű�� �Ѵ�.
			prev->llink=fore;//�� ����� llink�� �ռ���带 ����Ű���Ѵ�.
		}
		h->first->rlink=prev;//�������� �ٲ� ���Ḯ��Ʈ�� ù��°��尡 ������� ��ũ�� ���ġ�� ������ ù��°�� ����Ű���Ѵ�.
		h->first->llink->rlink=NULL;//�������� �ٲ� ���Ḯ��Ʈ�� ����������� rlink�� NULL�� �����.
	}
	return 0;
}

int insertNode(headNode* h, int key) {/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
	listNode* node=(listNode*)malloc(sizeof(listNode));//���Ե� ��� �Ҵ�
	listNode* search=h->first;//�� ������ Ű���� ���ϱ����� ������ search�� ù��° ��带 ����Ű���� �Ѵ�.
	node->key=key;//������ ��忡 �Է¹��� Ű���� �ִ´�.
	node->rlink=NULL;//�ϴ� ������ ����� rlink�� NULL�� �����.

	if(h->first==NULL){//���Ḯ��Ʈ�� ����ٸ� ó���� ��带 �����Ѵ�.
		node->llink=node;//llink�� ������ ���(�ڱ��ڽ�)�� ����Ų��
		h->first=node;//�ص���� �����Ѵ�.
	}
	else{//���Ḯ��Ʈ�� ��������ʴٸ�
		while(search){//���Ḯ��Ʈ�� ������ ������ ���غ���.
			if(search->key>key){//���� ����� Ű���� �Է¹��� Ű������ ũ�ٸ� ���� ����� �տ� �Ҵ���� ��带 �����Ѵ�.
				node->rlink=search;//������ ����� rlink�� ���� ��带 ����Ű���Ѵ�.
				node->llink=search->llink;//������ ����� llink�� ���� ����� llink�� ����Ű�� ���� ����Ű���Ѵ�. ���� ���� ��尡 ù��������� ��������带 ����ų�װ� �߰������ ������带 ����ų���̴�.
				if(search==h->first){//���� ���� ��尡 ù��° ����� �ص���� ������ ��带 �����ϰ�
					h->first=node;
				}
				else//�ƴ϶�� ���� ����� ������ ������ ��带 �����Ѵ�.
					search->llink->rlink=node;
				search->llink=node;//���� ����� llink�� ������ ��带 ����Ű���Ѵ�.
				return 0;//�������� �������� �Լ��� �����Ѵ�.
			}
			search=search->rlink;//���� ��尡 ������ ����� Ű������ �۴ٸ� ���� ��带 ���غ���.
		}//���Ḯ��Ʈ�� ���������� ������ ����� Ű������ ū ��带 �߰����� ���ߴٸ� �������� �Ҵ���� ��带 �����Ѵ�.
		node->llink=h->first->llink;//����� llink�� ������ ��������带 ����Ű�� �Ѵ�.
		h->first->llink->rlink=node;//��������尡 ������ ��带 ����Ű���Ѵ�.
		h->first->llink=node;//���Ḯ��Ʈ�� ù��° ��尡 ���ε��� ������ ��带 ����Ű���Ѵ�.
	}
	return 0;
}

int deleteNode(headNode* h, int key) {//list���� key�� ���� ��� ����
	listNode* search=h->first;//�� ������ Ű���� ���ϱ����� ������ search�� ù��° ��带 ����Ű���� �Ѵ�.

	if(h->first==NULL){//���Ḯ��Ʈ�� ����ٸ� �Լ��� �����Ѵ�.
		return 0;
	}
	else{
		while(search->rlink!=NULL){//���Ḯ��Ʈ�� ��������� ������ ���Ѵ�.
			if(search->key==key){//�Է¹��� key���� ������ ��带 ã�Ҵٸ�
				if(search==h->first){//ã�� ��尡 ù���� �����
					deleteFirst(h);//ù���� ��带 �����Ѵ�.
					return 0;
				}
				else{//ù���� ��尡 �ƴ϶��
					search->rlink->llink=search->llink;//ã�� ����� ���� ����� llink�� ã�� ����� ����带 ����Ű�� �ϰ�
					search->llink->rlink=search->rlink;//ã�� ����� �� ����� rlink�� ã�� ����� ������带 ����Ű�� �Ѵ�.
					free(search);//ã�� ��带 �����Ѵ�.
					return 0;
				}
			}
			search = search->rlink;//���� ��尡 �Է¹��� key�� �ٸ��ٸ� ���� ��带 ���Ѵ�.
		}
	}
	if(search->key==key){//����������� key���� �����Ϸ��� key�� ���ٸ� ��������带 �����Ѵ�.
		deleteLast(h);
	}
	return 1;
}


