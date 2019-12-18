#include "sequence.h"

FILE *ouvrirFic(int i, char** argv) {
	char fic[25];

	sprintf(fic, "%s/seq%02d.txt", argv[1], i);
	
	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier\n");
		exit(EXIT_FAILURE); 
	}
	
	return f;
}


int compterCarac(int nf, char** argv) {
	FILE *f = ouvrirFic(nf, argv);
	
	int cmp = 0;
	int c = fgetc(f);
	while (c != EOF) {
		cmp++;
		c = fgetc(f);
	}
	
	fclose(f);
	return cmp;
}

Sequence initSeq(int nf, char** argv) {
	Sequence seq;
	seq.l = compterCarac(nf, argv);
	FILE *f = ouvrirFic(nf, argv);

	seq.sequence = malloc( (seq.l+1) *sizeof(char)); //+1 pour le \O en fin de chaîne
	
	fscanf(f, "%s", seq.sequence);
	
	fclose(f);
	return seq;
}

// Libération de mémoire à ajouter