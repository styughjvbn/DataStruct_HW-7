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

int insertLast(headNode* h, int key) {//연결리스트의 마지막에 노드를 삽입한다.
	listNode* node=(listNode*)malloc(sizeof(listNode));//입력받은 key를 가질 노드를 할당받는다.
	node->key=key;//key값을 넣는다.
	node->rlink=NULL;//연결리스트의 마지막에 삽입되기 때문에 rlink는 NULL이다.

	if(h->first!=NULL){//연결리스트가 비어있지않다면 연결리스트의 마지막에 삽입한다.
		node->llink=h->first->llink;//할당받은 노드의 llink가 마지막노드를 가르키게한다. 첫번째 노드의 llink가 마지막 노드를 가르키고 있기때문에 h->first->llink로 접근한다.
		h->first->llink->rlink=node;//마지막노드의 rlink를 할당받은 노드를 가르키게한다.
		h->first->llink=node;//연결리스트의 첫번째노드가 새로들어온 마지막노드를 가르키게한다.
	}
	else{//비어있다면 해드노드와 연결한다.
		node->llink=node;//연결리스트의 첫번째 노드이며 유일한 노드이기 때문에 llink가 자기자신(마지막노드)을 가르킨다.
		h->first=node;//해드노드와 연결한다.
	}
	return 0;
}

int deleteLast(headNode* h) {//연결리스트의 마지막 노드를 삭제한다.
	if(h->first==NULL){//연결리스트가 비었다면 함수를 종료한다.
		return 0;
	}
	else if(h->first->rlink==NULL){//연결리스트의 노드가 1개뿐이라면
		free(h->first);//첫번째 노드를 해제한후
		h->first=NULL;//연결리스트가 비었다는것을 표시한다.
	}
	else{//연결리스트의 노드가 2개이상이라면
		h->first->llink=h->first->llink->llink;//첫번째 노드의 llink는 항상 마지막노드를 가르키므로 본래 마지막노드(h->first->llink)의 전노드(->llink)를 가르키게한다.
		free(h->first->llink->rlink);//본래 마지막노드를 해제한다.
		h->first->llink->rlink=NULL;//마지막노드(h->first->llink)의 rlink를 NULL로 만든다.
	}
	return 0;
}

int insertFirst(headNode* h, int key) {//연결리스트의 처음에 노드를 삽입한다.
	listNode* node=(listNode*)malloc(sizeof(listNode));//입력받은 key를 받을 노드를 할당받는다.
	node->key=key;//입력받은 key값을 할당받은 노드에 넣는다.

	if(h->first!=NULL){//연결리스트가 비어있지않다면 해드노드와 본래의 첫번째 노드사이에 할당받은 노드를 삽입한다.
		node->llink=h->first->llink;//첫번째 노드의 llink는 마지막 노드를 가르킨다. 떄문에 본래의 첫번째 노드가 가르키는 마지막 노드를 할당받은 노드의 llink가 가르키게한다.
		node->rlink=h->first;//할당받은 노드의 rlink를 연결리스트이 본래의 첫번째 노드를 가르키게한다.
		h->first->llink=node;//본래의 첫번째 노드의 llink가 할당받은 노드를 가르키게한다.
	}
	else{//연결리스트가 비어있다면 할당받은 노드가 마지막노드가 되므로
		node->rlink=NULL;//rlink를 NULL로 만들고
		node->llink=node;//llink를 자기자신(마지막노드)를 가르키게만든다.
	}
	h->first=node;//해드노드가 할당받은 노드를 가르키게한다.
	return 0;
}

int deleteFirst(headNode* h) {//연결리스트의 첫번째 노드를 삭제한다.
	if(h->first==NULL){//만약 연결리스트가 비었다면 함수를 종료한다.
		return 0;
	}
	else if(h->first->rlink==NULL){//연결리스트에 노드가 한개 뿐이라면
		free(h->first);//첫번째 노드를 해제하고
		h->first=NULL;//연결리스트가 비었다는 것을 표시한다.
	}
	else{//연결리스트에 2개이상의 노드가 있다면
		h->first->llink->rlink=h->first;//마지막노드의 rlink에 삭제할 첫번째노드의 주소를 임시로 가르키게한다.
		h->first->rlink->llink=h->first->llink;//연결리스트의 첫번째 노드는 항상 마지막 노드를 가르킨다. 첫번째 노드가 삭제된 후에 첫번째 노드가 될 두번째 노드의 llink가 마지막노드를 가르키게만든다.
		h->first=h->first->rlink;//해드노드가 두번째 노드를 가르키게만든다.
		free(h->first->llink->rlink);//마지막노드를 이용하여 삭제할 첫번째 노드에 접근하여 삭제한다.
		h->first->llink->rlink=NULL;//마지막노드의 rlink를 다시 NULL로 만든다.
	}

	return 0;
}
/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* fore=h->first;//앞선 노드를 기억하는 포인터다
	listNode* prev=NULL;////전 노드를 기억하는 포인터다
	if(h->first==NULL||h->first->rlink==NULL)//연결리스트가 비었거나 노드가 한개라면 함수를 종료한다.
		return 0;
	else{
		h->first->llink->llink=h->first;//마지막노드의 llink가 첫번째노드를 가르키게한다. 역순재배치가 된다면 마지막노드가 첫번째 노드가 되고 첫번째 노드가 마지막노드가 되기때문이다.
		h->first=h->first->llink;//해드노드가 마지막 노드를 가르키게한다. 역순으로 바뀌면 마지막노드가 첫번째 노드가 되기때문이다.
		while(fore->rlink!=NULL){//마지막노듣 제외한 나머지 노드의 링크를 역순으로 재배치한다.
			prev=fore;//앞선노드로 가기 전노드를 저장한다.
			fore=fore->rlink;//앞선 노드로 이동한다.
			prev->rlink=prev->llink;//전 노드의 rlink가 전전 노드를 가르키게 한다.
			prev->llink=fore;//전 노드의 llink가 앞선노드를 가르키게한다.
		}
		h->first->rlink=prev;//역순으로 바뀐 연결리스트의 첫번째노드가 각노드의 링크가 재배치된 노드들의 첫번째를 가르키게한다.
		h->first->llink->rlink=NULL;//역순으로 바뀐 연결리스트의 마지막노드의 rlink를 NULL로 만든다.
	}
	return 0;
}

