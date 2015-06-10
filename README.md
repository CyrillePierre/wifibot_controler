# Wifibot controler

Ce petit programme permet de piloter de façon très basique un Wifibot. On peut
contrôler la vitesse des moteurs de droite et de gauche en utilisant de simples
instructions écrites dans un format compréhensible par un humain.

## Téléchargement du programme

Grâce à **Gitlab**, il est possiblke de télécharger le programme de plusieurs façons
:
* en clonant le projet avec git
* en téléchargeant une archive du projet

### Récupération du projet avec git

La meilleure méthode pour récupérer le projet est d'utiliser les commandes de
git. Il existe également des interfaces graphiques pour manipuler Git mais
j'expliquerai uniquement la méthode en ligne de commande. Dans tous les cas, il
faut avoir installé Git au préalable.

Pour télécharger le projet, il suffit de taper la commande suivante :

	git clone https://git.cpierre.ovh/cyrille/wifibot_controler.git

Cette commande va créer un répertoire nommé **wifibot_controler** qui contiendra
le code source ainsi que le **Makefile** qui permettra de compiler le programme.

L'avantage d'utiliser git, c'est que l'on peut ensuite mettre à jour
l'application en utilisant la commande suivante :

	git pull

On peut ensuite passer à l'étape de compilation

### Téléchargement d'une archive du projet

Cette méthode n'est pas la plus aproprié pour récupérer le projet puisqu'elle ne
permet pas de suivre facilement ses évolutions. En effet, si l'on télécharge le
projet sous la forme d'une archive, on ne récupère que les fichiers sans le système
de versionnage.

Voici un lien qui permet de récupérer le projet au format zip :
[wifibot_controler](https://git.cpierre.ovh/cyrille/wifibot_controler/repository/archive.zip?ref=master).
Il est également possible de télécharger le projet sous d'autres format en
cliquant sur le triangle à droite du bouton **download zip** en haut à droite.

On peut ensuite passer à l'étape de compilation

## Compilation

Lorsqu'il vient d'être téléchargé, le répertoire du projet ne contient pas
encore d'exécutable. C'est pourquoi il est nécessaire de le compiler.

La compilation nécessite cependant quelques prérequis. Le code a été optimisé
pour être compiler sur **Raspberry Pi** avec le système d'exploitation **Raspbian**.
Le projet doit donc être compilé dans un environnement Linux équipé de la
commande `make` ainsi que le compilateur **g++-4.6** ou une version ultérieure
(si une autre version de g++ est utilisée, modifier le Makefile).

Pour compiler, il faut suffit de se placer à la racine du projet et de taper la
commande suivante :

	make

Si la compilation se déroule correctement, un exécutable nommé
**wifibot_controler** sera générée.