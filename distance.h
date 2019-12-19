#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sequence.h"

/* Matrice de distances :
 * 		A	C	G	T	 -
 * 	A	0	2	1	2	1.5
 * 	C	2	0	2	1	1.5
 * 	G	1	2	0	2	1.5
 * 	T	2	1	2	0	1.5
 *	-      1.5     1.5     1.5     1.5
 */
 
struct distance {
	// Comprend 2 Struct Séquences (ADN & taille) + n° de séquence associé, ainsi qu'un float pour la distance
	Sequence V;
	int v;
	Sequence W;
	int w;
	float dist;
};
typedef struct distance Distance;


int charCompare(int cv, int cw);
// Comparateur de caractères selon la matrice de distances (Pour D1)
Distance distanceD1(int v, int w, char** argv);
// Distance D1, retourtant une structure Distance, expliquée en détail dans le fichier .c

Distance *StockDistances(char **argv);
// Stockage de toutes les distances entre paires de séquences dans un tableau de structure Distance

void afficherDistance(Distance D);
void afficheAll(Distance *All, char** argv);
// Fonctions pour l'affichage et la mise en forme de toutes les distances & séquences associées 

void fileDistances (Distance *All);
// Création d'un fichier stockDistances.txt avec l'ensemble des distances & séquences associées

void libereMemoire(Distance D);
// Libère les 2 champs de séquences compris dans une structure Distance
void libereAll(Distance *All);
// Libération de mémoire de toutes les séquences dans le tableau de struct Distance