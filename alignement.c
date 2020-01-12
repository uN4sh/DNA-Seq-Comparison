#include "alignement.h"

void creaConsensus(Famille *AllF, Distance *All, char** argv){
	int i = 0;
	
	while((AllF[i].taille) != 0){
		//Si il y a une seule séquence dans une famille, elle deviens donc la séquence consensus
		if(AllF[i].taille == 1){ 
			Sequence temp;
			temp = initSeq(AllF[i].ns[0], argv);
			AllF[i].seqCons = malloc ((temp.l)+1 * sizeof(char));
			for (int j = 0; j < temp.l; j++)
				AllF[i].seqCons[j] = temp.sequence[j];
			free(temp.sequence);
		}
		//Sinon
		else {
			Alignement* list = NULL;
			int seqMax = 0;
			int cpt;
			for (int j = 0; j < AllF[i].taille; j++)
			{
				cpt = charCounter(AllF[i].ns[j], argv);
				if(cpt > seqMax) seqMax = cpt;
			}		
			seqMax++; //pour la valeur de fin de séquence
			
			//Prends les deux premières cases car la première est le pivot et est par définition, avec la deuxième, le couple le plus proche.
			list = initAlignement(list, AllF[i].ns[0], AllF[i].ns[1], seqMax, argv); 
			
			Alignement *temp;
			for(int k = 2; k < AllF[i].taille; k++){
				int cpt = 0;
				int comp = 0;
				float dmin;
				temp = list;
				int min = Dmin(temp->numSeq, AllF[i].ns[k], All);
				
				while(temp){
					dmin = Dmin(temp->numSeq, AllF[i].ns[k], All);
					if(dmin < min){
						min = dmin;
						comp = cpt;
					}
					cpt++;
					temp = temp->suiv;					
				}
				ajoutSequence(list, AllF[i].ns[k], comp, seqMax, argv);
			}
			
			calculCons(AllF, list, i, seqMax);	
			
			while(list){
			list = libereAlignement(list);
			}	
		}
		i++;		
	}
}

Alignement *initAlignement(Alignement* list, int seq1, int seq2, int seqMax, char** argv){
	Alignement* e1 = malloc (sizeof(Alignement));
	Alignement* e2 = malloc (sizeof(Alignement));
	Sequence temp1, temp2;
	temp1 = initSeq(seq1, argv);
	temp2 = initSeq(seq2, argv);
	e1->numSeq = seq1;
	e2->numSeq = seq2;
	e1->seq = malloc (seqMax * sizeof(char));
	e2->seq = malloc (seqMax * sizeof(char));
	int i = 0;
	while(temp1.sequence[i] != '\0'){
		e1->seq[i] = temp1.sequence[i];
		i++;		
	}
	if(temp1.l < seqMax){
		while(i < seqMax-1){
			e1->seq[i] = '*';
			i++;
		}			
	}
	e1->seq[i] = '\0';
	i = 0;
	while(temp2.sequence[i] != '\0'){
		e2->seq[i] = temp2.sequence[i];
		i++;		
	}
	if(temp2.l < seqMax){
		while(i < seqMax-1){
			e2->seq[i] = '*';
			i++;
		}			
	}
	e2->seq[i] = '\0';
	
	e2->suiv = list;
	e1->suiv = e2;
	free(temp1.sequence);
	free(temp2.sequence);

	return e1;	
}


void ajoutSequence(Alignement *list, int seq, int i, int seqMax, char **argv){	
	Alignement *e;
	Sequence s = initSeq(seq, argv);
	for (int j = 0; j < i; j++)
		list = list->suiv;
	e = malloc(sizeof(Alignement));
	e->suiv = list->suiv;
	list->suiv = e;
	e->numSeq = seq;
	e->seq = malloc(seqMax * sizeof(char));
	int k = 0;
	while(s.sequence[k] != '\0'){
		e->seq[k] = s.sequence[k];
		k++;		
	}
	if(s.l < seqMax){
		while(k < seqMax-1){
			e->seq[k] = '*';
			k++;
		}			
	}
	e->seq[k] = '\0';
	
	free(s.sequence);
	
}

void calculCons(Famille *AllF, Alignement *list, int i, int seqMax){
	
	int j;
	Alignement *temp;
	char *seqCons = malloc(seqMax * sizeof(char));
	int *freq = malloc(5 * sizeof(int));
	
	for (j = 0; j < seqMax-1; j++) {
		temp = list;
		for(int v = 0; v < 5; v++)
		freq[v] = 0;
		while(temp){
			//printf("oui\n");
			switch(temp->seq[j]){
			case 'A':
				freq[0]++;
				break;
			case 'T':
				freq[1]++;
				break;
			case 'C':
				freq[2]++;
				break;
			case 'G':
				freq[3]++;
				break;
			case '*':
				freq[4]++;
				break;
			default:
				fprintf(stderr, "Probleme, sequence ne contient pas les bons caractères\n");
				exit(EXIT_FAILURE);	
				break;	
			}
			
			temp = temp->suiv;
		}
				
		int max = 0;
		int check = 0;
		int final = 0;
		for (int r = 0; r < 5; r++)
		{
			if(max < freq[r]){
				max = freq[r];
				check = 0;
				final = r;
			}
			else if(max == freq[r])
				check++;
		}
		if(check > 0)
		final = 4;
		
		//printf("bonsoir final %d\n", final);
		switch(final){
			case 0:
				seqCons[j] = 'A';
				break;
			case 1:
				seqCons[j] = 'T';
				break;
			case 2:
				seqCons[j] = 'C';
				break;
			case 3:
				seqCons[j] = 'G';
				break;
			case 4:
				seqCons[j] = '.';
				break;
			default:
				fprintf(stderr, "Probleme, sequence ne contient pas les bons caractères\n");
				exit (EXIT_FAILURE);
				break;
		}
	}	
	
	seqCons[j] = '\0';
	AllF[i].seqCons = seqCons;	
	
	free(freq);
}

float Dmin(int v, int w, Distance *All){
	
	for (int i = 0; i < 190; i++)
	{
		if(All[i].v == v && All[i].w == w)
			return All[i].dist;
		else if(All[i].w == v && All[i].v == w)
			return All[i].dist;
	}
	
	fprintf(stderr, "Séquences non trouvées pour renvoyer Dmin\n");
	return EXIT_FAILURE;	
}

Alignement *libereAlignement(Alignement* list){
	if(!list)return NULL;
	free(list->seq);
	Alignement *e;
	e = list;
	list = list->suiv;
	free(e);
return(list);
}
