CC = gcc
FLAGS = -std=c99 -pthread -w -pipe -O2 -Wextra -Werror -Wall -Wno-sign-compare -pedantic -lm

all: run

run: libstack.so main_stat.o main_shared.o
	$(CC) $(FLAGS) -o run-stat main_stat.o -L. -lqueue -Wl,-rpath,.
	$(CC) $(FLAGS) -o run-dyn main_shared.o -ldl

main_stat.o: main_stat.c
	$(CC) -c $(FLAGS) main_stat.c

main_shared.o: main_shared.c
	$(CC) -c $(FLAGS) main_shared.c

stack.o: stack.c
	$(CC) -c -fPIC $(FLAGS) stack.c

libstack.so: stack.o
	$(CC) $(FLAGS) -shared -o libstack.so stack.o

clean:
	rm -f *.o run-stat run-dyn *.so
