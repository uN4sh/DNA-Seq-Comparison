#include "famille.h"

int main(int argc, char* argv[]) {
	char clear[6] = "clear";
	system(clear);
	
	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main2 rep\n");
		exit(EXIT_FAILURE); 
	}
	
	printf("\n\033[00;01mMakefile :\033[00m\n");
	printf("\033[33;01m    main1\033[00m \033[33mpour compiler la partie1\n\033[33;01m    partie1\033[00m \033[33mpour l'exécuter\n\033[33;01m    debug1\033[00m \033[33mpour l'exécuter sous valgrind\n\n\033[00m");
	printf("\033[34;01m    main2\033[00m \033[34mpour compiler la partie2\n\033[34;01m    partie2\033[00m \033[34mpour l'executer\n\033[34;01m    debug2\033[00m \033[34mpour l'executer sous valgrind\n\n\033[00m");
	printf("\033[32;01m    main3\033[00m \033[32mpour compiler la partie3\n\033[32;01m    partie3\033[00m \033[32mpour l'executer\n\033[32;01m    debug3\033[00m \033[32mpour l'executer sous valgrind\n\n\033[00m");
	printf("\033[36;01m    clean\033[00m \033[36m nettoyer le répertoire\033[00m\n\n");
	
	int D;
	// Stock de toutes les distances dans un tableau Distance selon D1 ou D2
	printf("Quelle méthode de calcul des distances souhaitez-vous utiliser ? (1 ou 2)\n");
	scanf("%d", &D);
	Distance *All = StockDistances(argv, D);

	printf("\nLa distance D%d est utilisée pour le calcul.\n", D);
	printf("Les distances et séquences associées ont toutes été stockées dans le tableau *All.\n");
	
	// Tri croissant des distances et création d'un fichier texte avec les distances triées
	triFusion(All, 0, 189);
	printf("\nLe tableau *All a été trié dans l'ordre croissant de ses distances.\n");
	fileDistancesTriees(All);
	
	Famille *AllF = creaFamilles(All);
	printf("\nLes familles ont été créés et réparties dans leurs répertoires respectifs.\n");  
	afficheFamille(AllF, argv);
	
	// Affiche dans le terminal l'ensemble de ces distances
	//afficheAll(All, argv);

	// Libère la mémoire allouée au tableau de structures Distance et Famille
	
	libereAll(All);
	libereAllFamille(AllF);
	
	return EXIT_SUCCESS;
}
