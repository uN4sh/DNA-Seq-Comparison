#include "distance.h"
#include "sequence.h"


int main() {
	// fichier à ouvrir en boucle pour lire les sequences
	Sequence Seq1 = initSeq("sequences_ADN/seq03.txt");
	printf("Seq3 a %d caractères\n", Seq1.l);
	
	for (int i = 0; i < Seq1.l ; i++)
	{
		printf("%c", Seq1.sequence[i]);
	}
	printf("\n");
	
	return 0;
}
