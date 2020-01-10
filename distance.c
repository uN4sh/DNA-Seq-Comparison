#include "distance.h"

// Pour calculer le min entre 3 valeurs (Utile pour D2)
#define min3(x,y,z) ( (x) < (min2(y, z)) ? (x):(min2(y,z)) )
#define min2(x,y)  ( (x) < (y) ? (x):(y))

int charCompare(int cv, int cw) {
	// Comparateur de caractères selon la matrice de distances (Pour D1)
	if (cv == cw) {
		return 0;
	}

	if ( (cv == 'A' && cw == 'G') || (cv == 'G' && cw == 'A') || (cv == 'C' && cw == 'T') || (cv == 'T' && cw == 'C') ) {
		return 1;
	}
	
	return 2;
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
	for (int i = 0; i < D1.V.l && i < D1.W.l; i++) 
	{
		D1.dist += charCompare(D1.V.sequence[i], D1.W.sequence[i]);
	}
	// Puis on ajoute à la distance les "blancs" du nombre de la différence des deux chaînes
	D1.dist += fabs(D1.V.l - D1.W.l) * 1.5;
	
	// C'est la structure entière qui est retournée
	return D1;
}

Distance distanceD2(int v, int w, char** argv) {
	// Structure de donnée Distance : 2 Séquences, 2 int associés, un float pour la distance
	Distance D2;
	// On initialise les 2 champs des 2 séquences (Seq & taille)
	D2.V = initSeq(v, argv);
	D2.W = initSeq(w, argv);
	// Et on associe les numéros de séquences utlisés à la structure 
	D2.v = v;
	D2.w = w;
	// Initialisation du float distance à 0
	D2.dist = 0.0;

	D2.dist = Dist2(D2.V, D2.W);
	return D2;
}

float Dist2 (Sequence V, Sequence W) {
	// Programmation dynamique! Pas de récursivité!
	float m[21][21]; 
	// Tableau avec le max de caractères possibles dans une séquences
	// On pourrait mettre pile V.l et W.l mais ça complique la boucle de remplissage des bords
	for (int i = 0; i < 21; i++) {
		// On remplit le bord bas et gauche des multiples de 1.5
		m[0][i] = 1.5*i; // Délétion de tous les caractères de la 2eme seq
		m[i][0] = 1.5*i; // Délétion de tous les caractères de la 1ere seq
	}
	
	for (int i = 1; i <= V.l; i++)
	{ 
		for (int j = 1; j <= W.l; j++)
		{
			// On remplit chaque case du tableau avec la meilleure distance 
			m[i][j] = min3( (m[i][j-1] + 1.5),
						   (m[i-1][j] + 1.5),
						   (m[i-1][j-1] + charCompare(V.sequence[i-1], W.sequence[j-1])) );
		}
	}
	return m[V.l][W.l]; 
}

Distance *StockDistances(char **argv, int D) {
	int k = 0;
	// *All est un tableau de structures Distance qui stock toutes les distances & séquences associées
	// 190 distances différentes, *All doit contenir 190 fois la taille de la structure
	// Note : On pourrait faire un double tour de boucle avant l'allocation en incrémentant k pour la preuve des 190 distances
	Distance *All = malloc(190*sizeof(Distance));
	for (int v = 1; v <= 19; v++) {
		// La première boucle va jusqu'à la 19ème séquence pour la comparer avec la 20ème
		for (int w = v+1; w <= 20; w++) {
		// La deuxième boucle s'initialise à v+1 pour ne pas reprendre les distances déjà calculées (1_2 puis 2_1)
			if (D == 1)
				All[k] = distanceD1(v, w, argv);
			else if (D == 2)
				All[k] = distanceD2(v, w, argv);
			else {
				fprintf(stderr, "Erreur : Veuillez choisir la distance 1 ou 2\n");
				exit(EXIT_FAILURE);
			}
			
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

void fileDistances (Distance *All) {
	// Création d'un fichier des distances
	FILE *fDist = fopen("stockDistances.txt", "w");
	if(fDist == NULL) {
		fprintf(stderr,"Echec lors de la création du fichier du stockage des distances\n");
		exit(EXIT_FAILURE); 
	}
	int k = 0;
	for (int v = 1; v <= 19; v++)
	{
		for (int w = v+1; w <= 20; w++)
		{
			fprintf(fDist, "%d %s\t %d %s\t   D_%d_%d :\t%.1f\n", All[k].v, All[k].V.sequence,
				    All[k].w, All[k].W.sequence, All[k].v, All[k].w, All[k].dist);
			k++;
			fprintf(fDist, "\n");
		}
	}
	fclose(fDist);
	printf("Le fichier stockDistances.txt a été créé avec succès.\n");
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