#include <stdio.h>
#include <stdlib.h>
#include "distance.h"
// En incluant le header distance.h, est également inclus séquence.h

void fusion(Distance *All, int g, int m, int d);
void triFusion(Distance *All, int g, int d);
// Fonctions pour le tri fusion d'un tableau de structure de données Distance - compléxité o(n*log n)

void fileDistancesTriees(Distance *All);
// Création d'un fichier stockDistancesTriées.txt avec l'ensemble des distances triées & séquences associées