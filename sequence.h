#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sequence {
	char* sequence; // Tableau de char stocke une séquence
	int l; // Longueur de la séquence
};
typedef struct Sequence Sequence;

FILE *ouvrirFic(int i, char** argv);
Sequence initSeq(int nf, char** argv);
int compterCarac(int nf, char** argv);
