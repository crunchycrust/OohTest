#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

struct stack_entry {
  char *data;
  struct stack_entry *next;
};

struct stack_t
{
  struct stack_entry *head;
  size_t stackSize;  // not strictly necessary, but
                     // useful for logging
};

struct stack_t *newStack(void)
{
  struct stack_t *stack = malloc(sizeof *stack);
  if (stack)
  {
    stack->head = NULL;
    stack->stackSize = 0;
  }
  return stack;
}

char *copyString(char *str)
{
  char *tmp = malloc(strlen(str) + 1);
  if (tmp)
    strcpy(tmp, str);
  return tmp;
}

void push(struct stack_t *theStack, char *value)
{
  struct stack_entry *entry = malloc(sizeof *entry); 
  if (entry)
  {
    entry->data = copyString(value);
    entry->next = theStack->head;
    theStack->head = entry;
    theStack->stackSize++;
  }
  else
  {
    // handle error here
  }
}

char *top(struct stack_t *theStack)
{
  if (theStack && theStack->head)
    return theStack->head->data;
  else
    return NULL;
}

void pop(struct stack_t *theStack)
{
  if (theStack->head != NULL)
  {
    struct stack_entry *tmp = theStack->head;
    theStack->head = theStack->head->next;
    free(tmp->data);
    free(tmp);
    theStack->stackSize--;
  }
}

void clear (struct stack_t *theStack)
{
  while (theStack->head != NULL)
    pop(theStack);
}

void stack_show(struct stack_t *theStack) {
    int count = 0;
    struct stack_entry *temp;
 
    temp = theStack->head;

    while (temp != NULL) {
       printf(" %s\n",temp->data);
        temp = temp->next;
		count++;
    }
    printf("size of stack is %d \n",count);
}

void destroyStack(struct stack_t **theStack)
{
  clear(*theStack);
  free(*theStack);
  *theStack = NULL;
}

int main(void)
{
  struct stack_t *theStack = newStack();
  char *data;

  push(theStack, "foo");
  push(theStack, "bar");
  
  stack_show(theStack);
  // ...
  data = top(theStack);
  pop(theStack);
  // ...
  clear(theStack);
  destroyStack(&theStack);
  // ...
}


/*int main(void)
{
  struct stack_t myStack = {NULL, 0};
  push (&myStack, "this is a test");
  push (&myStack, "this is another test");
  
 
  clear(&myStack);
}*/
