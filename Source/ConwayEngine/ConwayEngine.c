#include <stdlib.h>
#include <stdio.h>
#include "ConwayEngine.h" 

void conwayTransform(int **CellData, int MW, int MH){
	
	//Allocation de la mémoire cache
	int **CellDataCache;
	CellDataCache = (int**) malloc(sizeof(int*)*MH);
	if(CellDataCache == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCache 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<MH; y++){
		CellDataCache[y] = (int*) malloc(sizeof(int)*MW);
		if(CellDataCache[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCache 2:%d)", y);
			for(int Y = 0; Y<y; Y++) free(CellDataCache[Y]);
			free(CellDataCache);
			exit(EXIT_FAILURE);
		}
	}

	//Conway Process
	for(int x = 0; x<MW; x++){
		for(int y = 0; y<MH; y++){
			//Récupération de voisins
			int AN = getAliveNeyboors(CellData, x, y, MW, MH);
			//Calcul de l'état à t+1 pour chaque cellules et stockage dans le cache 
			if(CellData[y][x] == 1){
				if(AN >= 2 && AN <= 3){
					CellDataCache[y][x] = 1;
				}else CellDataCache[y][x] = 0;
			}else{
				if(AN == 3) CellDataCache[y][x] = 1;
				else CellDataCache[y][x] = 0;
			}
		}
	}

	//Merging du cache
	for(int x = 0; x<MW; x++) for(int y = 0; y<MH; y++) CellData[y][x] = CellDataCache[y][x];

	//Libération de la mémoire cache
	for(int y = 0; y<MH; y++) free(CellDataCache[y]);
	free(CellDataCache);
}

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

int Vivant(int **CellData,int MW, int MH)
{
	int vivant=0;
	for(int x = 0; x<MH; x++) {
		for(int y = 0; y<MW; y++)
		{
			if(CellData[x][y]==1){vivant++;
			}
		}
	}
	return vivant;
}