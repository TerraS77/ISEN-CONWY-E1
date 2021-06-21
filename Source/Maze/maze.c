#include <../Maze/maze.h>

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

void mazeEngine(int **tab, int W, int H)
{
	if (W % 2 == 0) W = W - 1;
	if (H % 2 == 0) H = H - 1;
	
	// Init metaData
	int **metaData;
	metaData = (int **)malloc(sizeof(int *) * H);
	for (int i = 0; i < H; i++)
	{
		metaData[i] = (int *)malloc(sizeof(int) * W);
	}
	setMetaData(metaData, tab, W, H);

	// Init setting
	int case_x = 0, case_y = 0;
	int delta_x = 0, delta_y = 0;
	int nb_zone = ((W - 1) * (H - 1)) / 4 - 1;
	int id1 = 0, id2 = 0;

	// Create Maze
	while (nb_zone != 0)
	{
		// for (int loop = 0; loop < 10000 ; loop++ ){
		case_x = rand() % (W - 1); // x de la case
		case_y = rand() % (H - 1); // y de la case

		if (case_x > 0 && case_y > 0 && case_x < W - 1 && case_y < H - 1 && metaData[case_y][case_x] == -1)
		{
			delta_x = rand() % 2;
			if (delta_x == 0)
				delta_y = 1;
			else
				delta_y = 0;
			id1 = metaData[case_y - delta_y][case_x - delta_x];
			id2 = metaData[case_y + delta_y][case_x + delta_x];
			if (id1 != id2 && id1 != -1 && id2 != -1)
			{
				tab[case_y][case_x] = 0;
				metaData[case_y][case_x] = id1;
				nb_zone = nb_zone - 1;
				updateMetaData(metaData, id1, id2, W, H);
			}
		}
	}
	free(metaData);
}

// Update MetaData
void updateMetaData(int **metaData, int id1, int id2, int W, int H)
{
	for (int k = 0; k < H; k++)
	{
		for (int j = 0; j < W; j++)
		{
			if (metaData[k][j] == id2)
			{
				metaData[k][j] = id1;
			}
		}
	}
}

// Set MetaData
void setMetaData(int **metaData, int **mazeData, int W, int H)
{
	// Set metaData & mazeData
	int countMaker = 0;
	for (int k = 0; k < H; k++)
	{
		for (int j = 0; j < W; j++)
		{
			if (k % 2 == 0)
			{
				mazeData[k][j] = 1;
				metaData[k][j] = -1;
			}
			else if (j % 2 == 0)
			{
				mazeData[k][j] = 1;
				metaData[k][j] = -1;
			}
			else
			{
				mazeData[k][j] = 0;
				metaData[k][j] = countMaker;
				countMaker = countMaker + 1;
			}
		}
	}
}

// print MazeData
void printMazeData(int **mazeData, int **CellData, int W, int H, int size)
{
	int WcellCap = (W - 1) / 2;
	int x = 0;
	int y = 0;
	int temp = 0;

	for (int k = 0; k < H; k++)
	{
		x = 0;
		for (int j = 0; j < W; j++)
		{
			for (int n = 0; n < size; n++)
			{
				for (int m = 0; m < size; m++)
				{
					CellData[k + n + y][j + m + x] = mazeData[k][j];
				}
			}
			x = x + (size - 1);
		}
		y = y + (size - 1);
	}
}