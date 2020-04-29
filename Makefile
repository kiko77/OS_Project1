main: main.o scheduler.o process.o queue.o
	gcc main.o scheduler.o process.o queue.o -o main
main.o: main.c
	gcc main.c -c
scheduler.o: scheduler.c 
	gcc scheduler.c -c
process.o: process.c process.h
	gcc process.c -c
queue.o: queue.c queue.h
	gcc queue.c -c
clean:
	 rm -rf *o
