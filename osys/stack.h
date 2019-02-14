#ifndef _STACK_H_
#define _STACK_H_

#define SUCCESS 0
#define FAILURE 1
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

struct stackEl {
	char *data;
	struct stackEl *next;
};

//typedef struct queue_element queue_element;

struct Stack {
	struct stackEl *head;
	//size_t stackSize; //don't really need it  
};

extern struct Stack *stack_init(void);
extern char *stack_init_el(char *str);
extern bool stack_isempty (struct Stack *sta);
extern void push(struct Stack *sta, char *value);
extern char *top(struct Stack *sta);
extern void pop(struct Stack *sta);
extern void clear (struct Stack *sta);
extern void stack_show(struct Stack *theStack); 
extern void destroyStack(struct Stack **sta);

#endif /* _STACK_H */
