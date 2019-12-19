#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Ce fichier sequence.h est inclus dans chacun des autres fichiers via les autres header qui le contiennent

// Structure séquence comprend la longueur l de la séquence et un tableau de char pour l'ADN
struct Sequence {
	char* sequence; 
	int l; 
};
typedef struct Sequence Sequence;

// Le char** argv en argument de chacune des fonctions sert à préciser le répertoire d'ouverture des fichiers

FILE *openFic(int i, char** argv);
//Ouvre le fichier associé à l'entier dans le repertoire mis en argument par l'éxecution (ici : sequences_ADN)
int charCounter(int nf, char** argv);
// Pour un numéro de séquence donnée, retourne le nombre de caractères que contient son fichier
Sequence initSeq(int nf, char** argv);
// Initialise une séquence en lui assignant d'abord sa taille puis sa chaîne de caractères
void libereSeq(Sequence S);
// Pour une structure Sequence donnée, free de la mémoire allouée à la chaîne ADN
