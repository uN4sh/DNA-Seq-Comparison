#include "alignement.h"

int main(int argc, char* argv[]) {

	if(argc < 2) {
		fprintf(stderr,"Erreur syntaxe : ./main2 rep\n");
		exit(EXIT_FAILURE); 
	}

	printf("\n*********************************************\nMakefile :\n\n  main1 pour compiler la partie1\n  partie1 pour l'exécuter\n  debug1 pour l'exécuter sous valgrind\n\n  main2 pour compiler la partie2\n  partie2 pour l'executer\n  debug2 pour l'executer sous valgrind\n\n  main3 pour compiler la partie3\n  partie3 pour l'exécuter\n  debug3 pour l'exécuter sous valgrind\n\n clean nettoyer le répertoire\n*********************************************\n");
	
	// Stock de toutes les distances dans un tableau Distance
	Distance *All = StockDistances(argv);
	printf("\nLa distance D1 est utilisée pour le calcul.\n");
	printf("Les distances et séquences associées ont toutes été stockées dans le tableau *All.\n");
	
	
	// Pour la partie 2 : tri croissant des distances et création d'un fichier texte avec les distances triées
	triFusion(All, 0, 189);
	printf("\nLe tableau *All a été trié dans l'ordre croissant de ses distances.\n");
	fileDistancesTriees(All);
	
	Famille *AllF = creaFamilles(All);
	printf("\nLes familles ont été créés et réparties dans leurs répertoires respectifs.\n\n");
	
	creaConsensus(AllF, All, argv);
	
	afficheFamille(AllF);
	
	
	/*int cptTab; //Taille du tableau d'alignement
	for (int i = 0; i < 20; i++)
		if(AllF[i].taille != 0) cptTab++; //Nombre de familles*/
		
	//Alignement *AllA = creaAlignement(AllF, cptTab, argv);
	
	// Affiche dans le terminal l'ensemble de ces distances
	//afficheAll(All, argv);

	// Libère la mémoire allouée au tableau de structures Distance et Famille
	libereAll(All);
	libereAllFamille(AllF);

	return EXIT_SUCCESS;
}
