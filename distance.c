#include "distance.h"

int charCompare(int cv, int cw) {
	// Comparateur de caractères selon la matrice de distances (Pour D1)
	if ( (cv == 'A' && cw == 'C') || (cv == 'C' && cw == 'A') || (cv == 'A' && cw == 'T') || (cv == 'T' && cw == 'A') 
	|| (cv == 'C' && cw == 'G') || (cv == 'G' && cw == 'T') || (cv == 'T' && cw == 'G') ) {
		return 2;
	}
	if ( (cv == 'A' && cw == 'G') || (cv == 'G' && cw == 'A') || (cv == 'C' && cw == 'T') || (cv == 'T' && cw == 'C') ) {
		return 1;
	}
	return 0;
}

Distance distanceD1(int v, int w, char** argv) {
	// Structure de donnée Distance : 2 Séquences, 2 int associés, un float pour la distance
	Distance D1;
	// On initialise les 2 champs des 2 séquences (Seq & taille)
	D1.V = initSeq(v, argv);
	D1.W = initSeq(w, argv);
	// Et on associe les numéros de séquences utlisés à la structure 
	D1.v = v;
	D1.w = w;
	// Initialisation du float distance à 0
	D1.dist = 0.0;
	// On effectue les comparaisons en allant jusqu'à la fin de la plus longue chaîne ADN
	for (int i = 0; i < D1.V.l || i < D1.W.l; i++) 
	{
		D1.dist += charCompare(D1.V.sequence[i], D1.W.sequence[i]);
	}
	// Puis on ajoute à la distance les "blancs" du nombre de la différence des deux chaînes
	for (int i = 0; i < fabs(D1.V.l - D1.W.l); i++)
		D1.dist += 1.5;
	// C'est la structure entière qui est retournée
	return D1;
}

Distance *StockDistances(char **argv) {
	int k = 0;
	// *All est un tableau de structures Distance qui stock toutes les distances & séquences associées
	// 190 distances différentes, *All doit contenir 190 fois la taille de la structure
	// Note : On pourrait faire un double tour de boucle avant l'allocation en incrémentant k pour la preuve des 190 distances
	Distance *All = malloc(190*sizeof(Distance));
	for (int v = 1; v <= 19; v++) {
		// La première boucle va jusqu'à la 19ème séquence pour la comparer avec la 20ème
		for (int w = v+1; w <= 20; w++) {
		// La deuxième boucle s'initialise à v+1 pour ne pas reprendre les distances déjà calculées (1_2 puis 2_1)
			All[k] = distanceD1(v, w, argv);
			// On incrémente k pour passer à la case suivante du tableau (k atteint les 190 en fin de boucle)	
			k++;
		}
	}
	
	return All; // Rappel : All = tableau de 190 structures Distance
}

void afficherDistance(Distance D){
	// Pour une structure Distance donnée, la fonction affiche les 2 séquences + n° associés, et leur distance
	printf("%d %s\t %d %s\t   D_%d_%d :\t%.1f\n", D.v, D.V.sequence, D.w, D.W.sequence, D.v, D.w, D.dist);
}

void afficheAll(Distance *All, char** argv) {
	// On reprend les mêmes boucles que celles du stockage pour afficher chaque case du tableau All
	int k = 0;
	for (int v = 1; v <= 19; v++)
	{
		for (int w = v+1; w <= 20; w++)
		{
			afficherDistance(All[k]);
			k++;
			printf("\n");
		}
	}
}

void libereMemoire(Distance D) {
	// Pour une structure Distance donnée, free de la mémoire allouée aux 2 séquences ADN dans leurs struct respectives
	free(D.V.sequence);
	free(D.W.sequence);
}

void libereAll(Distance *All) {
	// Pour libérer le tableau All, on free ses 190 cases puis son adresse propre
	for (int k = 0; k < 190; k++)
	{
		libereMemoire(All[k]);
	}
	free(All);
}