partie2: main2
	./main2 sequences_ADN

debug2: main2
	valgrind ./main2 sequences_ADN
	
main2: sequence.o distance.o main2.o triFusion.o famille.o
	gcc -Wall -g -o main2 main2.o sequence.o distance.o triFusion.o famille.o

main2.o: main2.c sequence.h distance.h triFusion.h famille.h
	gcc -Wall -g -c main2.c

partie1: main1
	./main1 sequences_ADN

debug1: main1
	valgrind ./main1 sequences_ADN

main1: sequence.o distance.o main1.o 
	gcc -Wall -g -o main1 main1.o sequence.o distance.o

main1.o: main1.c sequence.h distance.h
	gcc -Wall -g -c main1.c
	
triFusion.o : triFusion.c triFusion.h 
	gcc -Wall -g -c triFusion.c

distance.o: distance.c sequence.h distance.h
	gcc -Wall -g -c distance.c

sequence.o: sequence.c sequence.h
	gcc -Wall -g -c sequence.c
	
famille.o: famille.c famille.h
	gcc -Wall -g -c famille.c

clean:
	rm -f *.o
	rm -f main1
	rm -f main2
	rm -f stockDistances.txt
	rm -f stockDistancesTriées.txt
	ls -l
