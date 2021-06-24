/*
	.___  ___.      ___       ________   _______     _______ .__   __.   _______  __  .__   __.  _______ 
	|   \/   |     /   \     |       /  |   ____|   |   ____||  \ |  |  /  _____||  | |  \ |  | |   ____|
	|  \  /  |    /  ^  \    `---/  /   |  |__      |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__   
	|  |\/|  |   /  /_\  \      /  /    |   __|     |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|  
	|  |  |  |  /  _____  \    /  /----.|  |____    |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____ 
	|__|  |__| /__/     \__\  /________||_______|   |_______||__| \__|  \______| |__| |__| \__| |_______| 

	Version 1.2 (24/06/2021) : Création de la fonction mazeEngine qui englobe toutes les fonctions de création et d'affichage du Labyrinthe
	Version 1.1 (18/06/2021) : On peut à présent choisir la taille d'une case ( mur ou chemin )
	Version 1.0 (17/06/2021) : Création du générateur de Labyrinthe (W x H) qui sera stocké dans une matrice mazeData

*/

// Créer un labyrinthe enregistré dans la matrice [tab] de taille [W*H]
void mazeEngine(int **tab, int W, int H, int size);

// Met à jour les ID dans [metaData] ( fusion de zones )
void updateMetaData(int **metaData, int id1, int id2, int W, int H); 

// Initialise la matrice [metaData] pour créer les zones
void setMetaData(int **metaData, int **mazeData, int W, int H);

// Enregistre le labyrithe stocké dans [mazeData] à l'échelle [size] dans la grille d'affichage [CellData]
void printMazeData(int **mazeData, int **CellData, int W, int H, int size);