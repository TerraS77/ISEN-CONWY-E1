#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "maze.h"

// Créer un labyrinthe enregistré dans la matrice [tab] de taille [W*H]
void mazeEngine(int **tab, int W, int H, int size)
{
	if (W * size > W) W = (W / size);
	if (H * size > H) H = (H / size);
	if (W % 2 == 0) W = W - 1;
	if (H % 2 == 0) H = H - 1;
	int **mazeData = NULL;
	iniCellData(&mazeData, W, H);
	
	// Init metaData
	int **metaData;
	metaData = (int **)malloc(sizeof(int *) * H);
	for (int i = 0; i < H; i++)
	{
		metaData[i] = (int *)malloc(sizeof(int) * W);
	}
	setMetaData(metaData, mazeData, W, H);

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
				mazeData[case_y][case_x] = 0;
				metaData[case_y][case_x] = id1;
				nb_zone = nb_zone - 1;
				updateMetaData(metaData, id1, id2, W, H);
			}
		}
	}
	free(metaData);
	printMazeData(mazeData, tab, W, H, size);
}

// Met à jour les ID dans [metaData] ( fusion de zones )
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

// Initialise la matrice [metaData] pour créer les zones
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

// Enregistre le labyrithe stocké dans [mazeData] à l'échelle [size] dans la grille d'affichage [CellData]
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