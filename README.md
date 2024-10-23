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
Un executable est inclu dans le dossier bin.

## Principe de la démonstration
Pour lancer la simulation, il faut appuyer sur 1. Une particule violette apparaît, ce qui symbolise le centre du blob. Attention à ne pas déplacer trop vite la souris, dû à la méthode de calcul, cela peut provoquer des évènements non voulus.

En appuyant à nouveau sur 1, une particule sera attaché au blob par un ressort. Si on se déplace assez loin d'une particule, le ressort se brise.
Le lien entre la particule et le centre devient alors un cable.

En appuyant sur 2, le blob se séparera en 2 (une seule partie reste contrôlable).

En appuyant sur 3, le blob se regroupera à nouveau mais ses liens seront brisés (les ressorts deviendront des cables).