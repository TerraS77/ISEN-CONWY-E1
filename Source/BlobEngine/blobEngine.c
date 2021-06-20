#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "blobEngine.h"
#include "../SmartUI/SmartUI.h" 

#define OOBPenality 50
#define WallPenality 20
#define FoodBonus 50
#define EmptyBonus 5

void blobNewRound(cell **cellGrid, int CW, int CH, blob_blob *target_blob, int *BN, simulation sim){
	if(target_blob->isExpanding){
		for(int i = 0; i < NumberOfAnts; i++){
			if(AntsData[i].ttl > 0){
				if(AntsData[i].ttl<500) AntsData[i].ttl -= rand()%5;
				if(AntsData[i].ttl <= 0){;}
				else{
					AntsData[i].t++;
					AntsData[i].moov.x += (float)((10.00 - (rand()%20))/15.0);
					AntsData[i].moov.y += (float)((10.00 - (rand()%20))/15.0);
					vector mucus = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(AntsData[i].x),(int)floorf(AntsData[i].y)), cell_mucus, sim.detectionRadius);
					vector wall = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(AntsData[i].x),(int)floorf(AntsData[i].y)), cell_block, sim.detectionRadius);
					vector self = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(AntsData[i].x),(int)floorf(AntsData[i].y)), cell_blob, sim.detectionRadius);
					vector food = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(AntsData[i].x),(int)floorf(AntsData[i].y)), cell_food, sim.detectionRadius);			
					vector oscil = getOscilatorVect(cellGrid, CW, CH, new2Dcoord((int)floorf(AntsData[i].x),(int)floorf(AntsData[i].y)), AntsData[i].oscillation, AntsData[i].id);
					printf("V : %f, %f\nVmucus : %f, %f\n V : %f, %f\n Vwall : %f, %f\n Vself : %f, %f\n Vfood : %f, %f\n Voscil : %f, %f\n", AntsData[i].moov.x, AntsData[i].moov.y, mucus.x*sim.RepMucusMultiplicator, mucus.y*sim.RepMucusMultiplicator, wall.x*sim.RepWallMultiplicator, wall.y*sim.RepWallMultiplicator, self.x*sim.RepSelfMultiplicator, self.y*sim.RepSelfMultiplicator, food.x*sim.AtracFoodMultiplicator, food.y*sim.AtracFoodMultiplicator, oscil.x*sim.OscilInfluence, oscil.y*sim.OscilInfluence);
					AntsData[i].moov.x -= mucus.x*sim.RepMucusMultiplicator + wall.x*sim.RepWallMultiplicator + self.x*sim.RepSelfMultiplicator - food.x*sim.AtracFoodMultiplicator - oscil.x*sim.OscilInfluence;
					AntsData[i].moov.y -= mucus.y*sim.RepMucusMultiplicator + wall.y*sim.RepWallMultiplicator + self.y*sim.RepSelfMultiplicator - food.y*sim.AtracFoodMultiplicator - oscil.y*sim.OscilInfluence;
					AntsData[i].moov = crunchSpeed(AntsData[i].moov, 1);
					float xCache = AntsData[i].x;
					float yCache = AntsData[i].y;
					AntsData[i].x += AntsData[i].Vx;
					AntsData[i].y += AntsData[i].Vy;
					int fX = (int)floorf(AntsData[i].x);
					int fY = (int)floorf(AntsData[i].y);
					if(fY > CH || fY < 0 || fX > CW || fX < 0){
						if(fY > CH || fY < 0){
							AntsData[i].y = yCache;
							AntsData[i].moov.y = -AntsData[i].moov.y;
							AntsData[i].oscillation -= OOBPenality;
						}
						if(fX > CW || fX < 0){
							AntsData[i].x = xCache;
							AntsData[i].moov.x = -AntsData[i].moov.x;
							AntsData[i].oscillation -= OOBPenality;
						}
					}else if(CellData[fY][fX].type == cell_block){
						if(xCache - AntsData[i].x == -1 || xCache - AntsData[i].x == 1) AntsData[i].moov.x = -AntsData[i].moov.x;
						if(yCache - AntsData[i].y == -1 || yCache - AntsData[i].y == 1) AntsData[i].moov.y = -AntsData[i].moov.y;
						AntsData[i].oscillation -= WallPenality;
						AntsData[i].x = xCache;
						AntsData[i].y = yCache;
					}else if(CellData[fY][fX].type == cell_food){
						AntsData[i].oscillation += FoodBonus;
						target_blob->isExpanding = false;
					}else if(CellData[fY][fX].type == cell_empty) AntsData[i].oscillation += EmptyBonus;
					int fX = (int)floorf(AntsData[i].x);
					int fY = (int)floorf(AntsData[i].y);
					if(CellData[fY][fX].type == cell_blob && AntsData[i].t>50 && AntsData[i].ttl<500) AntsData[i].ttl = 0;
					else{
						if(rand()%30 == 1 && AntsData[i].t>AntsData[i].ttl/50){
							float newVx = AntsData[i].Vx + (float)((10.00 - (rand()%20))/10.0);
							float newVy = AntsData[i].Vy + (float)((10.00 - (rand()%20))/10.0);
							newAnt(&AntsData, &NumberOfAnts, new2Dcoord(AntsData[i].x,AntsData[i].y), newVx, newVy, AntsData[i].ttl/1.5, AntsData[i].oscillation);
						}
						if(CellData[fY][fX].type == cell_blob) CellData[fY][fX].blob_bm += AntsData[i].ttl;
						else CellData[fY][fX] = newBlobCell(CellData, CellData[fY][fX].food_amount, blob_vein, AntsData[i].id, -1, AntsData[i].ttl, CellData[fY][fX].mucus_amount, new2Dcoord(fX, fY), AntsData[i].oscillation);
					}
				}
			}
		}
	}else{
		int totalFood;
	}
}

