#include "stack.h"

struct Stack *stack_init(void) {
	struct Stack *sta = malloc(sizeof *sta);
	if (sta) {    
		sta->head = NULL;
		//sta->stackSize = 0;
	}
	else {
		exit(1);
	}
	return sta;
}

char *stack_init_el(char *str) {
	char *tmp = malloc(strlen(str) + 1);
	if (tmp)
		strcpy(tmp, str);
	return tmp;
}

bool stack_isempty (struct Stack *sta) {
	return sta->head == NULL;
}

void push(struct Stack *sta, char *value) {
	struct stackEl *so = malloc(sizeof *so); 
	if (so) {
		char *tmp = malloc(strlen(value) + 1);
		if (tmp)
			strcpy(tmp, value);
		so->data = tmp;
		//so->data = stack_init_el(value);
		so->next = sta->head;
		sta->head = so;
		//sta->stackSize++;
	}
	else
	{
		// handle error here
	}
}

char *top(struct Stack *sta) {
	if (sta && sta->head)
		return sta->head->data;
	else
		return NULL;
}

void pop(struct Stack *sta) {
	if (sta->head != NULL) {
		struct stackEl *tmp = sta->head;
		sta->head = sta->head->next;
		free(tmp->data);
		free(tmp);
		//sta->stackSize--;
	}
}

void clear (struct Stack *sta) {
	while (sta->head != NULL)
		pop(sta);
}

void stack_show(struct Stack *theStack) {
    int count = 0;
    struct stackEl *temp;
 
    temp = theStack->head;

    while (temp != NULL) {
       printf(" %s\n",temp->data);
        temp = temp->next;
		count++;
    }
    printf("size of stack is %d \n",count);
}

void destroyStack(struct Stack **sta) {
  clear(*sta);
  free(*sta);
  *sta = NULL;
}
