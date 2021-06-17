#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "blobEngine.h"
#include "../SmartUI/SmartUI.h" 



void blobNewRound(cell **cellGrid, int CW, int CW, blob *blob, int *BN){

}

void blobFusion(cell **cellGrid, int CW, int CW, blob *blob, blob *mergedBlob){

}

void blobDivision(cell **cellGrid, int CW, int CW, blob *blob, blob *newBlob){

}

int getNeyboorsByType(cell **cellGrid, int CW, int CW, coord2D target, cellType type){
	int A = 0;
	for(int ty = -1; ty < 2 ; ty++) for(int tx = -1; tx < 2; tx++)
			if((target.x+tx) > 0 && (target.x+tx) < xmax && (target.y+ty) > 0 && (target.y+ty) < ymax && !(target.x == tx && target.y == ty)) 
				if(cellGrid[target.y+ty][target.x+tx].type == type) A++;
	return A;
}

blob newBlob(cell **cellGrid, int CW, int CW, blob *blob, coord2D SP, int ttf, int ttnutr, int ttbio){
	srand( time( NULL ) );
	blob newBlob;
    newBlob.id = newBlobID();
	newBlob.totalCells = 10;
	newBlob.cells = (blob_cell*) malloc(sizeof(blob_cell)*newBlob.totalCells);
	if(CellDataCache == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniBlobCells)");
		exit(EXIT_FAILURE);
	}
	newBlob.cells[0] = newBlobCell(cellGrid, cellGrid[SP.y][SP.x].type == food ? fb : blob, cellGrid[SP.y][SP.x].food_amount, kernel, newBlob.id, -1, 50, 200, SP);
	int cX = SP.x;
	int cY = SP.y;
	for(i = 1; i < 10; i++){
		while(cellGrid[cY][cX].type != empty && cellGrid[cY+1][cX+1].type == empty)
	}
    int harvest_totalFood;
    int harvest_foodPR;

    int stock_totalNutr;
    int stock_nutrPR;

    int biomass_totalBiomass;
    int biomass_biomassPR;

    blob_agent *agents;
    int nAgents;
}

blob_cell newBlobCell(cell **cellGrid, cellType type, int food, blob_cellType blob_type, int id, int ttl, int bm, int nutr, coord2D spawn){
	blob_cell newBlobCell;
	newBlobCell.type = type;
    newBlobCell.food_amount = food;
    newBlobCell.blob_type = blob_type;
    newBlobCell.blob_id = id;
    newBlobCell.blob_ttl = ttl;
    newBlobCell.blob_bm = bm;
    newBlobCell.blob_nutr = nutr;
    newBlobCell.blob_request_bm = 0;
    newBlobCell.blob_request_nutr = 0;
    newBlobCell.coord2D = spawn;
	cellGrid[spawn.y][spawn.x] = newCell(type, food, blob_type, id, ttl, bm, nutr);
}

cell newCell(cellType type, int food_amount, blob_cellType blob_type, int blob_id, int blob_ttl, int blob_bm, int blob_nutr){
	cell newCell;
    newCell.type = type;
    newCell.food_amount = food_amount;
    newCell.blob_type = blob_type;
    newCell.blob_id = blob_id;
    newCell.blob_ttl = blob_ttl;
    newCell.blob_bm = blob_bm;
    newCell.blob_nutr = blob_nutr;
}

cell newEmptyCell(){
	cell newCell;
    newCell.type = empty;
    newCell.food_amount = 0;
    newCell.blob_type = none;
    newCell.blob_id = -1;
    newCell.blob_ttl = -1;
    newCell.blob_bm = -1;
    newCell.blob_nutr = -1;
    newCell.color = newColor(0,0,0);
	return newCell;
}

int newBlobID(){
    static int id = 0;
    id++;
    return id;
}

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