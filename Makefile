log: parser.o scanner.o main.o list.o stack.o
	gcc -o log main.o scanner.o parser.o list.o stack.o

parser.o: parser.c 
	gcc -c parser.c -o parser.o

scanner.o: scanner.c
	gcc -c scanner.c -o scanner.o

main.o: main.c
	gcc -c main.c -o main.o

list.o: list.c 
	gcc -c list.c -o list.o

stack.o: stack.c 
	gcc -c stack.c -o stack.o

clean:
	rm -f scanner.o log parser.o list.o stack.o *.o scan
