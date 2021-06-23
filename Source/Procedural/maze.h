/*
	.___  ___.      ___       ________   _______     _______ .__   __.   _______  __  .__   __.  _______ 
	|   \/   |     /   \     |       /  |   ____|   |   ____||  \ |  |  /  _____||  | |  \ |  | |   ____|
	|  \  /  |    /  ^  \    `---/  /   |  |__      |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__   
	|  |\/|  |   /  /_\  \      /  /    |   __|     |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|  
	|  |  |  |  /  _____  \    /  /----.|  |____    |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____ 
	|__|  |__| /__/     \__\  /________||_______|   |_______||__| \__|  \______| |__| |__| \__| |_______| 


	Version 1.1 (18/06/2021) : On peut à présent choisir la taille d'une case ( mur ou chemin )
	Version 1.0 (17/06/2021) : Création du générateur de Labyrinthe (W x H) qui sera stocké dans une matrice mazeData

*/

/* 
----- Voici la liste des variables et fonctions à utiliser pour Maze Engine --------

static int **mazeData = NULL; -> Et initialiser le tableau avec IniCellData();
int Wmaze = 21; -> Longueur du laby
int Hmaze = 31; -> Largeur du laby
int SizeMaze = 3; -> Echelle du laby (size case / bloc)

iniCellData(&mazeData, Wmaze, Hmaze); -> Initialiser le tableau
maze(mazeData, Wmaze, Hmaze); -> Créer le laby
printMazeData(mazeData, CellData, Wmaze, Hmaze, SizeMaze); -> Affiche le laby

*/

void mazeEngine(int **tab, int W, int H, int size);								 
void updateMetaData(int **metaData, int id1, int id2, int W, int H); 
void setMetaData(int **metaData, int **mazeData, int W, int H);
void printMazeData(int **mazeData, int **CellData, int W, int H, int size);