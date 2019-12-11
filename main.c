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
	
	free(Seq3.sequence);
	
	int v = 7;
	int w = 1;
	printf("Distance d'édition Seq%d et Seq%d = %.1f\n", v, w, distanceD1(v, w));
	printf("Distance d'édition v2 Seq%d et Seq%d = %.1f\n", v, w, distanceD1v2(v, w));
	
	//free(D1);
	return 0;
}
