# LINFO1252-Projet1-Groupe3-10

Projet réalisé dans le cadre du cours d'informatique LINFO1252 donné par le Pr. Riviere Etienne.
Lien vers le répo : https://github.com/Jackli77/LINFO1225_P1

## Objectif

Ce repertoire a pour but de tester les performances de programmes multithreadés pour un nombre différent de thread  et de donner les résultats sous une forme graphique.

### Contenu du repertoire

Makefile : Permet de lancer les programmes et de clean les fichiers résiduels.\
lect_read.c : Résout le problème des lecteurs écrivians a l'aide des sémaphores de la librairie POSIX.\
mylect_read.c : Résout le problème des lecteurs écrivians a l'aide des sémaphores de mysem.h.\
matplot_tuto(1).py : Trace les graphiques de performance depuis les données csv.\
mysem.h : Implémente des sémaphores binaires à l'aide de l'inline assembly.\
semsem.h : Implémente les counting sémaphores.\
philo.c : Résout le problème des philosophes à l'aide des sémaphores de la librairie POSIX.\
myphilo.c : Résout le problème des philososphes à l'aide des sémaphores de mysem.h.\
prodcons.c : Résout le problème des producteurs consommateurs à l'aide des sémaphores de la librairie POSIX.\
myprodcons.c : Résout le problème des producteurs consimmateurs à l'aide des sémaphores de mysem.h.\
script.sh : Lance les problèmes et effectue les tests de performance.\
tatas.h : Implemente test and test and set.\
test.c : Teste les programmes test and set.\
testandset.h  : Impemente test and set.\

### Pré-requis

Afin de faire fonctionner le code contenu dans le repo, vous aurez besoin de:

- Make
- Gcc
- Python3
- Matplotlib
- Une machine 8 coeurs
 
### Lancement du code

Dans votre terminal, exécutez la fonction make all. Cette commande compile les différents fichiers et lance le script qui effectuant le test de performances.

### Logiciels utilisés
[Fedora](https://getfedora.org/fr/)


### Auteurs
* **Guang Li** _alias_ [@Jackli77](https://github.com/Jackli77)
* **Charles Lohest** _alias_ [@chlohest](https://github.com/chlohest)
