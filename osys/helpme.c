#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

struct stackEl {
	char *data;
	struct stackEl *next;
};

struct Stack {
	struct stackEl *head;
	//size_t stackSize; //don't really need it  
};

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

void menuen() {
	printf("0. menuen will be shown to du \n");
	printf("1. push an element \n");
	printf("2. pop an element \n");
	printf("3. clear stack \n");
	printf("4. check if stack is full \n");
	printf("5. count/display elements present in stack \n");
	printf("6. empty and destroy stack \n");
	printf("7. Print top of the stack \n");
	printf("8. exit \n");
	printf("Enter your choice \n");
}

int main(void) {
	struct Stack *theStack = stack_init();
	//char *data;
	int choice;
	
	printf("Enter 0 for menuen, please \n");
	
	while (1)    {
		printf("> ");
		scanf("%d",&choice);

		switch (choice) {
		case '\n':
			break;
		case 0:
			menuen();
			break;
		case -4:
			printf("Please, enter your string ");
			char *data;
			//fgets(data, 256, stdin);
			//data[strcspn(data, "\n")] = 0;
			scanf("%[^\n]255s", data);
			push(theStack, data); 
			
			break;    
        case 2:    
			pop(theStack);
            break;         
		case 3:    
            clear(theStack);
            break;                
		case 5:    
			stack_show(theStack);
			break;         
        case 6:    
          clear(theStack);
			destroyStack(&theStack);
           break;         
        /*case 7:    
            print_top();
            break;*/
        case 8:    
            exit(0);
        default:
            printf("wrong choice\n");    
        }
   }

	
	
/*  push(theStack, "foo");
  push(theStack, "bar");
  
  stack_show(theStack);
  // ...
  data = top(theStack);
  pop(theStack);
  // ...
  clear(theStack);
  destroyStack(&theStack);
  // ...8*/
}


/*int main(void)
{
  struct Stack myStack = {NULL, 0};
  push (&myStack, "this is a test");
  push (&myStack, "this is another test");
  
 
  clear(&myStack);
}*/
