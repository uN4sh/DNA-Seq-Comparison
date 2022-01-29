### Partie 1 ###

partie1: main1
	./main1 DNA

debug1: main1
	valgrind ./main1 DNA

main1: sequence.o distance.o main1.o 
	gcc -Wall -g -o main1 main1.o sequence.o distance.o

main1.o: src/main1.c headers/sequence.h headers/distance.h
	gcc -Wall -g -c src/main1.c

### Partie 2 ###

partie2: main2
	./main2 DNA

debug2: main2
	valgrind ./main2 DNA
	
main2: sequence.o distance.o main2.o triFusion.o famille.o
	gcc -Wall -g -o main2 main2.o sequence.o distance.o triFusion.o famille.o

main2.o: src/main2.c headers/sequence.h headers/distance.h headers/triFusion.h headers/famille.h
	gcc -Wall -g -c src/main2.c

### Partie 3 ###

partie3: main3
	./main3 DNA

debug3: main3
	valgrind ./main3 DNA
	
main3: sequence.o distance.o main3.o triFusion.o famille.o alignement.o
	gcc -Wall -g -o main3 main3.o sequence.o distance.o triFusion.o famille.o alignement.o

main3.o: src/main3.c headers/sequence.h headers/distance.h headers/triFusion.h headers/famille.h headers/alignement.h
	gcc -Wall -g -c src/main3.c

### Compilation des fichiers ###	

sequence.o: src/sequence.c headers/sequence.h
	gcc -Wall -g -c src/sequence.c

distance.o: src/distance.c headers/sequence.h headers/distance.h
	gcc -Wall -g -c src/distance.c

triFusion.o : src/triFusion.c headers/triFusion.h 
	gcc -Wall -g -c src/triFusion.c

famille.o: src/famille.c headers/famille.h
	gcc -Wall -g -c src/famille.c

alignement.o: src/alignement.c headers/alignement.h
	gcc -Wall -g -c src/alignement.c
	

### Programmes supplémentaires ###

distCalcul: bonus1
	./bonus1 DNA

bonus1: sequence.o distance.o bonus1.o 
	gcc -Wall -g -o bonus1 bonus1.o sequence.o distance.o

bonus1.o: src/bonus1.c headers/distance.h
	gcc -Wall -g -c src/bonus1.c

### Utilitaires ###

clean:
	rm -f *.o
	rm -f main1
	rm -f main2
	rm -f main3
	rm -f bonus1
	rm -f stockDistances.txt
	rm -f stockDistancesTriées.txt
	rm -rf Famille*
	ls -l

NOM = Archive
archive:
	rm -rf ${NOM} 
	mkdir ${NOM} 
	cp -r DNA ${NOM} 
	cp src/*.c ${NOM} 
	cp headers/*.h ${NOM} 
	cp Makefile ${NOM} 
	zip -r $(NOM) .zip $(NOM)
