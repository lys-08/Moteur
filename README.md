# Moteur
Ce projet de Moteur de jeu a été réalisé dans le cadre du cours de mathématiques et physique pour le jeu vidéo à l'UQAC (Université du Québec à Chicoutimi). Il est actuellement en cours de développement. La durée totale du projet sera de 4 mois.

## Arborescence
Le projet présente l'arborescence suivante :
    * Moteur/
      * src/
      * tests/

Dans le dossier source se trouvent tous les headers et les fichiers sources qui constituent le projet. Dans le dossier tests se trouvent tous les fichiers de tests du projet.

## Comment lancer ce projet ?
Pour lancer le projet, il faut créer un projet vide dans Visual Studio depuis le project creator d'OpenFrameworks, et ajouter les fichiers de code à l'intérieur de votre nouveau projet. Pour cela, il suffit de faire un clic droit sur le dossier src de votre projet, puis, dans "Nouveau", cliquer sur "ajouter un élément existant", et ajouter les fichiers sources et tests qui se trouvent dans les dossiers *src* et *test*.

Ensuite, il faut générer le projet en release dans la barre d'outils de Visual Studio.

## Comment fonctionne le projet ?
Lorsque vous avez lancé l'executable, une fenêtre s'ouvre. Une interface présente les différentes particules pouvant être tirées :
    - **Ping Pong Ball (touche 1) :** masse de 3kg
    - **Basket Ball (touche 2) :** masse de 10kg
    - **Fire Ball (touche 3) :** masse de 30kg
    - **Canon Simple Ball (touche 4) :** masse de 100kg

En appuyant sur la touche correspondante, on peut choisir la particule à tirer. Pour tirer, il suffit de faire un **clic gauche** avec la souris. **Plus le curseur est loin du canon, plus la vitesse de la particule augmente**.

Pour lancer les tests, il faut cliquer sur la touche **t**. Les tests se lance et le résultat d'affichera dans le terminal qui s'est ouvert avec la fenêtre.