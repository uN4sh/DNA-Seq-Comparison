#include "famille.h"

int main(int argc, char* argv[]) {

	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main2 rep\n");
		exit(EXIT_FAILURE); 
	}

	printf("\n\033[00;01mMakefile :\033[00m\n");
	printf("\033[33;01m    main1\033[00m \033[33mpour compiler la partie1\n\033[33;01m    partie1\033[00m \033[33mpour l'exécuter\n\033[33;01m    debug1\033[00m \033[33mpour l'exécuter sous valgrind\n\n\033[00m");
	printf("\033[34;01m    main2\033[00m \033[34mpour compiler la partie2\n\033[34;01m    partie2\033[00m \033[34mpour l'executer\n\033[34;01m    debug2\033[00m \033[34mpour l'executer sous valgrind\n\n\033[00m");
	printf("\033[36;01m    clean\033[00m \033[36m nettoyer le répertoire\033[00m\n\n");

	// Stock de toutes les distances dans un tableau Distance
	Distance *All = StockDistances(argv);
	printf("\nLa distance D1 est utilisée pour le calcul.\n");
	printf("Les distances et séquences associées ont toutes été stockées dans le tableau *All.\n");
	
	
	// Pour la partie 2 : tri croissant des distances et création d'un fichier texte avec les distances triées
	triFusion(All, 0, 189);
	printf("\n\033[34mLe tableau *All a été trié dans l'ordre croissant de ses distances.\033[00m\n");
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
