#include "famille.h"


struct ALIGNEMENT{
	
	int numSeq;
	char* seq;
	struct ALIGNEMENT* suiv;	
	
	
};
typedef struct ALIGNEMENT Alignement;

void creaConsensus(Famille *AllF, Distance *All, char** argv);
Alignement *initAlignement(Alignement* list, int seq1, int seq2, int seqMax, char** argv);
void ajoutSequence(Alignement*list, int seq, int i, int seqMax, char** argv);
Alignement *libereAlignement(Alignement* list);
float Dmin(int v, int w, Distance *AllF);
void calculCons(Famille *AllF, Alignement *list, int i, int seqMax);
