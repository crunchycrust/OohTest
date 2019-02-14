#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "stack.h"

void menuen() {
	printf("0. menuen will be shown to du \n");
	printf("1. push an element \n");
	printf("2. pop an element \n");
	printf("3. clear stack \n");
	printf("4. check if stack is full \n");
	printf("5. count/display elements present in stack \n");
	printf("6. destroy stack \n");
	//printf("7. Print top of the stack \n");
	printf("8. exit \n");
	printf("Enter your choice \n");
}

int main(void) {
	
	struct Stack (*stack_init)(void);//*stack_init(void);
	char (*stack_init_el)(char *str);
	bool (*stack_isempty) (struct Stack *sta);
	void (*push)(struct Stack *sta, char *value);
	char (*top) (struct Stack *sta);
	void (*pop)(struct Stack *sta);
	void (*clear) (struct Stack *sta);
	void (*stack_show) (struct Stack *theStack); 
	void (*destroyStack) (struct Stack **sta); 
	char *err;   

    void *libHandle;
    libHandle = dlopen("./libstack.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(FAILURE);
    }

    stack_init = dlsym(libHandle, "stack_init");
    stack_init_el = dlsym(libHandle, "stack_init_el");
    stack_isempty = dlsym(libHandle, "stack_isempty");
    push = dlsym(libHandle, "push");
    top = dlsym(libHandle, "top");
    pop = dlsym(libHandle, "pop");
    clear = dlsym(libHandle, "cleat");
    stack_show = dlsym(libHandle, "stack_show");
    destroyStack = dlsym(libHandle, "destroyStack");

    if(err = dlerror()) {
        fprintf(stderr, "%s\n", err);
        exit(FAILURE);
    }
    
    struct Stack *theStack = stack_init();
	//char *data;
	int choice = 0;
	
	printf("Enter 0 for menuen, please \n");
   
			
	while (scanf("%d", &choice) && choice )    {
		printf("> ");
		

		switch (choice) {
		case '\n':
			break;
		case 0:
			menuen();
			break;
		case 1:
			printf("Please, enter your string ");
			char *data;
			//fgets(data, 256, stdin);
			//data[strcspn(data, "\n")] = 0;
			scanf("%[^\n]255s", data);
			(*push) (theStack, data); 
			
			break;    
        case 2:    
			(*pop) (theStack);
            break;         
		case 3:    
            (*clear) (theStack);
            break;                
		case 5:    
			(*stack_show) (theStack);
			break;         
        case 6:
			(*destroyStack)(&theStack);
           break;         
        /*case 7:    
            print_top();
            break;*/
        case 8:
			break;
			//(*destroyStack)(&theStack);
            //exit(0);
        default:
            printf("wrong choice\n");    
        }
	}
	
	(*destroyStack)(&theStack);
	dlclose(libHandle);
	return SUCCESS;
    
}
