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
	if(t != NULL){
		for (int o = 0; o < N; o++)
			F.ns[o] = 0;
		
		int j = 0;
		for (int i = 0; i < N; i++) {
			// Tous les nums de seqs qui étaient dans temp[] sont mis dans tableau ns de la famille
			if((t[i] != 0) && j < N) { 
				F.ns[j] = t[i];
				j++;
			}		
		}
	}
	
	return F;
}

Famille *creaFamilles(Distance *All){
	//Creation du tableau contenant les familles, de taille 20 car il ne peut y en avoir plus de 20 (20 séquences et familles de 1)
	Famille *AllF = malloc (20 * sizeof(Famille));
	int fCount = 0;  // Compte le nombre de familles (pour le if de fin)
	int dCount = 0;  // Curseur dans le tableau Distances
	float Dmin; 
	int cptFamille;  // Nbr de seqs dans la meme famille 
	int dtemp;       // Indice 
	int nbDist = 0;  // Nbr de comparaisons qui ont en commun Dmin ET que des seqs orphelines
	int piv;         // sequence pivot qui a le plus de voisines en Dmin
	int d;			 // Nbr de seqs qui ont le même Dmin en question (pour le for avec j)
	int temp[190] = {0}; // Tableau temporaire pour les numéros de seqs d'une même famille (pour initFamille)
	
	while(familleAllCheck(All)){
		// Tant que y'a encore des familles orphelines
		if(dCount<190 && (familleCheck(All, dCount) == 0)){
			Dmin = All[dCount].dist;
			// Si les 2 premieres seq de la premiere distance sont orph, on la prend comme Dmin
			d = 0;
			nbDist = 0;
			dtemp = dCount;
			cptFamille = 0;
			// Pour l'instant la famille compte 0 seqs
			while(dCount < 190 && (All[dCount].dist) == Dmin){
				// On peut faire ce while vu que les distances sont classées croissantes
				if(familleCheck(All, dCount) == 0)
					nbDist++;
				d++; // increase le nombre de seqs qui ont le même Dmin
				dCount++; // on avance dans le tableau de distance
			}
			dCount = dtemp;	
			piv = pivot(All, dCount, Dmin, nbDist);
			dtemp = 0;
			
			for (int i = 0; i < 190 ; i++)
			{
				temp[i] = 0;
			}
			
			for (int j = dCount; j < (dCount+d); j++)
			{
				// On remplit le tableau temp avec indice dtemp avec le num de seq qui n'est pas pivot
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
			temp[dtemp] = piv;
			cptFamille++;
			// Et si dans la distance y'a pas de seq pivot ça va pas la remplir dans temp ?
			// Bah non justement, une famille à que des comparaisons qui lie le pivot à une autre

			//On élimine les doublons
			for (int m = 0 ; m < 190 ; m++){
				if(temp[m]!=0){
					for (int n = m+1 ; n < 190 ; n++){
						if(temp[n] == temp[m]) temp[n] = 0;						
					}
				}	
			}
			
			AllF[fCount] = initFamille(cptFamille, Dmin, fCount+1, temp);
			familleRep(AllF[fCount]);
			dCount = 0;
			fCount++;
			
			for (int r = 0; r < 190; r++)
			{
				for (int s = 0; s < cptFamille; s++)
				{
					if(temp[s] == (All[r].v)) All[r].V.check = 1;
					else if(temp[s] == (All[r].w)) All[r].W.check = 1;
				}
			}	
		}
		//Dans le cas où une séquence est solitaire à la fin de la répartition
		else if (dCount == 190) {
			int solo = 0;
			int i;
			for (i = 0; i < 190; i++)
			{
				if (All[i].V.check == 0){
					solo = All[i].v;
					Dmin = All[i].dist;
					break;
				}
				else if(All[i].W.check == 0){
					solo = All[i].w;
					Dmin = All[i].dist;
					break;
				}				
			}
				
			for (i = 0; i < 190; i++)
			{
				if(solo == (All[i].v)) All[i].V.check = 1;
				else if(solo == (All[i].w)) All[i].W.check = 1;
				temp[i] = 0;
			}
			
			temp[0] = solo;
			AllF[fCount] = initFamille(1,Dmin,fCount+1,temp);
			familleRep(AllF[fCount]);
			fCount++;			
		}
		else dCount++;	
	}
	
	// Juste pour remplir le reste des cases du tableau de familles
	if(fCount<20){
		for (int i = (fCount+1); i < 20; i++)
		{
			AllF[i] = initFamille(0,0,0,NULL);
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
	if(All[i].V.check == 1 || All[i].W.check == 1)
		return 1;
	return 0;	
}

//Fonction qui permet de savoir si toutes les sequences sont classees
int familleAllCheck(Distance *All){
	
	for (int i = 0; i < 190; i++)
	{
		if((All[i].V.check == 0) && (All[i].V.check == 0)) return 1;
	}
	return 0;
}

//Fonction qui trouve la sequence ayant le plus de "vosines" à une distance Dmin
int pivot(Distance *All, int i, float Dmin, int nbDist){
	//La fonction prend en parametre le tableau des distances, le point de départ de la valeur Dmin, 
	//et le nombre de comparaisons ayant cette meme distance (sans compter celles avec des sequences en famille)
	//Puisque le tableau est trié en fonction des distances, on a le nombre de comparaisons à une meme distance.
	//Pour celles qui n'ont pas de sequences classées, on repertorie les sequences dans un tableau seqList 
	int k = 0;
	nbDist*=2;
	int *seqList = malloc (nbDist * sizeof(int));

	for (int o = 0; o < nbDist; o++)
		seqList[o] = 0;
	
	while(i < 190 && (All[i].dist) == Dmin){
		if(familleCheck(All, i) == 0) {
			seqList[k] = All[i].v;
			k++;
			seqList[k] = All[i].w;
			k++;
		}
		i++;
	}	

	// On initialise un tableau à double entrées, afin de sauvegarder et de mettre en relation les numéros des sequences 
	//  et leurs fréquences d'apparition
	
	int **cpt = NULL;
	cpt = malloc (nbDist * sizeof(int*));
	for (int j = 0; j < nbDist; j++)
		cpt[j] = malloc (2*sizeof(int));

	for (int j = 0; j < nbDist; j++)
	{
		cpt[j][0] = 0;
		cpt[j][1] = 0;
	}
	//Au fur et à mesure que l'on tombe sur les mêmes nombres, on donne à leur case la valeur 0 pour ne pas retomber dessus
	for (int n = 0; n < nbDist; n++)
	{		
		if(seqList[n] != 0) {
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
	free(seqList);

	for (int i = 0; i < nbDist; i++)
		free(cpt[i]);
	free(cpt);

	return pivot;	
}

//Fonctions pour libérer les mallocs
void libereFamille(Famille F){

	if(F.taille>0) free(F.ns);			
}

void libereAllFamille(Famille *AllF){
	for (int i = 0; i < 20; i++)
	{
		libereFamille(AllF[i]);		
	}	
	free(AllF);
}

void afficheFamille(Famille *AllF){
	printf("Les familles de séquences :\n");
	for (int i = 0; i < 20; i++)
	{
		if(AllF[i].taille != 0){
			
			printf("Famille n°%d : ", AllF[i].nF);
			for (int j = 0; j < AllF[i].taille; j++)
				printf("%d ",AllF[i].ns[j]);
			printf("\n");			
		}		
	}
}
