#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "blobEngine.h"

#define OOBPenality 50
#define WallPenality 20
#define FoodBonus 50
#define EmptyBonus 0

void blobNewRound(cell **cellGrid, int CW, int CH, blob_blob *target_blob, int *BN, simulation sim){
	cell **cacheData = NULL;
	iniCellData(&cacheData, CW,CH);
	for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) cacheData[y][x] = cellGrid[y][x];
	for(int x = 0; x<CW; x++){
		for(int y = 0; y<CH; y++){
			if(cellGrid[y][x].type == cell_food && getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_blob, 1) > 0 && rand()%2 == 0){
				cacheData[y][x].type = cell_blob;
				cacheData[y][x].blob_bm = 150 + rand()%100;
				cacheData[y][x].blob_id = target_blob->id;
				target_blob->isExpanding = false;
			}
			if(cellGrid[y][x].type == cell_empty && getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_blob, 1) > 0 && rand()%5 == 0){
				int CN = 0;
				for(int ty = -1; ty <= 1 ; ty++) for(int tx = -1; tx <= 1; tx++)
					if((x+tx) > 0 && (x+tx) < CW && (y+ty) > 0 && (y+ty) < CH && !(x == tx && y == ty))
						if(cellGrid[y+ty][x+tx].type == cell_blob && cellGrid[y+ty][x+tx].food_amount > 0)
							CN++;
				if(CN>0){
					cacheData[y][x].type = cell_blob;
					cacheData[y][x].blob_bm = 50 + rand()%100;
					cacheData[y][x].blob_id = target_blob->id;
				}
			}
		}
	}
	for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) cellGrid[y][x] = cacheData[y][x];
	freeCellData(&cacheData,CW,CH);
	if(target_blob->isExpanding){
		int actAnt = 0;
		for(int i = 0; i < target_blob->nAnts; i++){
			if(target_blob->ants[i].ttl > 0){
				actAnt++;
				target_blob->ants[i].ttl -= rand()%5;
				if(target_blob->ants[i].ttl <= 0){;}
				else{
					target_blob->ants[i].t++;
					target_blob->ants[i].moov.x += (float)((10.00 - (rand()%20))/10.0);
					target_blob->ants[i].moov.y += (float)((10.00 - (rand()%20))/10.0);
					vector mucus = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(target_blob->ants[i].x),(int)floorf(target_blob->ants[i].y)), cell_mucus, sim.detectionRadius);
					vector wall = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(target_blob->ants[i].x),(int)floorf(target_blob->ants[i].y)), cell_block, sim.detectionRadius);
					vector self = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(target_blob->ants[i].x),(int)floorf(target_blob->ants[i].y)), cell_blob, sim.detectionRadius);
					vector food = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(target_blob->ants[i].x),(int)floorf(target_blob->ants[i].y)), cell_food, sim.detectionRadius);			
					vector empty = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord((int)floorf(target_blob->ants[i].x),(int)floorf(target_blob->ants[i].y)), cell_empty, sim.detectionRadius);	
					vector oscil = getOscilatorVect(cellGrid, CW, CH, new2Dcoord((int)floorf(target_blob->ants[i].x),(int)floorf(target_blob->ants[i].y)), target_blob->ants[i].oscillation, target_blob->ants[i].id);
					vector otherAnts;
					otherAnts.x = 0;
					otherAnts.y = 0;
					for(int j = 0; j < target_blob->nAnts; j++){
						if(sqrtf(powf(target_blob->ants[i].x-target_blob->ants[j].x,2)+powf(target_blob->ants[i].y-target_blob->ants[j].y,2)) <= sim.detectionRadius){
							otherAnts.x += cosf(atan2f(target_blob->ants[i].y-target_blob->ants[j].y, target_blob->ants[i].x-target_blob->ants[j].x));
							otherAnts.y += sinf(atan2f(target_blob->ants[i].y-target_blob->ants[j].y, target_blob->ants[i].x-target_blob->ants[j].x));
						}
					}
					otherAnts = crunchSpeed(otherAnts, 1);
					// printf("mucus X = %f mucus Y = %f\n",mucus.x,mucus.y);
					// printf("wall X = %f wall Y = %f\n",wall.x,wall.y);
					// printf("self X = %f self Y = %f\n",self.x,self.y);
					// printf("food X = %f food Y = %f\n",food.x,food.y);
					// printf("empty X = %f empty Y = %f\n",empty.x,empty.y);
					// printf("oscil X = %f oscil Y = %f\n",oscil.x,oscil.y);
					// printf("otherAnts X = %f otherAnts Y = %f\n",mucus.x,mucus.y);
					target_blob->ants[i].moov.x -= mucus.x*sim.RepMucusMultiplicator + wall.x*sim.RepWallMultiplicator + self.x*sim.RepSelfMultiplicator + otherAnts.x*sim.RepSelfMultiplicator - food.x*sim.AtracFoodMultiplicator - oscil.x*sim.OscilInfluence - empty.x*sim.AtracEmptyMultiplicator;
					target_blob->ants[i].moov.y -= mucus.y*sim.RepMucusMultiplicator + wall.y*sim.RepWallMultiplicator + self.y*sim.RepSelfMultiplicator + otherAnts.y*sim.RepSelfMultiplicator - food.y*sim.AtracFoodMultiplicator - oscil.y*sim.OscilInfluence - empty.y*sim.AtracEmptyMultiplicator;
					target_blob->ants[i].moov = crunchSpeed(target_blob->ants[i].moov, 1);
					float xCache = target_blob->ants[i].x;
					float yCache = target_blob->ants[i].y;
					target_blob->ants[i].x += target_blob->ants[i].moov.x;
					target_blob->ants[i].y += target_blob->ants[i].moov.y;
					int fX = (int)floorf(target_blob->ants[i].x);
					int fY = (int)floorf(target_blob->ants[i].y);
					if(fY > (CH-1) || fY < 0 || fX > (CW-1) || fX < 0){
						if(fY > (CH-1) || fY < 0){
							target_blob->ants[i].y = yCache;
							target_blob->ants[i].moov.y = 0;
							target_blob->ants[i].oscillation -= OOBPenality;
						}
						if(fX > (CW-1) || fX < 0){
							target_blob->ants[i].x = xCache;
							target_blob->ants[i].moov.x = 0;
							target_blob->ants[i].oscillation -= OOBPenality;
						}
					}else if(cellGrid[fY][fX].type == cell_block){
						if((int)floorf(xCache) - (int)floorf(target_blob->ants[i].x) == -1 || (int)floorf(xCache) - (int)floorf(target_blob->ants[i].x == 1)) target_blob->ants[i].moov.x = 0;
						if((int)floorf(yCache) - (int)floorf(target_blob->ants[i].y) == -1 || (int)floorf(yCache) - (int)floorf(target_blob->ants[i].y == 1)) target_blob->ants[i].moov.y = 0;
						target_blob->ants[i].oscillation -= WallPenality;
						target_blob->ants[i].x = xCache;
						target_blob->ants[i].y = yCache;
					}else if(getNeyboors(cellGrid, CW, CH, new2Dcoord(fX,fY), cell_food, 1) > 0){
						target_blob->ants[i].oscillation += FoodBonus;
						target_blob->isExpanding = false;
						target_blob->Food_End = new2Dcoord(fX,fY);
					}else if(cellGrid[fY][fX].type == cell_empty) target_blob->ants[i].oscillation += EmptyBonus;
					fX = (int)floorf(target_blob->ants[i].x);
					fY = (int)floorf(target_blob->ants[i].y);
					if(cellGrid[fY][fX].type == cell_blob && target_blob->ants[i].t>50 && target_blob->ants[i].ttl<500) target_blob->ants[i].ttl = 0;
					else{
						if(rand()%sim.ramificationRarity == 0){ // && 
							int iCell = 0;
							for(int ty = -sim.detectionRadius; ty <= sim.detectionRadius ; ty++){
								for(int tx = -sim.detectionRadius; tx <= sim.detectionRadius; tx++){
									if((fX+tx) >= 0 && (fX+tx) < CW && (fY+ty) >= 0 && (fY+ty) < CH && !(tx == 0 && ty == 0))
										if(cellGrid[fY+ty][fX+tx].type == cell_empty)
											iCell += getNeyboors(cellGrid, CW, CH, new2Dcoord(fX+tx, fY+ty), cell_blob, sim.detectionRadius) > 0 ? 0 : 1;
								}
							}
							if(iCell > 0){
								float newVx = target_blob->ants[i].moov.x + (float)((10.00 - (rand()%20))/10.0);
								float newVy = target_blob->ants[i].moov.y + (float)((10.00 - (rand()%20))/10.0);
								newAnt(&target_blob->ants, &target_blob->nAnts, new2Dcoord(target_blob->ants[i].x,target_blob->ants[i].y), newVx, newVy, target_blob->ants[i].ttl/1.5, target_blob->ants[i].oscillation, target_blob->id, sim.ramificationRarity);	
							}
						}
						if(cellGrid[fY][fX].type == cell_blob) cellGrid[fY][fX].blob_bm += target_blob->ants[i].ttl;
						else cellGrid[fY][fX] = newBlobCell(cellGrid, cellGrid[fY][fX].food_amount, blob_vein, target_blob->ants[i].id, -1, target_blob->ants[i].ttl, cellGrid[fY][fX].mucus_amount, new2Dcoord(fX, fY), target_blob->ants[i].oscillation);
					}
				}
			}
		}
		if(actAnt == 0){
			for(int i = 0; i<1; i++){
				target_blob->nAnts = 0;
				coord2D newStart;
				vector newVect;
				int score = getBestStartingPoint(cellGrid, CW, CH, target_blob->id, &newVect, &newStart, sim);
				//printf("x:%d y:%d score:%d\n", newStart.x, newStart.y, score);
				newAnt(&target_blob->ants, &target_blob->nAnts, new2Dcoord(newStart.x,newStart.y), newVect.x, newVect.y, score/2 + 200 > 400 ? 400 : score/2 + 200, cellGrid[newStart.y][newStart.x].blob_oscillation, target_blob->id, sim.ramificationRarity);
			}
		}
	}else{
		if(!target_blob->pathIsSet){
				if(target_blob->path == NULL){
					target_blob->path = (int**) malloc(sizeof(int*)*CH);
					for(int y = 0; y<CH; y++) target_blob->path[y] = (int*) malloc(sizeof(int)*CW);
					for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++){
						if(cellGrid[y][x].blob_id == target_blob->id){
							target_blob->path[y][x] = 1;
							target_blob->pathSize++;
						}else target_blob->path[y][x] = 0; 
					}
					target_blob->pathSize = (int) floorf(powf(target_blob->pathSize,1.5));
				}
				// exit(EXIT_SUCCESS);
				coord2D minBM = target_blob->Kernel_Start;
				for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) 
					if(target_blob->path[y][x] && cellGrid[y][x].blob_bm < cellGrid[minBM.y][minBM.x].blob_bm)
						minBM = new2Dcoord(x,y);
				target_blob->path[minBM.y][minBM.x] = 0;
				if(IsStartAndEndLinked(target_blob->path, CW, CH, target_blob->Kernel_Start, target_blob->Food_End) && cellGrid[minBM.y][minBM.x].blob_type != blob_kernel && cellGrid[minBM.y][minBM.x].food_amount == 0){
					cellGrid[minBM.y][minBM.x] = newCell(cell_mucus, 0, 0, cellGrid[minBM.y][minBM.x].blob_bm);
					target_blob->path[minBM.y][minBM.x] = 0; 
				}else{
					target_blob->path[minBM.y][minBM.x] = 1;
					cellGrid[minBM.y][minBM.x].blob_bm *= 1.5;
				}
			target_blob->pathSize--;
			if(target_blob->pathSize <= 0){
				target_blob->pathSize = 0;
				if(IsAllLinker(target_blob->path, CW, CH, target_blob->Kernel_Start, target_blob->Food_End)) target_blob->pathIsSet = true;
			}
		}
	}
}