int insertNode(headNode* h, int key) {/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
	listNode* node=(listNode*)malloc(sizeof(listNode));//삽입될 노드 할당
	listNode* search=h->first;//각 노드들의 키값을 비교하기위한 포인터 search가 첫번째 노드를 가르키도록 한다.
	node->key=key;//삽입할 노드에 입력받은 키값을 넣는다.
	node->rlink=NULL;//일단 삽입할 노드의 rlink를 NULL로 만든다.

	if(h->first==NULL){//연결리스트가 비었다면 처음에 노드를 삽입한다.
		node->llink=node;//llink는 마지막 노드(자기자신)를 가르킨다
		h->first=node;//해드노드와 연결한다.
	}
	else{//연결리스트가 비어있지않다면
		while(search){//연결리스트의 마지막 노드까지 비교해본다.
			if(search->key>key){//비교할 노드의 키값이 입력받은 키값보다 크다면 비교한 노드의 앞에 할당받은 노드를 삽입한다.
				node->rlink=search;//삽입할 노드의 rlink를 비교한 노드를 가르키게한다.
				node->llink=search->llink;//삽입할 노드의 llink를 비교한 노드의 llink가 가르키는 곳을 가르키게한다. 만약 비교한 노드가 첫번쨰노드라면 마지막노드를 가르킬테고 중간노드라면 이전노드를 가르킬것이다.
				if(search==h->first){//만약 비교한 노드가 첫번째 노드라면 해드노드와 삽입할 노드를 연결하고
					h->first=node;
				}
				else//아니라면 비교한 노드의 전노드와 삽입할 노드를 연결한다.
					search->llink->rlink=node;
				search->llink=node;//비교한 노드의 llink가 삽입한 노드를 가르키게한다.
				return 0;//노드삽입이 끝났으니 함수를 종료한다.
			}
			search=search->rlink;//비교한 노드가 삽입할 노드의 키값보다 작다면 다음 노드를 비교해본다.
		}//연결리스트의 마지막까지 삽입할 노드의 키값보다 큰 노드를 발견하지 못했다면 마지막에 할당받은 노드를 삽입한다.
		node->llink=h->first->llink;//노드의 llink가 원래의 마지막노드를 가르키게 한다.
		h->first->llink->rlink=node;//마지막노드가 삽입할 노드를 가르키게한다.
		h->first->llink=node;//연결리스트의 첫번째 노드가 새로들어온 마지막 노드를 가르키게한다.
	}
	return 0;
}

int deleteNode(headNode* h, int key) {//list에서 key에 대한 노드 삭제
	listNode* search=h->first;//각 노드들의 키값을 비교하기위한 포인터 search가 첫번째 노드를 가르키도록 한다.

	if(h->first==NULL){//연결리스트가 비었다면 함수를 종료한다.
		return 0;
	}
	else{
		while(search->rlink!=NULL){//연결리스트의 마지막노드 전까지 비교한다.
			if(search->key==key){//입력받은 key값을 가지는 노드를 찾았다면
				if(search==h->first){//찾은 노드가 첫번쨰 노드라면
					deleteFirst(h);//첫번쨰 노드를 삭제한다.
					return 0;
				}
				else{//첫번쨰 노드가 아니라면
					search->rlink->llink=search->llink;//찾은 노드의 다음 노드의 llink를 찾은 노드의 전노드를 가르키게 하고
					search->llink->rlink=search->rlink;//찾은 노드의 전 노드의 rlink를 찾은 노드의 다음노드를 가르키게 한다.
					free(search);//찾은 노드를 해제한다.
					return 0;
				}
			}
			search = search->rlink;//비교한 노드가 입력받은 key과 다르다면 다음 노드를 비교한다.
		}
	}
	if(search->key==key){//마지막노드의 key값이 삭제하려는 key과 같다면 마지막노드를 삭제한다.
		deleteLast(h);
	}
	return 1;
}


