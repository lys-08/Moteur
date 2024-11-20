# Moteur
Ce projet de Moteur Physique a été réalisé dans le cadre du cours de mathématiques et physique pour le jeu vidéo à l'UQAC (Université du Québec à Chicoutimi). Il est actuellement en cours de développement. La durée totale du projet sera de 4 mois.

## Arborescence
Le projet présente l'arborescence suivante :
    * Moteur/
      * src/
      * tests/
      * bin/

Dans le dossier source se trouvent tous les headers et les fichiers sources qui constituent le projet. Dans le dossier tests se trouvent tous les fichiers de tests du projet.

## Comment lancer ce projet ?
Un executable est inclu dans le dossier bin/.

## Principe de la démonstration
Lorsque vous avez lancé l'executable, une fenêtre s'ouvre. Une interface présente les différents objets pouvant être tirés, qui sont, avec leur touche associée :
    - **"B" :** Une boîte carrée dont le centre de masse vaut 20kg est lancée
    - **"C" :** Un cône dont le centre de masse vaut 30kg est lancé
    - **"P" :** Un pavé dont le centre de masse vaut 20kg est lancé
    - **"Z" :** Une boîte carrée dont le centre de masse vaut 20kg est lancée à la fois selon z et selon x
    - **"Q" :** Une boîte carrée dont le centre de masse vaut 20kg est lancée à la fois selon y et selon x
  
Il est également possible de changer le point d'application de la force, ainsi que son orientation. Voici les cas possibles :
    - **"1" :** Le point d'application est décalé de 20 unités selon l'axe z
    - **"2" :** Le point d'application est décalé de 20 unités selon l'axe y
    - **"3" :** Le point d'application est décalé de 20 unités selon l'axe x

Pour chaque objet, il est possible de modifier le point d'application.

Enfin, il est possible de lancer les **tests** en cliquant sur la touche **"t"**. Des messages s'afficheront dans le terminal indiquant si les tests de chaque classes sont bien passés ou non.