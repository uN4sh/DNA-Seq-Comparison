#include "triFusion.h"

struct Famille {
	//Structure de la famille avec son numéro, le nombre de sequences qu'elle contient, les numéros des sequences et la distance qui les separe
	int nF; // Numéro de la famille
	int taille; // Nombre de séquences dans la famille
	int* ns; // Tableau des numéros de séquences que la famille contient
	float Dmin; // Distance Dmin associée
	int pivot; // Pivot de la famille
	char *seqCons; // Séquence consensus de la famille
	
};
typedef struct Famille Famille;

// Allocation de mémoire selon la taille et initialisation de tous les paramètres pour une famille 
Famille initFamille(int N, float Dmin, int nF, int *t, int pivot);
Famille *creaFamilles(Distance *All);
void solo(Famille *AllF, Distance *All, int fCount, float Dmin);
// Dans le cas où une séquences est solitaire à la fin de la répartition

int pivot(Distance *All, int i, float Dmin, int nbDist);

// Créé un répertoire pour un numéro de famille donné et copie les fichiers des séquences dedans
void familleRep(Famille F);

// Verifie si une des deux sequences comparées est deja dans une famille
int familleCheck(Distance *All, int i);
// Renvoie 1 si toutes les séquences sont classées dans des familles (condition de fin de boucle)
int familleAllCheck(Distance *All);

void afficheFamille(Famille *AllF);

void libereAllFamille(Famille *AllF);