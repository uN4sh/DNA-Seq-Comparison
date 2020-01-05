#include "triFusion.h"

struct Famille {
	
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