// void blobFusion(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *mergedBlob){

// }

// void blobDivision(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *newBlob){

// }

bool IsStartAndEndLinked(int **tab,int CW,int CH,coord2D start, coord2D end){
	int **Pathinding;
	Pathinding = (int**) malloc(sizeof(int*)*CH);
	for(int y = 0; y<CH; y++) Pathinding[y] = (int*) malloc(sizeof(int)*CW);
	for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) Pathinding[y][x] = tab[y][x];
	Pathinding[start.y][start.x] = 2;
	int change;
	do{
		change = 0;
		for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++){
			if(Pathinding[y][x] == 1){
				int DN = 0;
				for(int ty = -1; ty <= 1 ; ty++) for(int tx = -1; tx <= 1; tx++)
					if((x+tx) > 0 && (x+tx) < CW && (y+ty) > 0 && (y+ty) < CH && !(x == tx && y == ty))
						if(Pathinding[y+ty][x+tx] == 2) DN++;
				if(DN>0){
					Pathinding[y][x] = 2;
					change++;
				}
			}
		}
		if(Pathinding[end.y][end.x] == 2) return true;
		if(Pathinding[end.y][end.x] == 0) return false;
		// printf("changes = %d\n", change);
	}while(change != 0);
	return Pathinding[end.y][end.x] == 2;
}

