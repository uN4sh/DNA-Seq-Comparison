# 301Project

###15.11

Structure séquence avec un char* et la longueur de la séquence

Fonction d'initialisation (compte les caractères et stocke la chaîne dans la structure)

**Cons :
Double ouverture / fermeture de fichier

**A ajouter : 
sprintf pour prendre un i en argument et pouvoir init la sequence en fonction du i 
 
###20.11

Fonction d'ouverture fichier faite, je vois plus trop l'intérêt d'une structure Séquence, vu que meme si on stocke les ADN dans une string, on peut pas la lire. Donc réouverture de fichier puis lecture de caractère puis comparaisons.

Distance D1 faite à l'arrache // Surement beaucoup trop de comparaisons

###11.12

####**SEQUENCE.H**
**Struct sequence :** un char* pour l'ADN et un int l pour la longueur de la chaîne

**ouvrirFic :** prend un int en argument et ouvre le fichier séquence associé dans le répertoire sequence_ADN

**compterCarac :** prend le numéro de fic en argument, ouvre le fichier, compte les caractères par fgetc, close le fichier et return le nombre de caracts

**initSeq :** créé une structure séquence, compte les caracs, réouvre le fichier et stocke le contenu du fichier dans la char* de la séquence, return la séquence avec l et char*


####**DISTANCE.H**
**Struct distance :** deux struct Séquence et un float pour la distance entre les 2

**compD1 :** comparateur pour D1, prend 2 char en argument et fait les comparaisons selon le tableau de Leveinstein, return un ENTIER
**distanceD1 :**  deux entiers en arguments (numéros de fic), créé une structure distance, initSeq les 2 séquences qu'elle contient
quence 
boucle for : inférieur à la plus grande des deux chaines, fait les comparaisons
deuxieme boucle : valeur absolue de la différence de taille, ajout des 1.5 des blancs
return un float pour D1
// on pourrait changer la fct en Distance, prendre 2 Séquences en argument et return la struct distance 
