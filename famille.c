#include "famille.h"
// En incluant le header famille.h, sont également inclus triFusion.h, distance.h & sequence.h

Famille initFamille(int N, float Dmin, int nF, int *t, int pivot){
	// Creation et allocation du nombre de séquences * la taille d'un int pour une famille
	Famille F;
	F.ns = malloc (N * sizeof(int)); if(!F.ns) exit(0);

	// On assigne à la famille son numéro, son nombre de séquence, son pivot, et Dmin la distance par rapport à son pivot
	F.nF = nF;
	F.taille = N;
	F.pivot = pivot;
	F.Dmin = Dmin;

	//Remplissage du tableau contenant les numéros des séquences de la famille
	if(t != NULL){
		int j = 0;
		for (int i = 0; i < N; i++) {
			// Tous les nums de seqs qui étaient dans temp[] sont mis dans tableau F.ns de la famille
				F.ns[j] = t[i];
				j++;	
		}
		int temp;
		if(F.ns[0] != pivot){
			for (int i = 0; i < N; i++)
			{
				if(F.ns[i] == pivot){
					temp = F.ns[0];
					F.ns[0] = F.ns[i];
					F.ns[i] = temp;
				}
			}
		}
	}
	
	F.seqCons = NULL;
	
	return F;
}

Famille *creaFamilles(Distance *All){
	// Creation du tableau contenant les familles, de taille 20 car il ne peut y en avoir plus de 20 (20 séquences et familles de 1)
	Famille *AllF = malloc (20 * sizeof(Famille)); if(!AllF) exit(0);
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
		// Tant que y'a encore des familles orphelines, condition de fin de boucle
		if(dCount<190 && (familleCheck(All, dCount) == 0)){
			Dmin = All[dCount].dist;
			// Le tableau etant trié, la première dMin est à dCount = 0
			d = 0;
			nbDist = 0;
			dtemp = dCount;
			cptFamille = 0;
			// Pour l'instant la famille compte 0 seqs
			while(dCount < 190 && (All[dCount].dist) == Dmin){
				// On peut faire ce while vu que les distances sont classées croissantes
				if(familleCheck(All, dCount) == 0) {
					// Aucune des séquences de la comparaison n'a de famille 
					nbDist++;
				}
				
				d++; // increase le nombre nombre de comparaisons de même distance Dmin
				dCount++; // on avance dans le tableau de distance
			}
			dCount = dtemp;	
			
			// On cherche maintenant le n° de séquence pivot de toutes ces séquences ayant le même Dmin
			piv = pivot(All, dCount, Dmin, nbDist);
			dtemp = 0;
			
			// On a maintenant la séquence pivot ainsi que le Dmin, on va chercher toutes les seqs en lien et de meme Dmin
			
			for (int j = dCount; j < (dCount+d); j++)
			{
				// On remplit le tableau temp avec le num de seq qui n'est pas pivot
				if((familleCheck(All, j) == 0) && (All[j].v == piv)) {
					temp[dtemp] = All[j].w;
					dtemp++;
					cptFamille++; // Nombre de séquences dans la famille
				}
				else if((familleCheck(All, j) == 0) && (All[j].w == piv)) {
					temp[dtemp] = All[j].v;
					dtemp++;
					cptFamille++; // Nombre de séquences dans la famille
				}	
			}
			// Et on fait entrer la séquence pivot à la fin du tableau temp
			temp[dtemp] = piv;
			cptFamille++;
			
			// Double boucle pour cocher la séquence dans tout le tableau All des distances
			for (int r = 0; r < 190; r++) {
				// Pour passer en CHECK toutes les séquences du même numéro
				for (int s = 0; s < cptFamille; s++) {
					if(temp[s] == (All[r].v)) All[r].V.check = 1;
					else if(temp[s] == (All[r].w)) All[r].W.check = 1;
				}
			}				
			//On élimine les doublons dans le tableau temp, pas nécessaire mais au cas où
			for (int m = 0 ; m < 190 ; m++){
				if(temp[m]!=0){
					for (int n = m+1 ; n < 190 ; n++){
						if(temp[n] == temp[m]) temp[n] = 0;						
					}
				}	
			}
			
			// On créé la famille avec tous les paramètres, ainsi que son répertoire avec ses fichiers
			// cptFamille = N = = taille nbr de séquences dans la famille
			AllF[fCount] = initFamille(cptFamille, Dmin, fCount+1, temp, piv);
			familleRep(AllF[fCount]);

			dCount = 0;
			fCount++;
		}

		//Dans le cas où une séquence est solitaire à la fin de la répartition
		else if (dCount == 190) {
			solo(AllF, All, fCount, Dmin);
			fCount++;
		}

		else dCount++;	
	}
	
	// Juste pour remplir le reste des cases du tableau de familles
	if(fCount<20){
		for (int i = fCount; i < 20; i++)
			AllF[i] = initFamille(0,0,0,NULL,0);			
	}
	
	return AllF;
}

