#include "triFusion.h"

//Structure famille avec son numéro, la distance Dmin associée, le nombre de sequences qu'elle contient et les numéros des sequences membres
struct famille {
	int nF; // Numéro de la famille
	int Dmin; // Distance Dmin associée
	int N; // Nombre de séquences dans la famille
	int *ns; // Tableau des numéros de séquences que la famille contient
};
typedef struct famille Famille;

// Allocation de mémoire selon la taille et initialisation de tous les paramètres pour une famille 
Famille initFamille(int nF, float Dmin, int N, int *ns);
Famille *creaFamilles(Distance *All);

// Verifie si une des deux sequences comparées est deja dans une famille
int familleCheck(Distance *All, int i);
// Renvoie 1 si toutes les séquences sont classées dans des familles (condition de fin de boucle)
int familleAllCheck(Distance *All);

int pivot(Distance *All, int i, float Dmin, int nbDist);

// Créé un répertoire pour un numéro de famille donné et copie les fichiers des séquences dedans
void familleRep(Famille F);

void afficheFamille(Famille *AllF);

void libereFamille(Famille F);
void libereAllFamille(Famille *AllF);
