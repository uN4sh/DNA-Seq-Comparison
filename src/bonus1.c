#include "../headers/distance.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Syntaxe : ./distance rep\n");
		exit(EXIT_FAILURE); 
	}
	char clear[6] = "clear";
	system(clear);
	printf("\n\033[36;01mBienvenue dans l'assistant comparateur de séquences.\033[00m\n\n");

	int v, w;
	printf("Veuillez entrer le numéro de la première sequence : ");
	scanf("%d", &v);
	printf("\n");

	printf("Veuillez entrer le numéro de la seconde sequence : ");
	scanf("%d", &w);
	printf("\n");

	printf("Distance D1 :\n");
	Distance D1 = distanceD1(v, w, argv);
	printf("\033[33;01m%02d %s\n%02d %s\n   D_%d_%d :\t%.1f\033[00m\n", D1.v, D1.V.sequence, D1.w, D1.W.sequence, D1.v, D1.w, D1.dist);
	printf("\n");

	printf("Distance D2 :\n");
	Distance D2 = distanceD2(v, w, argv);
	printf("\033[33;01m%02d %s\n%02d %s\n   D_%d_%d :\t%.1f\033[00m\n", D2.v, D2.V.sequence, D2.w, D2.W.sequence, D2.v, D2.w, D2.dist);
	printf("\n");


	exit(EXIT_SUCCESS);
}