// void blobFusion(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *mergedBlob){

// }

// void blobDivision(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *newBlob){

// }

vector getNeyboorsVect(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius){
	vector newVect;
	newVect.x = 0;
	newVect.y = 0;
	for(int ty = -radius; ty <= radius ; ty++){
		for(int tx = -radius; tx <= radius; tx++){
			if((target.x+tx) > 0 && (target.x+tx) < CW && (target.y+ty) > 0 && (target.y+ty) < CH && !(target.x == tx && target.y == ty)){
				if(cellGrid[target.y+ty][target.x+tx].type == type){
					newVect.x += cosf(atan2f(ty, tx));
					newVect.y += sinf(atan2f(ty, tx));
				}
			}
		}
	}
	return newVect;
}

int getNeyboors(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius){
	int SN;
	for(int ty = -radius; ty <= radius ; ty++) for(int tx = -radius; tx <= radius; tx++)
		if((target.x+tx) > 0 && (target.x+tx) < CW && (target.y+ty) > 0 && (target.y+ty) < CH && !(target.x == tx && target.y == ty))
			if(cellGrid[target.y+ty][target.x+tx].type == type)
				SN++;
	return SN;
}

vector crunchSpeed(vector vect, int speed){
	float a = speed/(sqrtf(powf(vect.x, 2.0) + powf(vect.y, 2.0)));
	vect.x *= a;
	vect.y *= a;
	return vect;
}

