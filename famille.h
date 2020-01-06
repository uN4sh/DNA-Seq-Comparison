#include "triFusion.h"

struct Famille {
	//Structure de la famille avec son numéro, le nombre de sequences qu'elle contient, les numéros des sequences et la distance qui les separe
	int nF;
	int taille;
	int *ns;
	int Dmin;
	
};
typedef struct Famille Famille;

Famille initFamille(int N, float Dmin, int nF, int *t);
Famille *creaFamilles(Distance *All);
void familleRep(Famille F);
int familleCheck(Distance *All, int i);
int familleAllCheck(Distance *All);
int pivot(Distance *All, int i, float Dmin, int nbDist);
void libereFamille(Famille F);
void libereAllFamille(Famille *AllF);
void afficheFamille(Famille *AllF);
