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
			int k = 2;
			while(k < AllF[i].taille){
				//il faut comparer chaque séquence de la famille entre elles et les mettre
				//côte à côte.
				//ajoutSequence
				
				k++;
			}
			//calculCons(All[i]);	
						
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
	
	e1->suiv = list;
	e2->suiv = e1;
	free(temp1.sequence);
	free(temp2.sequence);

	return e2;	
}

Alignement *ajoutSequence(Alignement*list, int seq, int i){
	
	
	
	return list;
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