bool IsAllLinker(int **tab,int CW,int CH, coord2D start, coord2D end){
	int **Pathinding;
	Pathinding = (int**) malloc(sizeof(int*)*CH);
	for(int y = 0; y<CH; y++) Pathinding[y] = (int*) malloc(sizeof(int)*CW);
	for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) Pathinding[y][x] = tab[y][x];
	for(int x = 0; x<CW; x++) for(int y = 0; y<CH; y++) if(tab[y][x] && !(y == start.y && x == start.x) && !(y == end.y && x == end.x)){
		Pathinding[y][x] = 0;
		if(IsStartAndEndLinked(Pathinding, CW, CH, start, end)) return false;
		Pathinding[y][x] = 1;
	}
	return true;
}

vector getNeyboorsVect(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius){
	vector newVect;
	newVect.x = 0;
	newVect.y = 0;
	for(int ty = -radius; ty <= radius ; ty++){
		for(int tx = -radius; tx <= radius; tx++){
			if((target.x+tx) > 0 && (target.x+tx) < CW && (target.y+ty) > 0 && (target.y+ty) < CH && !(target.x == tx && target.y == ty)){
				if(cellGrid[target.y+ty][target.x+tx].type == type){
					newVect.x += cosf(atan2f(ty, tx))*sqrtf(powf(tx,2)+powf(ty,2));
					newVect.y += sinf(atan2f(ty, tx))*sqrtf(powf(tx,2)+powf(ty,2));
					//printf("FOOD : %d, %d\n",target.x+tx,target.y+ty);
				}
			}
		}
	}
	if(newVect.x != 0 && newVect.y != 0) newVect = crunchSpeed(newVect, 1);
	return newVect;
}

