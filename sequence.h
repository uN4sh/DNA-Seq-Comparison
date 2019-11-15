#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sequence {
	char* sequence; // Tableau de char stocke une séquence
	int l; // Longueur de la séquence
};
typedef struct Sequence Sequence;


Sequence initSeq(char* fic);
int compterCarac(char* fic);
