                                  Iryol.io

Copyright (C) HOSSAIN Shajjad, KHELILI Adrian, BOUICHE Ryma, MOULAY LAKHDAR Sarah

- ------ 'make main' pour complier la version final du jeu ------ -
- les touches
    "UP" et "DOWN" pour changer le volume de musique de fond
    "LEFT" et "RIGHT" pour changer de musique

0. make help : pour afficher la liste des recettes
1. make clean : supprime bin et obj
2. les fichers source
    src/mainTests contient les fichers sources pour les teste unitaire
    src/base contient les classe de base comme Vec2 Color Rectanle Cercle et d'autre
    src/core le coeur de notre jeu 
    src/sfml la librarie d'ihm 

3. description:
pour commancer le jeu possède 3 mode différent jeu libre, niveau et multijoueur.
le choix de mode se fait au début de partie.

4. format pour enregistrer un niveau
    terrain: Terrain
    nombre de murs : entier positive
    tous les murs : Murs
    nombre de petits cercles : entier positive
    tous les petits cercle : Cercles
    nombre de cercles du joueur : entier positive
    les cercles du joueur : Cercle
    nombre de point d'arrivé : entier positive
    les point d'arrivé : Cercle
5. format d'audio
    les musique du fond sont tous des ficher .ogg numéroté de 1 à n.
    Il souffit donc placer les musiques qu'on veut le dossier.
    attention il faut mettre à jours MAX_AUDIO_TRACKS dans FenetreSFML