#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "blobEngine.h"
#include "../SmartUI/SmartUI.h" 



void blobNewRound(cell **cellGrid, int CW, int CH, blob_blob *target_blob, int *BN, simulation sim){
	blobUpdateStats(target_blob, sim);
	cell **CellGridCache;
	CellGridCache = (cell**) malloc(sizeof(cell*)*CH);
	if(CellGridCache == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCache 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<CH; y++){
		CellGridCache[y] = (cell*) malloc(sizeof(cell)*CW);
		if(CellGridCache[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCache 2:%d)", y);
			for(int Y = 0; Y<y; Y++) free(CellGridCache[Y]);
			free(CellGridCache);
			exit(EXIT_FAILURE);
		}
	}
	//0. Start Expand
	int FF = 0;
	for(i = 0; i < target_blob->totalCells, i++) if(target_blob->cells[i].blob_type != none) FF += getNeyboorsByType(cellGrid, CW, CH, target_blob->cells[i].coord2D, food);
	if(FF > 0){
		target_blob->isExpanding = false;
		for(int x = 0; x<CW; x++){
			for(int y = 0; y<CH; y++){
				if(cellGrid[y][x].type == food){
					int AN = getNeyboorsByType(cellGrid, CW, CH, new2Dcoord(x,y), blob) + getNeyboorsByType(cellGrid, CW, CH, new2Dcoord(x,y), fb);
					if(AN>=1){
						target_blob->totalCells++;
						target_blob->cells = (blob_cell *) realloc(target_blob->cells, target_blob->totalCells * sizeof(blob_cell));
						target_blob->cells[totalCells-1] = newBlobCell(CellGridCache, fb, cellGrid[y][x].food_amount, food, target_blob->id, 10, 10, 0, new2Dcoord(x,y));
						target_blob->cells[totalCells-1].blob_request_bm = -10;
					}
				}
			}
		}
		for(int x = 0; x<CW; x++)for(int y = 0; y<CH; y++) cellGrid[y][x] = CellGridCache[y][x];
	}else if(target_blob->stock_nutrPR > target_blob->harvest_foodPR && 
		target_blob->stock_totalNutr < target_blob->nutrMinStock * target_blob->biomass_totalBiomass)
			target_blob->isExpanding = true;
	
	//1. Phase d'Expand
	if(target_blob->isExpanding){
		for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) CellGridCache[y][x] = cellGrid[y][x];
		for(int x = 0; x<CW; x++){
			for(int y = 0; y<CH; y++){
				if(cellGrid[y][x].type == empty || cellGrid[y][x].type == food){
					int AN = getNeyboorsByType(cellGrid, CW, CH, new2Dcoord(x,y), blob) + getNeyboorsByType(cellGrid, CW, CH, new2Dcoord(x,y), fb);
					if(AN>=2){
						target_blob->totalCells++;
						target_blob->cells = (blob_cell *) realloc(target_blob->cells, target_blob->totalCells * sizeof(blob_cell));
						target_blob->cells[totalCells-1] = newBlobCell(CellGridCache, cellGrid[y][x].type == food ? fb : blob, cellGrid[y][x].food_amount, cellGrid[y][x].type == food ? fb : plasma, target_blob->id, 10, 10, 0, new2Dcoord(x,y));
						target_blob->cells[totalCells-1].blob_request_bm = -10;
						if(cellGrid[y][x].type == food) target_blob->isExpanding = false;
					}
				}
			}
		}
		for(int x = 0; x<CW; x++){
			for(int y = 0; y<CH; y++){
				if((CellGridCache[y][x].type != cellGrid[y][x].type && (cellGrid[y][x].type == empty || cellGrid[y][x].type == food)){
					cellGrid[y][x] = CellGridCache[y][x];
				}
			}
		}
	}

	//2. CONSO ET REQUEST
	for(i = 0; i < target_blob->totalCells, i++){
		if(target_blob->cells[i].blob_type != none){
			//A - CONSO
			target_blob->cells[i].blob_request_nutr -= target_blob->cells[i].blob_bm * sim.nutrCons;
			//A - HARVEST
			if(target_blob->cells[i].blob_type == food){
				if(target_blob->stock_nutrPR > (target_blob->harvest_foodPR/sim.CroitFood){
					target_blob->cells[i].blob_bm += 10 * sim.food_SpeedExp;
				}
				if(target_blob->cells[i].food > (target_blob->cells[i].blob_bm * sim.FoodHarvest)){
					target_blob->cells[i].food -= target_blob->cells[i].blob_bm * sim.FoodHarvest;
					target_blob->cells[i].blob_nutr += (target_blob->cells[i].blob_bm * sim.FoodHarvest)/2;
					target_blob->cells[i].blob_request_nutr += (target_blob->cells[i].blob_bm * sim.FoodHarvest)/2;
					if(sim.StockCap * target_blob->cells[i].blob_bm > target_blob->cells[i].blob_nutr){
						target_blob->cells[i].blob_request_nutr += target_blob->cells[i].blob_nutr - (sim.StockCap * target_blob->cells[i].blob_bm)
						target_blob->cells[i].blob_nutr = sim.StockCap * target_blob->cells[i].blob_bm;
					}
					target_blob->cells[i].blob_bm * sim.FoodHarvest;
				}else //CONVERT FOOD TO KERNEL
			}
			//A - EGALIZATION
			if(abs(target_blob->cells[i].blob_request_bm) <= target_blob->cells[i].blob_nutr){
				target_blob->cells[i].blob_nutr += target_blob->cells[i].blob_request_bm;
				target_blob->cells[i].blob_request_bm = 0;
			}else{
				target_blob->cells[i].blob_request_bm += target_blob->cells[i].blob_nutr;
				target_blob->cells[i].blob_nutr = 0;
			}
			if(target_blob->cells[i].blob_request_nutr < 0 && target_blob->cells[i].blob_nutr > 0){
				if(abs(target_blob->cells[i].blob_request_nutr) <= target_blob->cells[i].blob_nutr){
					target_blob->cells[i].blob_nutr += target_blob->cells[i].blob_request_nutr;
					target_blob->cells[i].blob_request_nutr = 0;
				}
				else{
					target_blob->cells[i].blob_request_nutr += target_blob->cells[i].blob_nutr;
					target_blob->cells[i].blob_nutr = 0;
				}
			}
			//A - UPDATEGRID
			cellGrid[target_blob->cells[i].coord2D.y][target_blob->cells[i].coord2D.x].food_amount = target_blob->cells[i].food;
			cellGrid[target_blob->cells[i].coord2D.y][target_blob->cells[i].coord2D.x].blob_bm = target_blob->cells[i].blob_bl;
			cellGrid[target_blob->cells[i].coord2D.y][target_blob->cells[i].coord2D.x].blob_nutr = target_blob->cells[i].blob_nutr;
			cellGrid[target_blob->cells[i].coord2D.y][target_blob->cells[i].coord2D.x].blob_request_bm = target_blob->cells[i].blob_request_bm;
			cellGrid[target_blob->cells[i].coord2D.y][target_blob->cells[i].coord2D.x].blob_request_nutr = target_blob->cells[i].blob_request_nutr;
		}
	}
}

void blobUpdateStats(blob_blob *target_blob, simulation sim){
	target_blob->harvest_totalFood = 0;
	target_blob->stock_totalNutr = 0;
	target_blob->biomass_totalBiomass = 0;
	target_blob->biomass_biomassPR = 0;
	for(i = 0; i < target_blob->totalCells, i++){
		if(target_blob->cells[i].blob_type != none){
			if(target_blob->cells[i].food_amount > 0){
				target_blob->harvest_totalFood += target_blob->cells[i].food_amount;
				target_blob->harvest_foodPR += sim.FoodHarvest * (target_blob->cells[i].food_amount > target_blob->cells[i].blob_bm ? target_blob->cells[i].blob_bm : target_blob->cells[i].food_amount);
			}
			target_blob->stock_totalNutr += target_blob->cells[i].blob_nutr;
			target_blob->biomass_totalBiomass += target_blob->cells[i].blob_bm;
			target_blob->biomass_biomassPR += target_blob->cells[i].blob_request_bm;
		}
		target_blob->stock_nutrPR = target_blob->biomass_biomassPR * sim.nutrCons;
	}
}

void blobFusion(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *mergedBlob){

}

void blobDivision(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *newBlob){

}

int getNeyboorsByType(cell **cellGrid, int CW, int CH, coord2D target, cellType type){
	int A = 0;
	for(int ty = -1; ty < 2 ; ty++) for(int tx = -1; tx < 2; tx++)
			if((target.x+tx) > 0 && (target.x+tx) < CW && (target.y+ty) > 0 && (target.y+ty) < CH && !(target.x == tx && target.y == ty)) 
				if(cellGrid[target.y+ty][target.x+tx].type == type) A++;
	return A;
}

blob_blob newBlob(cell **cellGrid, int CW, int CH, coord2D SP, int ttf, int ttnutr, int ttbio, simulation sim){
	srand(time(NULL));
	blob_blob newBLOB;
    newBLOB.id = newBlobID();
	newBLOB.totalCells = 10;
	newBLOB.cells = (blob_cell*) malloc(sizeof(blob_cell)*newBLOB.totalCells);
	if(CellDataCache == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniBlobCells)");
		exit(EXIT_FAILURE);
	}
	newBLOB.cells[0] = newBlobCell(cellGrid, cellGrid[SP.y][SP.x].type == food ? fb : blob, cellGrid[SP.y][SP.x].food_amount, kernel, newBLOB.id, -1, 50, 200, SP);
	int cellMakeCount = ;
	int n = 1;
	while(n < (newBLOB.totalCells - 1)){
		for(int x = 0; x<CW; x++){
			for(int y = 0; y<CH; y++){
				if((cellGrid[y][x].type == empty || cellGrid[y][x].type == food) && n < (newBLOB.totalCells - 1) && (rand()%19) == 0){
					int BN = 0;
					if(y < (CH + 1)) if((cellGrid[y+1][x].type == blob_cell || cellGrid[y+1][x].type == fb) && cellGrid[y+1][x].blob_id == newBLOB.id) BN++;
					if(y > 0) if((cellGrid[y-1][x].type == blob_cell || cellGrid[y-1][x].type == fb) && cellGrid[y-1][x].blob_id == newBLOB.id) BN++;
					if(x < (CW + 1)) if((cellGrid[y][x+1].type == blob_cell || cellGrid[y][x+1].type == fb) && cellGrid[y][x+1].blob_id == newBLOB.id) BN++;
					if(x > 0) if((cellGrid[y][x-1].type == blob_cell || cellGrid[y][x-1].type == fb) && cellGrid[y][x-1].blob_id == newBLOB.id) BN++;
					if(BN > 0){
						newBLOB.cells[n] = newBlobCell(cellGrid, cellGrid[y][x].type == food ? fb : blob, cellGrid[y][x].food_amount, kernel, newBLOB.id, -1, 50, 200, new2Dcoord(x,y));
						n++;
					}
				}
			}
		}
	}
 	blobUpdateStats(&newBLOB, sim);
    newBLOB.agents = NULL;
    newBLOB.nAgents = 0;
	newBLOB.isExpanding = true;
	return newBLOB;
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