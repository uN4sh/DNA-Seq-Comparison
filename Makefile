run1: main1
	./main1 sequences_ADN

debug1: main1
	valgrind ./main1 sequences_ADN

main1: sequence.o distance.o main.o
	gcc -Wall -g -o main1 main.o sequence.c distance.o

main1.o: main1.c sequence.h distance.h
	gcc -Wall -g -c main.c
	
distance.o: distance.c sequence.h distance.h
	gcc -Wall -g -c distance.c

sequence.o: sequence.c sequence.h
	gcc -Wall -g -c sequence.c

clean:
	rm -f *.o
	rm -f main1
	ls -l