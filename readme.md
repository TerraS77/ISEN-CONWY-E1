```rs
  ________  ___       ________  ________          _______   ________   ________  ___  ________   _______      
 |\   __  \|\  \     |\   __  \|\   __  \        |\  ___ \ |\   ___  \|\   ____\|\  \|\   ___  \|\  ___ \     
 \ \  \|\ /\ \  \    \ \  \|\  \ \  \|\ /_       \ \   __/|\ \  \\ \  \ \  \___|\ \  \ \  \\ \  \ \   __/|    
  \ \   __  \ \  \    \ \  \\\  \ \   __  \       \ \  \_|/_\ \  \\ \  \ \  \  __\ \  \ \  \\ \  \ \  \_|/__  
   \ \  \|\  \ \  \____\ \  \\\  \ \  \|\  \       \ \  \_|\ \ \  \\ \  \ \  \|\  \ \  \ \  \\ \  \ \  \_|\ \ 
    \ \_______\ \_______\ \_______\ \_______\       \ \_______\ \__\\ \__\ \_______\ \__\ \__\\ \__\ \_______\
     \|_______|\|_______|\|_______|\|_______|        \|_______|\|__| \|__|\|_______|\|__|\|__| \|__|\|_______|
```


# ARCHITECTURE

Notre architecture modulaire permet d'avoir un ensemble de fichiers classés. Notre makefile est lui-même encadré par un script bash run.sh qui transforme les fichiers sources dans le dossier soource en des objets qui sont ensuite compiler dans l'exécutable du Build.

## Blob Engine

Cette librairie contient le fichier source et le fichier header du prototype du Blob. Dans ces fichiers, il y a les différentes caractéristiques du bob ainsi que ce qu'il peut faire.

## Procedural

Cette librairie  contient les fichiers sources et les fichiers headers de la création d'un environnement constitué d'un labyrinthe et un autre environnement constitué de rochers, les deux sont de tailles modifiables et aléatoires.

## GFXLib

Il s'agit de la libraire de l'ISEN dans laquelle certaines modifications ont eu lieu. On notera l'ajout du support de scroll-up et scroll-down (molette souris) et de l'actualisation à chaque frame de la position souris.

## Smart UI

Cette librairie contient l'extension de GFXLib réalisée par l'un des membres du groupe permettant de faciliter la mise en place de boutons, de sliders et de textes.


## Smart Grid

Cette librairie contient tout ce qui concerne l'affichage de la grille, le déplacement, le zoom et l'intéraction sur celle-ci.

## Menu

Cette librairie contient le menu principal et le menu contextuel secondaire à la simulation.