vector getOscilatorVect(cell **cellGrid, int CW, int CH, coord2D target, float targetOscillation, int id){
	vector newVect;
	newVect.x = 0;
	newVect.y = 0;
	for(int ty = 0; ty < CH; ty++){
		for(int tx = 0; tx < CW; tx++){
			if(!(target.x == tx && target.y == ty)){
				if(cellGrid[ty][tx].type == cell_blob && cellGrid[ty][tx].blob_id == id){
					newVect.x += (cosf(atan2f(ty-target.y, tx-target.x))*(cellGrid[ty][tx].blob_oscillation - targetOscillation)*sqrtf(powf(ty-target.y,2) + powf(tx-target.x,2));
					newVect.y += (sinf(atan2f(ty-target.y, tx-target.x))*(cellGrid[ty][tx].blob_oscillation - targetOscillation)*sqrtf(powf(ty-target.y,2) + powf(tx-target.x,2));
				}
			}
		}
	}
	newVect = crunchSpeed(newVect, 1);
	return newVect;
}

blob_blob newBlob(cell **cellGrid, int CW, int CH, coord2D SP, simulation sim){
	srand(time(NULL));
	blob_blob newBLOB;
    bool isExpanding;
    newBLOB.id = newBlobID();
	newBLOB.totalCells = 10;
	newBLOB.cells = (coord2D*) malloc(sizeof(coord2D)*newBLOB.totalCells);
	if(newBLOB.cells == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniBlobCells)");
		exit(EXIT_FAILURE);
	}
	newBLOB.cells[0] = newBlobCell(cellGrid, cellGrid[SP.y][SP.x].food_amount, blob_kernel, newBLOB.id, -1, 50, 200, SP);
	int n = 1;
	while(n < (newBLOB.totalCells - 1)){
		for(int x = 0; x<CW; x++){
			for(int y = 0; y<CH; y++){
				if((cellGrid[y][x].type == empty || cellGrid[y][x].type == food) && n < (newBLOB.totalCells - 1) && (rand()%19) == 0){
					int BN = 0;
					if(y < (CH + 1)) if(cellGrid[y+1][x].type == cell_blob && cellGrid[y+1][x].blob_id == newBLOB.id) BN++;
					if(y > 0) if(cellGrid[y-1][x].type == cell_blob && cellGrid[y-1][x].blob_id == newBLOB.id) BN++;
					if(x < (CW + 1)) if(cellGrid[y][x+1].type == cell_blob && cellGrid[y][x+1].blob_id == newBLOB.id) BN++;
					if(x > 0) if(cellGrid[y][x-1].type == cell_blob && cellGrid[y][x-1].blob_id == newBLOB.id) BN++;
					if(BN > 0){
						newBlobCell(cellGrid, cellGrid[y][x].food_amount, blob_kernel, newBLOB.id, -1, 50, new2Dcoord(x,y));
						n++;
					}
				}
			}
		}
	}
    newBLOB.ants = NULL;
    newBLOB.nAnts = 0;
	newBLOB.isExpanding = true;
	return newBLOB;
}

cell newBlobCell(cell **cellGrid, int food, blob_cellType blob_type, int id, int ttl, int bm, int mucus_amount, coord2D spawn, float oscillation){
	cell tnewBlobCell;
	tnewBlobCell.type = cell_blob;
    tnewBlobCell.food_amount = food;
    tnewBlobCell.blob_type = blob_type;
    tnewBlobCell.blob_id = id;
    tnewBlobCell.blob_ttl = ttl;
    tnewBlobCell.blob_bm = bm;
	tnewBlobCell.blob_oscillation = oscillation;
	tnewBlobCell.mucus_amount = mucus_amount;
	return tnewBlobCell;
}

cell newCell(cellType type, int food_amount, int blob_bm, int mucus_amount){
	cell tnewCell;
    tnewCell.type = type;
    tnewCell.food_amount = food_amount;
    tnewCell.blob_type = blob_none;
    tnewCell.blob_id = -1;
    tnewCell.blob_ttl = -1;
	tnewCell.blob_oscillation = -1;
	tnewCell.blob_oscillation = -1;
    tnewCell.blob_bm = blob_bm;
    tnewCell.mucus_amount = mucus_amount;
	return tnewCell;
}

cell newEmptyCell(){
	cell tnewCell;
    tnewCell.type = cell_empty;
    tnewCell.food_amount = 0;
    tnewCell.blob_type = none;
    tnewCell.blob_id = -1;
    tnewCell.blob_ttl = -1;
    tnewCell.blob_bm = -1;
	tnewCell.blob_oscillation = -1;
	tnewCell.mucus_amount = 0;
	return tnewCell;
}

int newBlobID(){
    static int id = 0;
    id++;
    return id;
}

void newAnt(ant **tab, int *tabSize, coord2D coords, float Vx, float Vy, int ttl, float oscillation){
	(*tabSize)++;
	*tab = (ant*) realloc(*tab, *tabSize * sizeof(ant));
	(*tab)[*tabSize - 1].dead = false;
    (*tab)[*tabSize - 1].Vx = Vx;
    (*tab)[*tabSize - 1].Vy = Vy;
    (*tab)[*tabSize - 1].x = coords.x;
    (*tab)[*tabSize - 1].y = coords.y;
	if(Vx == -2) vectorGeneratorRand(&(*tab)[*tabSize - 1].Vx, &(*tab)[*tabSize - 1].Vy, 1);
    (*tab)[*tabSize - 1].t = 0;
    (*tab)[*tabSize - 1].ttl = ttl;
    (*tab)[*tabSize - 1].oscillation = oscillation;
}

void vectorGeneratorRand(float *Vx, float *Vy, int speed){
	*Vx = (float)(rand()%11);
	*Vx = (*Vx)/10.0;
	*Vy = sqrtf(powf(speed, 2) - powf(*Vx, 2));
	if(rand()%2 == 0) *Vx = -(*Vx);
	if(rand()%2 == 0) *Vy = -(*Vy);
}

void iniCellData(cell ***tab, int W, int H){
	*tab = (cell**) malloc(sizeof(cell*)*H);
	if(*tab == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<H; y++){
		(*tab)[y] = (cell*) malloc(sizeof(cell)*W);
		if((*tab)[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 2:%d)", y);
			for(int Y = 0; Y<y; Y++) free((*tab)[Y]);
			free(*tab);
			exit(EXIT_FAILURE);
		}
	}
	for(int x = 0; x<W; x++) for(int y = 0; y<H; y++) (*tab)[y][x] = newEmptyCell();
}

void freeCellData(cell ***tab, int W, int H){
	for(int y = 0; y<H; y++) free((*tab)[y]);
	free(*tab);
}