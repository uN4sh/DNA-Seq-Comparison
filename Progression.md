# 301Project

### 15.11
 
### 20.11

### 11.12

### 19.12
Bon, j'ai tout effacé parce que beaucoup de choses ont changé, voilà le résumé du programme :

#### **MAKEFILE**
**make main1** : Compile l'ensemble des fichiers de la partie1

**make run1** : Exécute la partie1

**make debug1** : Exécute la partie1 sous Valgrind

**make clean** : Supprime l'ensemble des fichiers .o, l'exécutable ainsi que les 2 fichiers textes créés lors de l'éxécution

#### **DEROULEMENT ET SUITE**
L'exécution de la partie1 créera le fichier stockDistances.txt comprenant l'ensemble des 190 distances calculées ainsi que les séquences numérotées associées.

Elle ouvrira les fichiers, calculera les distances et les stockera proprement dans un tableau de 190 structures "Distance" qu'on peut faire afficher dans le terminal ou laissé dans le fichier texte créé.

L'ensemble de la mémoire allouée aux séquences, aux fichiers et au tableau, sera libérée.

*// Note : Tout fonctionne avec la distance D1, j'ai pas touché une seule seconde à D2, bien que j'ai déjà toutes les fonctions par un subtil cambriolage*

**Ebauche de partie 2 :** Fonctions de triFusion mises en oeuvre sur le tableau des distances et création d'un nouveau fichier stockDistancesTriées.txt

**Suite :** Il faudrait maintenant faire en sorte de partir de la distance minimum et trouver la séquence S qui a le plus de Dmin avec d'autres séquences, et en faire une famille..

Ou alors faudrait faire D2 mdr..

#### **SEQUENCE.H**
**Struct Sequence :** Structure séquence comprend la longueur l de la séquence et un tableau de char pour l'ADN

**openFic :** Ouvre le fichier associé à l'entier dans le repertoire mis en argument par l'éxecution (ici : sequences_ADN)

**charCounter :** Pour un numéro de séquence donnée, retourne le nombre de caractères que contient son fichier

**initSeq :** Initialise une séquence en lui assignant d'abord sa taille puis sa chaîne de caractères 

*// Note : double ouverture de fichier ici pour compter puis assigner. On pourrait combiner le tout en une ouverture avec un strlen() ?*

**libereSeq :** Pour une structure Sequence donnée, free de la mémoire allouée à la chaîne ADN

#### **DISTANCE.H**
**Struct Distance :** Comprend 2 Struct Séquences (ADN & taille) + n° de séquence associé, ainsi qu'un float pour la distance
	
**charCompare :** Comparateur de caractères selon la matrice de distances (Pour D1)

**distanceD1 :** Distance D1, retourtant une structure Distance, expliquée en détail dans le fichier distance.c

**StockDistances :** Stockage de toutes les distances entre paires de séquences dans un tableau de structure Distance

**afficherDistance & afficheAll** Fonctions pour l'affichage et la mise en forme de toutes les distances & séquences associées 

**fileDistances :** Création d'un fichier stockDistances.txt avec l'ensemble des distances & séquences associées

**libereMemoire :** Libère les 2 champs de séquences compris dans une structure Distance
**libereAll :** Libération de mémoire de toutes les séquences dans le tableau de struct Distance
