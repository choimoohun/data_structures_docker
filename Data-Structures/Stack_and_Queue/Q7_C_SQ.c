//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct stack
{
	LinkedList ll;
} Stack; // You should not change the definition of stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int balanced(Stack *s, char *expression);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	char ch, str[256];
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Enter a string:\n");
	printf("2: Check whether expressions comprised of the characters ()[]{} is balanced:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Enter expressions without spaces to check whether it is balanced or not: ");
			scanf("%s", str);
			break;
        case 2:
            if(balanced(&s, str))
                printf("not balanced!\n");
            else
                printf("balanced!\n");
			// 끝나면 스택을 초기화
			removeAllItemsFromStack(&s);
			break;
		case 0:
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////
// main 함수에 이미 스택이 있길래 매개변수를 바꿨음
int balanced(Stack *s, char *expression)
{
	char *ptr = expression;

	// 문자열을 그대로 순회
	while (*ptr)
	{
		// 여는 괄호는 push
		if (*ptr == '(' || *ptr == '[' || *ptr == '{')
		{
			push(s, *ptr);
		}
		// 비어있지 않으면 짝을 검사
		else if (!isEmptyStack(s))
		{
			char open = peek(s);
			switch (*ptr)
			{
			case ')':
				if (open == '(') pop(s);
				else return -1;
				break;
			case ']':
				if (open == '[') pop(s);
				else return -1;
				break;
			case '}':
				if (open == '{') pop(s);
				else return -1;
				break;
			}
		}
		// 아무것도 만족 못하면 바로 탈출
		else
		{
			return -1;
		}
		ptr++;
	}
	
	return !isEmptyStack(s);
}

////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;

	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
