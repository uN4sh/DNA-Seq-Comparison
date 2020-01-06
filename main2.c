#include "famille.h"

int main(int argc, char* argv[]) {

	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main2 rep\n");
		exit(EXIT_FAILURE); 
	}

	printf("\n*********************************************\nMakefile :\n\n  main1 pour compiler la partie1\n  run1 pour l'exécuter\n  debug1 pour l'exécuter sous valgrind\n\n  main2 pour compiler la partie2\n  run2 pour l'executer\n  debug2 pour l'executer sous valgrind\n\n  clean nettoyer le répertoire\n*********************************************\n");

	// Stock de toutes les distances dans un tableau Distance
	Distance *All = StockDistances(argv);
	printf("\nLa distance D1 est utilisée pour le calcul.\n");
	printf("Les distances et séquences associées ont toutes été stockées dans le tableau *All.\n");
	
	
	// Pour la partie 2 : tri croissant des distances et création d'un fichier texte avec les distances triées
	triFusion(All, 0, 189);
	printf("\nLe tableau *All a été trié dans l'ordre croissant de ses distances.\n");
	fileDistancesTriees(All);
	
	Famille *AllF = creaFamilles(All);
	printf("Les familles ont été créés et réparties dans leurs répertoires respectifs.\n");
	afficheFamille(AllF);
	
	// Affiche dans le terminal l'ensemble de ces distances
	//afficheAll(All, argv);

	// Libère la mémoire allouée au tableau de structures Distance et Famille
	libereAll(All);
	libereAllFamille(AllF);

	return EXIT_SUCCESS;
}
