#include "famille.h"

Famille initFamille(int N, float Dmin, int nF, int *t){
	//Creation de la famille
	Famille F;
	//allocation de N * int pour le nombre de séquences et l'allouer à tailleF
	F.ns = malloc (N * sizeof(int));
	F.taille = N;
	//prise en note de Dmin, distance par rapport au pivot
	F.Dmin = Dmin;
	//numéro de la famille
	F.nF = nF;
	//Remplissage du tableau contenant les numéros des séquences de la famille
	int j = 0;
	for (int i = 0; i < 150; i++)
	{
		if(t[i] != 0){ 
			F.ns[j] = t[i];
			j++;
		}		
	}	

	return F;
}

Famille *creaFamilles(Distance *All){
	//Creation du tableau contenant les familles, de taille 20 car il ne peut y en avoir plus de 20 (20 séquences et familles de 1)
	Famille *AllF = malloc (20 * sizeof(Famille));
	int fCount;
	int dCount = 0;
	float Dmin;
	int cptFamille;
	int dtemp;
	int nbDist;
	int piv;
	int d;
	int temp[150] = {0};
	
	while(familleAllCheck(All) == 0){
		
		if(familleCheck(All, dCount) == 0){
			Dmin = All[dCount].dist;
			d = 0;
			dtemp = dCount;
			cptFamille = 0;
			while((All[dCount].dist) == Dmin){
				if(familleCheck(All, dCount) == 0)
					nbDist++;
				d++;
				dCount++;
			}
			dCount = dtemp;		
			piv = pivot(All, dCount, Dmin, nbDist);
			dtemp = 0;
			for (int j = dCount; j < (dCount+d); j++)
			{
				if((familleCheck(All, j) == 0) && (All[j].v == piv)){
					All[j].V.check = 1;
					All[j].W.check = 1;
					temp[dtemp] = All[j].w;
					dtemp++;
					cptFamille++;
				}
				else if((familleCheck(All, j) == 0) && (All[j].w == piv)){
					All[j].V.check = 1;
					All[j].W.check = 1;
					temp[dtemp] = All[j].v;
					dtemp++;
					cptFamille++;				
				}				
			}
			//On élimine les doublons
			for (int m = 0 ; m < 150 ; m++){
				if(temp[m]!=0){
					for (int n = m+1 ; n < 150 ; n++){
						if(temp[n] == temp[m]) temp[n] = 0;						
					}
				}	
			}
			AllF[fCount] = initFamille(cptFamille, Dmin, fCount+1, temp);
			familleRep(AllF[fCount]);
			dCount = 0;
			fCount++;
		}
		else dCount++;
	}
	
	if(fCount<20){
		for (int i = fCount; i < 20; i++)
		{
			AllF[i] = initFamille(0,0,0,0);
		}		
	}
		
	return AllF;
}

//Fonction création répertoire qui prends le numéro de la famille en argument pour le nom du dossier
void familleRep(Famille F){
	char creaRep[100];
	char cpSeq[100];
	sprintf(creaRep, "mkdir Famille%02d",F.nF); //Creation du dossier avec le numéro de la famille
	system(creaRep);
	for (int i = 0; i < F.taille; i++)
	{
		//chaque sequence de la famille est copiee vers ce dossier
		sprintf(cpSeq, "cp sequences_ADN/seq%02d.txt Famille%02d/seq%02d.txt",F.ns[i],F.nF,F.ns[i]);
		system(cpSeq);
	}		
} 

//Fonction qui verifie si une des deux sequences comparees est deja dans une famille
int familleCheck(Distance *All, int i){

	if(All[i].V.check == 0 || All[i].W.check == 0)
		return 0;
	return 1;	
}

//Fonction qui permet de savoir si toutes les sequences sont classees
int familleAllCheck(Distance *All){
	
	for (int i = 0; i < 190; i++)
	{
		if((familleCheck(All, i)) == 0) return 0;
	}
	return 1;
}

//Fonction qui trouve la sequence ayant le plus de "vosines" à une distance Dmin
int pivot(Distance *All, int i, float Dmin, int nbDist){
	//La fonction prend en parametre le tableau des distances, le point de départ de la valeur Dmin, et le nombre de comparaisons ayant cette meme distance (sans compter celles avec des sequences en famille)
	//Puisque le tableau est trié en fonction des distances, on a le nombre de comparaisons à une meme distance.
	//Pour celles qui n'ont pas de sequences classées, on repertorie les sequences dans un tableau seqList 
	int k = 0;
	nbDist*=2;
	int seqList[nbDist];
	while((All[i].dist) == Dmin){
		if(familleCheck(All, i) == 0){
			seqList[k] = All[i].v;
			seqList[k+1] = All[i].w;
		}
		i++;
		k+=2;
	}	
	//On initialise un tableau à double entrées, afin de sauvegarder et de mettre en relation les numéros des sequences et leurs fréquences d'apparition
	int cpt[nbDist][2];
	for (int j = 0; j < nbDist; j++)
	{
		cpt[j][0] = 0;
		cpt[j][1] = 0;
	}
	//Au fur et à mesure que l'on tombe sur les mêmes nombres, on donne à leur case la valeur 0 pour ne pas retomber dessus
	for (int n = 0; n < nbDist; n++)
	{		
		if(seqList[n] != 0){
			cpt[n][0] = seqList[n];			
			for (int m = n; m < nbDist; m++)
			{
				if(seqList[m] == cpt[n][0]){
					cpt[n][1]++;
					seqList[m] = 0;
				}
			}
		}
	}
	//On trouve la fréquence max et on détermine le numéro de la séquence ayant le plus de "voisines" à Dmin
	int max = cpt[0][1];
	int pivot = cpt[0][0];
	
	for (int n = 0; n < nbDist; n++)
	{
		if(cpt[n][1] > max){
			max = cpt[n][1];
			pivot = cpt[n][0];
		}
	}
	return pivot;	
}

//Fonctions pour libérer les mallocs
void libereFamille(Famille F){	
	free(F.ns);	
}

void libereAllFamille(Famille *AllF){
	for (int i = 0; i < 20; i++)
	{
		libereFamille(AllF[i]);
	}
	free(AllF);
}
