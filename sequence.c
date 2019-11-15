#include "sequence.h"

int compterCarac(char* fic) {

	// sprintf(chaine, seq0%d.txt, i); inferieur à 10, et supérieur à 10 sans 0
	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier\n");
		exit(EXIT_FAILURE); 
	}
	
	int cmp = 0;
	int c = fgetc(f);
	while (c != EOF) {
		cmp++;
		c = fgetc(f);
	}
	
	fclose(f);
	return cmp;
}

Sequence initSeq(char* fic) {
	Sequence seq;
	seq.l = compterCarac(fic);
	
	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier init\n");
		exit(EXIT_FAILURE);
	}
	
	seq.sequence = malloc(seq.l*sizeof(char));
	fscanf(f, "%s", seq.sequence);
	
	fclose(f);
	return seq;
}
