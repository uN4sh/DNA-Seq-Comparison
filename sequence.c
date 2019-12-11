#include "sequence.h"

FILE *ouvrirFic(int i) {
	char fic[25];

	sprintf(fic, "sequences_ADN/seq%02d.txt",i);
	
	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier\n");
		exit(EXIT_FAILURE); 
	}
	
	return f;
}


int compterCarac(int nf) {
	FILE *f = ouvrirFic(nf);
	
	int cmp = 0;
	int c = fgetc(f);
	while (c != EOF) {
		cmp++;
		c = fgetc(f);
	}
	
	fclose(f);
	return cmp;
}

Sequence initSeq(int nf) {
	Sequence seq;
	seq.l = compterCarac(nf);
	
	FILE *f = ouvrirFic(nf);

	seq.sequence = malloc(seq.l*sizeof(char));
	fscanf(f, "%s", seq.sequence);
	
	fclose(f);
	return seq;
}