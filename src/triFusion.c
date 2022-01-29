#include "../headers/triFusion.h"

void fusion(Distance *All, int g, int m, int d) {
	// On a juste deux tableau, deb à mil et mil-1 à fin, qu'on va fusionner
	int i,j,k;
	Distance *tmpAll = malloc((d-g+1)*sizeof(Distance)); 
	if(tmpAll == NULL) {
		fprintf(stderr, "Erreur allocation tmpAll\n");
		exit(EXIT_FAILURE);
	}
	
	i = g; j = m+1; k = 0;
	// on va prendre la plus petite valeur des deux tableau et la mettre dans tmpAll
	while(i < m+1 && j < d+1) {
		if(All[i].dist < All[j].dist) {
			// On compare juste les distances entre elles, mais pour les échange c'est la structure entiere
			tmpAll[k] = All[i]; // Deux structures Distance 
			i++;
		}
		else {
			tmpAll[k] = All[j];
			j++;
		}
		k++; 
	}
	// quand un des deux tableau est fini, on va juste ecrire le reste du tableau
	// va faire un des deux while, ca depend lequel a fini en first
	while(i < m+1) {
		tmpAll[k] = All[i];
		i++;
		k++;
	}
	while(j<d+1) {
		tmpAll[k] = All[j];
		j++;
		k++;
	}
	
	
	for (i = 0; i < d-g+1; i++) {
		// on met tmpAll dans All // i+g pcq g pas forcément 0
		All[i+g] = tmpAll[i];
	}
	// La mémoire de toutes les cases est vidée, reste juste à free le tableau lui même
	free(tmpAll);
}

void triFusion(Distance *All, int g, int d) {
	int m; // g, d et m indices du tableau
	if(g < d) { // Tant que le tableau n'est pas vide
		m = (g + d) / 2;
		triFusion(All, g, m);
		triFusion(All, m+1, d);
		fusion(All, g, m, d);
	}
}


void fileDistancesTriees(Distance *All) {
	// Création d'un fichier stockDistancesTriées.txt avec l'ensemble des distances triées & séquences associées
	FILE *fDist = fopen("stockDistancesTriées.txt", "w");
	if(fDist == NULL) {
		fprintf(stderr,"Echec lors de la création du fichier du stockage des distances triées\n");
		exit(EXIT_FAILURE); 
	}
	int k = 0;
	for (int v = 1; v <= 19; v++)
	{
		for (int w = v+1; w <= 20; w++)
		{
			fprintf(fDist, "%02d %s\n%02d %s    \n\033[33;01mD_%02d_%02d : %.1f\033[00m\n", All[k].v, All[k].V.sequence,
				    All[k].w, All[k].W.sequence, All[k].v, All[k].w, All[k].dist);
			k++;
			fprintf(fDist, "\n");
		}
	}
	fclose(fDist);
	printf("Le fichier stockDistancesTriées.txt a été créé avec succès.\n\033[33mTapez \033[33;01mcat stockDistancesTriées.txt\033[00m \033[33mpour les afficher.\033[033m\n\n");
}