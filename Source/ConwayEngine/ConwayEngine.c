#include "ConwayEngine.h" 

void ConnwayTransform(int **CellData, int MW, int MH){
	int CellDataCache[MH][MW];
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
	for(int x = 0; x<1000; x++) for(int y = 0; y<MH; y++) CellData[y][x] = CellDataCache[y][x];
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