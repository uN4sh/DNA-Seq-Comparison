# Comparaison de séquences d’ADN

Le but de ce projet est de comparer des séquences d’ADN entre elles en utilisant la **distance de Levenshtein** pour déterminer des **familles de séquences** (correspondant à des familles d’organismes) et en déduire la **séquence consensus** pour chacune des familles, c'est à dire la séquence dans laquelle chaque caractère correspond à la lettre rencontrée le plus fréquemment à cette position dans la famille.

## Implémentation

Ce projet s'organise en trois parties :

- Une première dans laquelle **deux méthodes de calcul des distances de Levenshtein** entre les séquences ADN sont implémentées ; l'exécution de cette partie du projet génère un fichier texte rassemblant l'ensemble des 190 couples de séquences avec la distance de Levenshtein qui les sépare l'une de l'autre.
- La deuxième partie **regroupe les séquences par familles d'organismes** partageant une distance minimale entre elles ; chacune des familles de séquence est ensuite stockée dans un même répertoire.
- On détermine ensuite la **séquence consensus de chaque famille**, c'est à dire la séquence dans laquelle chaque caractère correspond à la lettre rencontrée le plus fréquemment à cette position dans la famille.

## Compétences ciblées

- Manipulation et lecture des fichiers en C
- Allocation et libération de la mémoire
- Implémentation d'un algorithme adapté pour le calcul de la Distance de Levenshtein
- Implémentation d'un algorithme de tri en C
- Séparation d'un projet en plusieurs partie en utilisant un Makefile

## Exécution

### Partie 1
- `main1` pour compiler la partie1
- `partie1` pour l'exécuter
- `debug1` pour l'exécuter sous Valgrind

### Partie 2
- `main2` pour compiler la partie2
- `partie2` pour l'executer
- `debug2` pour l'executer sous Valgrind

### Partie 3
- `main3` pour compiler la partie3
- `partie3` pour l'executer
- `debug3` pour l'executer sous Valgrind

### Utilitaire
- `clean`  pour nettoyer le répertoire
- `archive` pour construire une archive du projet 
