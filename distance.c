#include "distance.h"

int compD1(int cv, int cw) {
	if ( (cv == 'A' && cw == 'C') || (cv == 'C' && cw == 'A') || (cv == 'A' && cw == 'T') || (cv == 'T' && cw == 'A') 
	|| (cv == 'C' && cw == 'G') || (cv == 'G' && cw == 'T') || (cv == 'T' && cw == 'G') ) {
		return 2;
	}
	if ( (cv == 'A' && cw == 'G') || (cv == 'G' && cw == 'A') || (cv == 'C' && cw == 'T') || (cv == 'T' && cw == 'C') ) {
		return 1;
	}
	return 0;
}


float distanceD1(int v, int w) {
	float dist = 0.0;
	int vl = compterCarac(v);
	int wl = compterCarac(w);

	FILE *fv = ouvrirFic(v);
	FILE *fw = ouvrirFic(w);
	
	int cv, cw; //on va fgetc dans la seq v et w et les comparer
	
	if (vl > wl) {
		for (int i = 0; i < wl; i++) //vl plus grand
		{
			cv = fgetc(fv);
			cw = fgetc(fw);
			
			dist += compD1(cv, cw);
		}
		
		for (int i = 0; i < (vl-wl); i++)
			dist += 1.5;
	}
	else {
		for (int i = 0; i < vl; i++) //wl plus grand
		{
			cv = fgetc(fv);
			cw = fgetc(fw);
			
			dist += compD1(cv, cw);
		}
		
		for (int i = 0; i < (wl-vl); i++)
			dist += 1.5;
	}
	
	
	fclose(fv);
	fclose(fw);
	return dist;
}


float distanceD1v2(int v, int w) {
	Distance D1;
	//D1 = malloc(sizeof(Distance));
	D1.V = initSeq(v);
	D1.W = initSeq(w);
		
	for (int i = 0; i < D1.V.l || i < D1.W.l; i++) 
	{
		D1.dist += compD1(D1.V.sequence[i], D1.W.sequence[i]);
	}
	
	for (int i = 0; i < fabs(D1.V.l - D1.W.l); i++)
		D1.dist += 1.5;
	
	return D1.dist;
}