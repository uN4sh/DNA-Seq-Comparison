run : all
	./main
	
all: main

main: sequence.o distance.o main.o
	gcc -Wall -g -o main main.o sequence.c distance.o

main.o: main.c sequence.h distance.h
	gcc -Wall -g -c main.c
	
distance.o: distance.c sequence.h distance.h
	gcc -Wall -g -c distance.c

sequence.o: sequence.c sequence.h
	gcc -Wall -g -c sequence.c

clean:
	rm -f *.o
	rm -f main
	ls -l
