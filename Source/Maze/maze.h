#include <time.h>

void mazeEngine(int **tab, int W, int H);									 
void updateMetaData(int **metaData, int id1, int id2, int W, int H); 
void setMetaData(int **metaData, int **mazeData, int W, int H);		 
void printMazeData(int **mazeData, int **CellData, int W, int H, int size);   