int getBestStartingPoint(cell **cellGrid, int CW, int CH, int id, vector *SV, coord2D *SP, simulation sim){
	int BS = -50000;
	vector center = getBiomassCenter(cellGrid, CW, CH, id);
	*SP = new2Dcoord((int)floorf(center.x), (int)floorf(center.y));
	for(int x = 0; x<CW; x++){
		for(int y = 0; y<CH; y++){
			if(cellGrid[y][x].type == cell_blob && cellGrid[y][x].blob_id == id && cellGrid[y][x].blob_bm >= 100 && getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_empty, 6) > 5){
				int S = 0;
				S += cellGrid[y][x].blob_oscillation*5;
				S += getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_empty, sim.detectionRadius*2)*500;
				S -= getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_block, sim.detectionRadius*2)*5;
				S -= getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_blob, sim.detectionRadius*2)*10;
				S -= getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_blob, sim.detectionRadius*2) > (sim.detectionRadius*1.75) ? 10000 : 0;
				S -= getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_empty, sim.detectionRadius*2) < (sim.detectionRadius*1.6) ? 10000 : 0;
				S += getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_food, sim.detectionRadius*2)*1000;
				S += cellGrid[y][x].blob_type==blob_kernel ? 1000 : 0;
				S -= sqrt(pow((int)floorf(center.x)-x,2)+pow((int)floorf(center.y)-y,2))*4;
				if(S > BS || (S == BS && rand()%3 == 0)){
					BS = S;
					if(getNeyboors(cellGrid, CW, CH, new2Dcoord(x,y), cell_food, sim.detectionRadius) > 0) *SV = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord(x,y), cell_food, sim.detectionRadius);
					else *SV = getNeyboorsVect(cellGrid, CW, CH, new2Dcoord(x,y), cell_empty, sim.detectionRadius);
					//else{
					//	SV->x = 0;
					//	SV->y = 0;
					//}
					*SP = new2Dcoord(x,y);
				}
			}
		}
	}
	return BS;
}

