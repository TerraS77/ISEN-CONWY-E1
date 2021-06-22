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

# Utilisation et Fonctionnalitées

## Menu Principal

**Accès à 4 simulations différentes :**
#### Simulation Labyrinthe
On place un Blob dans un labyrinthe généré procéduralement et il doit trouver la nourriture dans celui-ci.
#### Simulation Environnement
On place un Blob dans un environnement généré procéduralement où il devra trouver de la nourriture pour survivre
#### Simulation Vide
On place un Blob dans un espace vide afin de voir son évolution sans aucun obstacle.
#### Simulation Custom
On place un Blob dans un environnement que l'on peut modifier selon nos envies.


## Navigation et Controle

- Clic Droit appuyé + déplacement souris : déplacement dans la grille
- Scroll-Up/Scroll-Down : Zoom/Dezoom de la grille
- Clic Gauche sur une case de la grille : apparition d'une cellule
- Touche F : Permet de selectionner la nourriture afin de la poser sur la grille
- Touche B : Permet de séléctionner le Blob afin de le poser sur la grille
- Touche W : Permet de séléctionner le mur afin d'en poser sur la grille.


## Paramètres du Simulation

Paramètre du Blob : 
- Rareté de Ramification
- Périmètre de détection de la nourriture
- Niveau de Répulsivité entre les parties mortes du Blob et le Blob
- Niveau de Répulsivité entre les murs et le Blob
- Niveau de Répulsivité entre les parties vivantes du Blob
- Niveau d'Attraction du Blob à la nourriture
- Influence de l'oscillation des autres cellules du Blob sur son développement

## Edition de la grille

Possibilité d'ajouter des Blobs, des Walls et de la Nourriture grâce à la partie Edition dans la grille.


## Génération procédurale

Le labyrinthe et l'environnement sont générés procéduralements à l'aide d'algorithme à évènements discrets.