void solo(Famille *AllF, Distance *All, int fCount, float Dmin) {
	int solo = 0;
	int i;
	int temp[1] = {0};
	for (i = 0; i < 190; i++) {
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
			
	AllF[fCount] = initFamille(1,Dmin,fCount+1,temp, solo);
	familleRep(AllF[fCount]);	
}

//Fonction création répertoire qui prends le numéro de la famille en argument pour le nom du dossier
void familleRep(Famille F){
	char creaRep[100];
	char cpSeq[100];
	char check[30];
	sprintf(check, "rm -rf Famille%02d",F.nF); //Suppression du dossier si il existait déjà
	system(check);
	sprintf(creaRep, "mkdir Famille%02d",F.nF); //Creation du dossier avec le numéro de la famille
	system(creaRep);
	for (int i = 0; i < F.taille; i++)
	{
		//chaque sequence de la famille est copiee vers ce dossier
		sprintf(cpSeq, "cp sequences_ADN/seq%02d.txt Famille%02d/seq%02d.txt",F.ns[i],F.nF,F.ns[i]);
		system(cpSeq);
	}		
} 

//Fonction qui trouve la sequence ayant le plus de "voisines" en une distance Dmin
int pivot(Distance *All, int i, float Dmin, int nbDist){
	//La fonction prend en parametre le tableau des distances, le point de départ de la valeur Dmin, 
	//et le nombre de comparaisons ayant cette meme distance (sans compter celles avec des sequences en famille)
	//Puisque le tableau est trié en fonction des distances, on a le nombre de comparaisons à une meme distance.
	//Pour celles qui n'ont pas de sequences classées, on repertorie les sequences dans un tableau seqList 
	int k = 0;
	nbDist *= 2; // Pour avoir le nombre de séquences
	// On classera tous les n° de séquences libres et en Dmin dans ce tableau
	int *seqList = malloc (nbDist * sizeof(int)); if(!seqList) exit(0);

	/*
	for (int o = 0; o < nbDist; o++)
		seqList[o] = 0;
	*/
	while(i < 190 && (All[i].dist) == Dmin){
		// On parcourt juste le nombre compaisons au même Dmin
		if(familleCheck(All, i) == 0) {
			// Si les séquences en question n'ont pas de famille, on les stocke dans seqList
			seqList[k] = All[i].v;
			k++;
			seqList[k] = All[i].w;
			k++;
		}
		i++;
	}	

	// On initialise un tableau à double entrées, afin de sauvegarder et de mettre en relation les numéros des sequences 
	//  et leurs fréquences d'apparition
	// Allocation du tableau à double entrée : cpt[nbDist][2]
	int **cpt = NULL;
	cpt = malloc (nbDist * sizeof(int*)); if(!cpt) exit(0);
	for (int j = 0; j < nbDist; j++)
		cpt[j] = malloc (2*sizeof(int));

	for (int j = 0; j < nbDist; j++)
	{
		cpt[j][0] = 0;
		cpt[j][1] = 0;
	}
	//Au fur et à mesure que l'on tombe sur les mêmes seq de seqList, on donne à leur case la valeur 0 pour ne pas retomber dessus
	for (int n = 0; n < nbDist; n++)
	{		
		if(seqList[n] != 0) {
			cpt[n][0] = seqList[n];
			// En 0, la séquence, et en 1, le nombre d'apparition
			// Exp : cpt[][1] = 3 apparitions			
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
			max = cpt[n][1]; // Le max est la fréquence d'apparition
			pivot = cpt[n][0]; // Le pivot prend le numéro de la séquence
		}
	}

	free(seqList);
	for (int i = 0; i < nbDist; i++)
		free(cpt[i]);
	free(cpt);

	return pivot;	
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

//Fonction pour libérer les mallocs
void libereAllFamille(Famille *AllF){
	
	for (int i = 0; i < 20; i++)
	{
		free(AllF[i].ns); // On libère le tableau de séquences de chaque famille
		if(AllF[i].seqCons != NULL)
			free(AllF[i].seqCons);
	}	
	free(AllF);
}

void afficheFamille(Famille *AllF){
	printf("\033[31;01mLes familles de séquences :\033[00m\n");
	int i = 0;
	while(AllF[i].taille != 0){
			printf("\033[31;01m    Famille n°%d :\033[00m ", AllF[i].nF);
			for (int j = 0; j < AllF[i].taille; j++)
				printf("\033[31m%d \033[00m",AllF[i].ns[j]);
			if(AllF[i].seqCons != NULL)
					printf("\nSéquence consensus %d : %s", (i+1), AllF[i].seqCons);
			printf("\n");
			i++;				
		}		
	printf("\n");
}