int getNeyboors(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius){
	int SN = 0;
	for(int ty = -radius; ty <= radius ; ty++) for(int tx = -radius; tx <= radius; tx++)
		if((target.x+tx) > 0 && (target.x+tx) < CW && (target.y+ty) > 0 && (target.y+ty) < CH && !(target.x == tx && target.y == ty))
			if(cellGrid[target.y+ty][target.x+tx].type == type){
				SN++;
			}
	return SN;
}
vector getBiomassCenter(cell **cellGrid, int CW, int CH, int id){
	vector center;
	center.x = 0;
	center.y = 0;
	int Summ = 0;
	for(int y = 0; y < CH; y++){
		for(int x = 0; x < CW; x++){
			if(cellGrid[y][x].blob_id == id && cellGrid[y][x].type == cell_blob){
				Summ += cellGrid[y][x].blob_bm;
				center.x += cellGrid[y][x].blob_bm*x;
				center.y += cellGrid[y][x].blob_bm*y;
			}
		}
	}
	center.x /= Summ;
	center.y /= Summ;
	return center;
}

coord2D getPeriphPoint(cell **cellGrid, int CW, int CH, int id, vector center, float targetAngle, float teta){
	coord2D result;
	result.x = -1;
	result.y = -1;
	targetAngle *= 180/M_PI;
	teta *= 180/M_PI;
	int minAngle = (int)floorf(targetAngle - teta);
	int maxAngle = (int)floorf(targetAngle + teta);
	float maxDist = 0;
	minAngle %= 360;
	maxAngle %= 360;
	if(minAngle > maxAngle){
		float cache = minAngle;
		minAngle = maxAngle;
		maxAngle = minAngle;
	}
	for(int y = 0; y < CH; y++){
		for(int x = 0; x < CW; x++){
			if(cellGrid[y][x].blob_id == id && cellGrid[y][x].type == cell_blob && cellGrid[y][x].blob_bm > 250){
				float ang = atan2f(y-center.y,x-center.x)*(180/M_PI);
				if(ang > minAngle && ang < maxAngle && sqrtf(powf(y-center.y,2) + pow(x-center.x,2)) > maxDist ){
					maxDist = sqrtf(powf(y-center.y,2) + pow(x-center.x,2));
					result.x = x;
					result.y = y;
				}
			}
		}
	}
	return result;
}


