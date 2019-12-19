//#include "distance.h"
#include "triFusion.h"
// Note : triFusion à inclure dans la partie 2, le main1 devrait s'arrêter aux distances

int main(int argc, char* argv[]) {

	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main1 rep\n");
		exit(EXIT_FAILURE); 
	}

	printf("\nMakefile :\n  main1 pour compiler la partie1\n  run1 pour l'exécuter\n  debug1 pour l'exécuter sous valgrind\n  clean nettoyer le répertoire\n");

	// Stock de toutes les distances dans un tableau Distance
	Distance *All = StockDistances(argv);
	printf("\nLa distance D1 est utilisée pour le calcul.\n");
	printf("Les distances et séquences associées ont toutes été stockées dans le tableau *All.\n");

	// Affiche dans le terminal l'ensemble de ces distances
	//afficheAll(All, argv);

	// Créé un fichier texte avec la mise en forme de toutes les distances
	fileDistances(All);
	
	// Pour la partie 2 : tri croissant des distances et création d'un nouveau fichier texte
	triFusion(All, 0, 189);
	printf("\nLe tableau *All a été trié dans l'ordre croissant de ses distances.\n");
	fileDistancesTriees(All);

	// Libère la mémoire allouée au tableau de structures Distance
	libereAll(All);

	return EXIT_SUCCESS;
}
