#include "distance.h"

int main(int argc, char* argv[]) {

	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main1 rep\n");
		exit(EXIT_FAILURE); 
	}

	printf("\n*********************************************\nMakefile :\n\n  main1 pour compiler la partie 1\n  run1 pour l'exécuter\n  debug1 pour l'exécuter sous valgrind\n\n  main2 pour compiler la partie 2\n  run2 pour l'executer\n  debug2 pour l'executer sous valgrind\n\n  clean nettoyer le répertoire\n*********************************************\n");

	// Stock de toutes les distances dans un tableau Distance
	Distance *All = StockDistances(argv);
	printf("\nLa distance D1 est utilisée pour le calcul.\n");
	printf("Les distances et séquences associées ont toutes été stockées dans le tableau *All.\n");

	// Affiche dans le terminal l'ensemble de ces distances
	//afficheAll(All, argv);

	// Créé un fichier texte avec la mise en forme de toutes les distances
	fileDistances(All);	
	

	// Libère la mémoire allouée au tableau de structures Distance
	libereAll(All);

	return EXIT_SUCCESS;
}
