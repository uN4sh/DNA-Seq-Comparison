#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

/* Matrice de distance de Levensetein :
 * 		A	C	G	T	 -
 * 	A	0	2	1	2	1.5
 * 	C	2	0	2	1	1.5
 * 	G	1	2	0	2	1.5
 * 	T	2	1	2	0	1.5
 *	-      1.5     1.5     1.5     1.5
 */
 
/*	Deux séquences :
 * 	v = v1.v2....v (lv)
 *  w = w1.w2....w (lw)
 */
 
struct distance {
	// Stocke les distances entre les paires de séquences contenues dans un répertoire
	Sequence v;
	Sequence w;
	int dist;
};

int compD1(int cv, int cw);
float distanceD1(int v, int w);
