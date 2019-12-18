#include "distance.h"


int main(int argc, char* argv[]) {
	// fichier à ouvrir en boucle pour lire les sequences
	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main1 rep\n");
		exit(EXIT_FAILURE); 
	}
	

	// Stock de toutes les distances dans un tableau Distance
	Distance *All = StockDistances(argv);
	afficheAll(All, argv);
	libereAll(All);

	return 0;
}
