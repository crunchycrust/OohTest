#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define ARRAY_INITIAL 100

//#include "Array.h"


typedef struct {
	int size; //what's used so far
	int capacity; //total available
	int *data;  //what we are sorting
} Array;

void arrayinit(Array *array);
void doublecapacity(Array *array);
void arrayadd(Array *array, int value);
void arrayget(Array *array, int index);
void arrayinsert(Array *array, int index, int value);
void arrayremove(Array *array, int index);
void arrayprint(Array *array); 
void arrayfree(Array *array);

void arrayinit(Array *array) {
	array->size = 0;
	array->capacity = ARRAY_INITIAL;
	array->data = malloc(sizeof(int) * array->capacity);
}

void doublecapacity(Array *array) {
	if (array->size >= array->capacity) {
		array->capacity *= 2;
		array->data = realloc(array->data, sizeof(int) * array->capacity);
	}
}

void arrayadd(Array *array, int value) {
	doublecapacity(array);
	array->data[array->size++] = value;
}

void arrayinsert(Array *array, int index, int value) {
	while (index >= array->size) {
		arrayadd(array, 0);
	}
	array->data[index] = value;
}

void arrayget(Array *array, int index) {
	int value;	
	if (index >= array->size || index < 0) {
		printf("Error: invalid index\n");	
	}
	else {
		value = array->data[index];
		printf("Value with %d index = %d\n", index, value);
	}
}

void arrayremove(Array *array, int index) {
	if (index >= array->size || index < 0) {
		printf("Error: invalid index\n");	
	}
	else {
		int i, value;
		for(i = index; i < array->size; i++) {
			value = array->data[i+1];
			array->data[i] = value;
		}
		array->size = (array->size) - 1;
	}
}

void arrayprint(Array *array) {
	if (array->size <= 0) {
		printf("Your array is empty");
	}
	else {
		int i;
		printf("Array: ");
		for (i= 0; i < array->size; i++) {
			printf("%d ", array->data[i]);
		} 
	}
}

void arraydel(Array *array) {
	if (array->size <= 0) {
		printf("Your array is empty");
	}
	else {
		int i;
		for(i = 0; i < array->size; i++) {
			array->data[i] = 0;
		}
		array->size = 0;
	}
}

void arrayfree(Array *array) {
	free(array->data);
}

void menu() {
	printf("HELP\n0) 'h'    - help;\n1) 'a'    - add;\n2) 'i'    - insert;\n3) 'g'    - value from index;\n4) 'p'    - print array;\n5) 'r'    - remove with index;\n6) 'e'    - empty your array;\n7) Ctrl+D - quit");
}


int main(){
	int fd[2]; 
	char buf;
	int c, i;
	int index, value;
	
	printf("HELP\n0) 'h'    - help;\n1) 'a'    - add;\n2) 'i'    - insert;\n3) 'g'    - value from index;\n4) 'p'    - print array;\n5) 'r'    - remove with index;\n6) 'e'    - empty your array;\n7) Ctrl+D - quit\n\n");
	Array array;
	arrayinit(&array);
	
	pipe(fd);
	if (pipe(fd) == -1){
		perror("pipe() error");
		return 1;
	}

	pid_t pid = fork();
	
	if (pid < 0) {
		perror("fork() error");
	}
	else if (pid == 0) {
		close(fd[0]);
		while ((c = getchar()) != EOF) {
			switch(c) {
			default: 
				write(fd[1], &c, 1);
				sleep(1);
				break;
			}
		}
		close(fd[1]);
	} 
	else {
		close(fd[1]);
		
		while(read(fd[0], &buf, 1)>0) {
			switch (buf) {
			case 'a':
				printf("Enter your value, please: "); 
				scanf("%d", &value);
				arrayadd(&array, value);
				printf("Value added");
				break;
			case 'g':
				printf("Enter your index, please: ");
				scanf("%d", &index);
				arrayget(&array, index);
				printf("Search complete");				
				break;
			case 'i':
				printf("Enter your index: ");
				scanf("%d", &index);
				printf("Enter your value: ");
				scanf("%d", &value);
				arrayinsert(&array, index, value);
				printf("Value added");				
				break;
			case 'r':
				printf("Enter your index, please: ");
				scanf("%d", &index);
				arrayremove(&array, index);
				printf("Removal complete");				
				break;
			case 'e':
				arraydel(&array);
				printf("Complete");
				break;
			case 'p':
				arrayprint(&array);
				printf("\nComplete");
				break;
			case 'h':
				menu();
				break;
			default:
				printf("Try again");
				break;
			}
			printf("\n");
			//printf("recieved: %c\n", buf);
		}
		close(fd[0]);
		//waitpid(-1, NULL, 0);	
		arrayfree(&array);
	}
	//arrayfree(&array);
	return 0;
}
