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
![Archi app](https://github.com/tom-bourjala/ISEN-ALG-BLOB/assets/31037693/e7490f81-9290-4660-800e-6bfce160aa13)

Our modular architecture allows for a set of organized files. Our makefile is itself framed by a bash script run.sh which transforms the source files in the source folder into objects that are then compiled into the Build executable. 

## Blob Engine
![Blob Routine](https://github.com/tom-bourjala/ISEN-ALG-BLOB/assets/31037693/15e23f46-cf17-4043-9b81-4f4a59235b5d)
This library contains the source file and the header file of the Blob prototype. In these files are the different characteristics of the bob and what it can do.

## Procedural 

This library contains the source files and the header files for the creation of an environment consisting of a maze and another environment consisting of rocks, both are of modifiable and random sizes.

## GFXLib

This is the ISEN library in which some modifications have taken place. Notably, the addition of support for scroll-up and scroll-down (mouse wheel) and the update of the mouse position at each frame.

## Smart UI

This library contains the extension of GFXLib that we have realized to ease the creation of buttons, sliders, and texts.

## Smart Grid

This library manages the entire interface between GFXLib and the simulation itself, the graphic rendering of the simulation grid, and the movement on it. This library allows the dynamic rendering of the simulation depending on the position of the mouse and the zoom on the grid with therefreshment of it. SmartGrid calls the different libraries that generate the various environments and acts as an interface between the Blob simulation, the graphics system, and the system of events and user input.

## Menu

This library contains the main menu and the secondary contextual menu for the simulation.

# Usage and Features

## Main Menu

**Access to 4 different simulations**
- Maze Simulation: A Blob is placed in a procedurally generated maze and it must find food in it.
- Environment Simulation: A Blob is placed in a procedurally generated environment where it will have to find food to survive.
- Empty Simulation: A Blob is placed in an empty space to see its evolution without any obstacles.
- Custom Simulation: A Blob is placed in an environment that can be modified according to our desires.

| Maze | Environment | Empty | Custom |
| --------------- | --------------- | --------------- | --------------- |
| ![maze](https://github.com/tom-bourjala/ISEN-ALG-BLOB/assets/31037693/2c935851-1ba0-4a04-8987-b1ae7e13f956) | ![env](https://github.com/tom-bourjala/ISEN-ALG-BLOB/assets/31037693/81a06445-4061-4936-add8-901c09fd782e) | ![void](https://github.com/tom-bourjala/ISEN-ALG-BLOB/assets/31037693/7ed6727e-c000-413e-a0a8-cbdaa8e2c8b5) | ![custom](https://github.com/tom-bourjala/ISEN-ALG-BLOB/assets/31037693/d2ff30a1-1cc3-4f40-88af-45c07324d83c) |




## Navigation and Control

- Right Click + mouse movement: movement in the grid
- Scroll-Up/Scroll-Down: Zoom/Unzoom of the grid
- Left Click on a grid square: place the element selected in the secondary menu
- F key: Allows selection of food to place on the grid
- B key: Allows blob selection to place on the grid
- W key: Allows wall selection to place on the grid.

## Simulation Settings

**Blob Setting**
- Rarity of branching
- Detection radius perimeter
- Level of repulsion between dead parts of the Blob and the Blob itself
- Level of repulsion between walls and the Blob
- Level of repulsion between living parts of the Blob
- Level of attraction of the Blob to food
- Influence of the oscillation of other Blob cells on its development
- Level of attraction of the Blob to emptiness

## Grid Editing

Ability to add Blobs, Walls, and Food through the Editing part in the grid.


## Procedural Generation

The maze and the environment are procedurally generated using discrete event algorithms.
