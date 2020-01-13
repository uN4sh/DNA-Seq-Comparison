#include "sequence.h"
// Les librairies stdio et stdlib sont incluses via le header sequence.h

FILE *openFic(int i, char** argv) {
	if (i < 1 || i > 20) {
		fprintf(stderr, "Erreur : les séquences sont numérotées de 0 à 20\n");
		exit(EXIT_FAILURE);
	}

	// Ouvre le fichier associé à l'entier dans le repertoire mis en argument par l'éxecution (ici : sequences_ADN)
	char fic[25];
	// On écrit dans la chaîne fic le chemin d'accès au fichier de séquences 
	sprintf(fic, "%s/seq%02d.txt", argv[1], i);
	// Le %2d assure que les séquences inférieurs à 10 s'écrivent bien "01, 02..."
	FILE *f = fopen(fic, "r");
	if(f == NULL) {
		fprintf(stderr,"Echec ouverture fichier\n");
		exit(EXIT_FAILURE); 
	}
	return f;
}


int charCounter(int nf, char** argv) {
	// Pour un numéro de séquence donnée, retourne le nombre de caractères que contient son fichier
	FILE *f = openFic(nf, argv);
	
	int cmp = 0;
	int c = fgetc(f);
	while (c != EOF) {
		cmp++;
		c = fgetc(f);
	}
	// Compteur classique caractère par caractère jusqu'à l'End of file
	fclose(f);
	return cmp;
}

Sequence initSeq(int nf, char** argv) {
	// Initialise une séquence en lui assignant d'abord sa taille puis sa chaîne de caractères
	Sequence seq;
	seq.l = charCounter(nf, argv);
	seq.check = 0;
	FILE *f = openFic(nf, argv);
	// On alloue la longueur de la séquence +1 pour le caractère de fin de chaîne présent
	seq.sequence = malloc( (seq.l+1) *sizeof(char)); if(!seq.sequence) exit(0);
	// Puis on écrit la séquence dans la chaîne de caractère
	fscanf(f, "%s", seq.sequence);
	
	fclose(f);
	return seq;
}

void libereSeq(Sequence S) {
	// Pour une structure Sequence donnée, free de la mémoire allouée à la chaîne ADN
	free(S.sequence);
}
