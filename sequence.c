#include "sequence.h"

FILE *ouvrirFic(int i) {
	char fic[25];
	if (i<10) 
		sprintf(fic, "sequences_ADN/seq0%d.txt",i);
	else 
		sprintf(fic, "sequences_ADN/seq%d.txt",i); 

	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier\n");
		exit(EXIT_FAILURE); 
	}
	
	return f;
}


int compterCarac(int nf) {
	FILE *f = ouvrirFic(nf);
	/*
	char fic[25];
	if (nf<10) 
		sprintf(fic, "sequences_ADN/seq0%d.txt",nf);
	else 
		sprintf(fic, "sequences_ADN/seq%d.text",nf); 

	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier\n");
		exit(EXIT_FAILURE); 
	}
	*/
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

	char fic[25];
	if (nf<10) 
	  sprintf(fic, "sequences_ADN/seq0%d.txt",nf);
	else 
	  sprintf(fic, "sequences_ADN/seq%d.text",nf);
	
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
