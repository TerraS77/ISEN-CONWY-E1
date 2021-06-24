#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "rock.h"
#include "../BlobEngine/blobEngine.h"

// Créer des rochers
void makeRock(int ***tab, int W, int H)
{
	srand(time(NULL));
	int Width = W;
	int Height = H;
	int randSharp = rand() % 10 + 1;

	*tab = (int **)malloc(sizeof(int *) * Height);
	if (*tab == NULL)
	{
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 1:0)");
		exit(EXIT_FAILURE);
	}

	for (int y = 0; y < Height; y++)
	{
		(*tab)[y] = (int *)malloc(sizeof(int) * Width);
		if ((*tab)[y] == NULL)
		{
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 2:%d)", y);
			for (int Y = 0; Y < y; Y++)
				free((*tab)[Y]);
			free(*tab);
			exit(EXIT_FAILURE);
		}
	}

	for (int x = 0; x < Width; x++)
		for (int y = 0; y < Height; y++)
			(*tab)[y][x] = 0;
	int size = rand() % ((Height * Width) / 3) + 10;
	int compteur = 2;

	int CentreY = Height / 2;
	int CentreX = Width / 2;

	(*tab)[CentreY][CentreX] = 1;

	switch (rand() % 4)
	{
	case 0:
		(*tab)[CentreY + 1][CentreX] = 1;
		break;

	case 1:
		(*tab)[CentreY][CentreX + 1] = 1;
		break;

	case 2:
		(*tab)[CentreY - 1][CentreX] = 1;
		break;

	case 3:
		(*tab)[CentreY][CentreX - 1] = 1;
		break;
	}

	while (compteur < size)
	{
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Height; y++)
			{

				if ((*tab)[y][x] == 0 && rand() % 20 == 0)
				{
					int AN = getAliveNeyboors(*tab, x, y, W, H);
					if (AN >= 2)
					{
						(*tab)[y][x] = 1;
						compteur++;
					}
				}

				if ((*tab)[y][x] == 0 && rand() % randSharp == 0)
				{

					int AN = getAliveNeyboors(*tab, x, y, W, H);

					if (AN >= 4)
					{

						(*tab)[y][x] = 1;
						compteur++;
					}
				}
			}
		}
	}
	int **Mask = NULL;
	if (rand() % 3 == 0)
	{
		;
	}
	else
	{
		bakeHole(&Mask, W, H);

		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Height; y++)
			{
				if ((*tab)[y][x] == 1 && (Mask)[y][x] == 1)
					(*tab)[y][x] = 0;
			}
		}
	}
}

// Créer des trous
void bakeHole(int ***tab, int W, int H)
{

	srand(time(NULL));
	float Vx;
	float Vy;
	int Width = W;
	int Height = H;

	int CentreY = Height / 2;
	int CentreX = Width / 2;

	*tab = (int **)malloc(sizeof(int *) * Height);
	if (*tab == NULL)
	{
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 1:0)");
		exit(EXIT_FAILURE);
	}

	for (int y = 0; y < Height; y++)
	{
		(*tab)[y] = (int *)malloc(sizeof(int) * Width);
		if ((*tab)[y] == NULL)
		{
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 2:%d)", y);
			for (int Y = 0; Y < y; Y++)
				free((*tab)[Y]);
			free(*tab);
			exit(EXIT_FAILURE);
		}
	}
	for (int x = 0; x < Width; x++)
		for (int y = 0; y < Height; y++)
			(*tab)[y][x] = 0;

	int randSharp = rand() % 20 + 1;
	int randx = rand() % 20 + 1;
	int randy = (20 - randx) + 1;

	int compteur = 2;
	int size = rand() % ((Height * Width) / 3) + 10;
	int X = rand() % (Width - 1) + 1;
	int Y = rand() % (Height - 1) + 1;

	while (sqrtf(powf((CentreY - Y), 2) + powf((CentreX - X), 2)) < 0.5 * (Width < Height ? Width : Height))
	{
		X = rand() % (Width - 1) + 1;
		Y = rand() % (Height - 1) + 1;
	}

	float PointX = X;
	float PointY = Y;

	Y = (int)floorf(PointY);
	X = (int)floorf(PointX);

	(*tab)[Y][X] = 1;

	Vy = CentreY - PointY;
	Vx = CentreX - PointX;

	float D = sqrtf(powf(Vy, 2) + powf(Vx, 2));

	vector vect;
	vect.x = Vx;
	vect.y = Vy;

	vect = crunchSpeed(vect,1);

	for (int i = 0; i < 2 * D; i++)
	{
		PointX += vect.x;
		PointY += vect.y;
		Y = (int)floorf(PointY);
		X = (int)floorf(PointX);

		if (Y < Height && Y >= 0 && X < Width && X >= 0)
			(*tab)[Y][X] = 1;
	}

	while (compteur < size)
	{
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Height; y++)
			{
				if ((*tab)[y][x] == 0 && rand() % 20 == 0)
				{
					int AN = getAliveNeyboors(*tab, x, y, W, H);
					if (AN >= 2)
					{

						if (y + 1 < Height)
							if ((*tab)[y + 1][x] == 1 && rand() % randy == 0)
								(*tab)[y][x] = 1;
						if (y - 1 > 0)
							if ((*tab)[y - 1][x] == 1 && rand() % randy == 0)
								(*tab)[y][x] = 1;
						if (x + 1 < Width)
							if ((*tab)[y][x + 1] == 1 && rand() % randx == 0)
								(*tab)[y][x] = 1;
						if (x - 1 > 0)
							if ((*tab)[y][x - 1] == 1 && rand() % randx == 0)
								(*tab)[y][x] = 1;

						compteur++;
					}
				}
				if ((*tab)[y][x] == 0 && rand() % randSharp == 0)
				{
					int AN = getAliveNeyboors(*tab, x, y, W, H);
					if (AN >= 4)
					{
						(*tab)[y][x] = 1;
						compteur++;
					}
				}
			}
		}
	}
}

// Créer un tableau stockant tout l'environnement généré
void RockPanel(int nC, int **CellData, int DataSizeX, int DataSizeY)
{

	for (int i = 0; i < nC; i++)
	{
		int WRock = (rand() % 51) + 50;
		int HRock = (rand() % 51) + 50;
		int Deltx = rand() % (DataSizeX - WRock);
		int Delty = rand() % (DataSizeY - HRock);
		int **Rock = NULL;
		if (rand() % 3 == 0)
		{
			bakeHole(&Rock, WRock, HRock);
			for (int y = Delty; y < (Delty + HRock); y++)
			{
				for (int x = Deltx; x < (Deltx + WRock); x++)
				{
					if (CellData[y][x] == 1 && Rock[y - Delty][x - Deltx] == 1)
						CellData[y][x] = 0;
				}
			}
		}

		else

		{
			makeRock(&Rock, WRock, HRock);
			for (int y = Delty; y < (Delty + HRock); y++)
			{
				for (int x = Deltx; x < (Deltx + WRock); x++)
				{
					CellData[y][x] = CellData[y][x] == 1 ? CellData[y][x] : Rock[y - Delty][x - Deltx];
				}
			}
		}
	}
}

// Détecte les voisins vivants
int getAliveNeyboors(int **tab, int x, int y, int xmax, int ymax){
	int AN = 0;
	for(int ty = -1; ty < 2 ; ty++){
		for(int tx = -1; tx < 2; tx++){
			if((x+tx) > 0 && (x+tx) < xmax && (y+ty) > 0 && (y+ty) < ymax) 
				if(tab[y+ty][x+tx] == 1) AN++;
		}
	}
	return (AN-tab[y][x]);
}