vector crunchSpeed(vector vect, int speed){
	if(vect.x != 0 && vect.y != 0){
		float a = speed/(sqrtf(powf(vect.x, 2.0) + powf(vect.y, 2.0)));
		vect.x *= a;
		vect.y *= a;
	}
	if(vect.x == 0 && vect.y == 0);
	else{
		if(vect.y == 0) vect.x = vect.x > 0 ? 1 : -1;
		if(vect.x == 0) vect.y = vect.y > 0 ? 1 : -1;
	}
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
					newVect.x += (cosf(atan2f(ty-target.y, tx-target.x)))*(cellGrid[ty][tx].blob_oscillation - targetOscillation)*sqrtf(powf(ty-target.y,2) + powf(tx-target.x,2));
					newVect.y += (sinf(atan2f(ty-target.y, tx-target.x)))*(cellGrid[ty][tx].blob_oscillation - targetOscillation)*sqrtf(powf(ty-target.y,2) + powf(tx-target.x,2));
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
    newBLOB.id = newBlobID();
	newBLOB.totalCells = 30;
	newBLOB.cells = (coord2D*) malloc(sizeof(coord2D)*newBLOB.totalCells);
	if(newBLOB.cells == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniBlobCells)");
		exit(EXIT_FAILURE);
	}
	cellGrid[SP.y][SP.x] = newBlobCell(cellGrid, cellGrid[SP.y][SP.x].food_amount, blob_kernel, newBLOB.id, -1, 50000, cellGrid[SP.y][SP.x].mucus_amount, SP, -50);
	// if(cellGrid[SP.y][SP.x].type == cell_blob) printf("OK\n");
	newBLOB.Kernel_Start = new2Dcoord(SP.x, SP.y);
	int n = 1;
	while(n < (newBLOB.totalCells - 1)){
		for(int x = 0; x<CW; x++){
			for(int y = 0; y<CH; y++){
				if((cellGrid[y][x].type == cell_empty || cellGrid[y][x].type == cell_food || cellGrid[y][x].type == cell_mucus) && n < (newBLOB.totalCells - 1) && (rand()%19) == 0){
					int BN = 0;
					if(y < (CH - 1)) if(cellGrid[y+1][x].type == cell_blob && cellGrid[y+1][x].blob_id == newBLOB.id) BN++;
					if(y > 1) if(cellGrid[y-1][x].type == cell_blob && cellGrid[y-1][x].blob_id == newBLOB.id) BN++;
					if(x < (CW - 1)) if(cellGrid[y][x+1].type == cell_blob && cellGrid[y][x+1].blob_id == newBLOB.id) BN++;
					if(x > 1) if(cellGrid[y][x-1].type == cell_blob && cellGrid[y][x-1].blob_id == newBLOB.id) BN++;
					//printf("%d, %d\n", BN, n);
					if(BN > 0){
						cellGrid[y][x] = newBlobCell(cellGrid, cellGrid[y][x].food_amount, blob_kernel, newBLOB.id, -1, 40000, cellGrid[y][x].mucus_amount, new2Dcoord(x,y), -20);
						n++;
					}
				}
			}
		}
	}
    newBLOB.ants = NULL;
	newBLOB.path = NULL;
    newBLOB.nAnts = 0;
	newBLOB.isExpanding = true;
	newBLOB.pathIsSet = false;
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

void newAnt(ant **tab, int *tabSize, coord2D coords, float Vx, float Vy, int ttl, float oscillation, int id, int ramRarety){
	(*tabSize)++;
	if(*tabSize == 1){
		*tab = (ant*) malloc((*tabSize) * sizeof(ant));
	}else{
		*tab = (ant*) realloc(*tab, (*tabSize) * sizeof(ant));
	}
	(*tab)[*tabSize - 1].dead = false;
    (*tab)[*tabSize - 1].moov.x = Vx;
    (*tab)[*tabSize - 1].moov.y = Vy;
    (*tab)[*tabSize - 1].x = coords.x;
    (*tab)[*tabSize - 1].y = coords.y;
	if(Vx == -2) vectorGeneratorRand(&(*tab)[*tabSize - 1].moov.x, &(*tab)[*tabSize - 1].moov.y, 1);
    (*tab)[*tabSize - 1].t = 0;
    (*tab)[*tabSize - 1].ttl = ttl;
    (*tab)[*tabSize - 1].oscillation = oscillation;
	(*tab)[*tabSize - 1].id = id;
	(*tab)[*tabSize - 1].ramR = ramRarety;
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
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (inicellData 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<H; y++){
		(*tab)[y] = (cell*) malloc(sizeof(cell)*W);
		if((*tab)[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (inicellData 2:%d)", y);
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
	*tab = NULL;
}

void freeBlobs(blob_blob **blobs, int *n, int H){
	for(int i = 0; i < *n; i++){
		free((*blobs)[i].ants);
		for(int y = 0; y < H; y++) free((*blobs)[i].path[y]);
		free((*blobs)[i].path);
	}
	free(*blobs);
	*blobs = NULL;
	*n = 0;
}