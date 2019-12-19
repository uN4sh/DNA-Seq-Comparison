run1: main1
	./main1 sequences_ADN

debug1: main1
	valgrind ./main1 sequences_ADN

main1: sequence.o distance.o main1.o triFusion.o
	gcc -Wall -g -o main1 main1.o sequence.o distance.o triFusion.o 

main1.o: main1.c sequence.h distance.h triFusion.h
	gcc -Wall -g -c main1.c
	
triFusion.o : triFusion.c triFusion.h 
	gcc -Wall -g -c triFusion.c

distance.o: distance.c sequence.h distance.h
	gcc -Wall -g -c distance.c

sequence.o: sequence.c sequence.h
	gcc -Wall -g -c sequence.c

clean:
	rm -f *.o
	rm -f main1
	rm -f stockDistances.txt
	rm -f stockDistancesTriées.txt
	ls -l