#include "distance.h"


int main() {
	// fichier à ouvrir en boucle pour lire les sequences
	Sequence Seq3 = initSeq(3);
	printf("Seq %d a %d caractères\n", 3, Seq3.l);
	
	for (int i = 0; i < Seq3.l ; i++)
	{
		printf("%c", Seq3.sequence[i]);
	}
	printf("\n");
	
	
	
	int v = 60;
	int w = 61;
	printf("Distance d'édition Seq%d et Seq%d = %f\n", v, w, distanceD1(v, w));
	
	return 0;
}
