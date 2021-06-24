#include "../SmartUI/SmartUI.h"
typedef enum{cell_empty, cell_block, cell_food, cell_blob, cell_mucus}cellType;
typedef enum{blob_none, blob_harvest, blob_kernel, blob_vein, blob_plasma}blob_cellType;

typedef struct{
    float x;
    float y;
}vector;

typedef struct{
    cellType type;
    int food_amount;
    blob_cellType blob_type;
    int blob_id;
    int blob_ttl;
    int blob_bm;
    int mucus_amount;
    int blob_oscillation;
    color color;
}cell;

typedef struct{
    bool dead;
    vector moov;
    float x;
    float y;
    int t;
    int ttl;
    int id;
    float oscillation;
    int ramR;
}ant;

typedef struct{
    int id;
    coord2D *cells;
    int totalCells;
    ant *ants;
    int nAnts;
    bool isExpanding;
    coord2D Kernel_Start;
    coord2D Food_End;
    bool pathIsSet;
    int **path;
    int pathSize;
}blob_blob;

typedef struct{
    int ramificationRarity;
    int detectionRadius;
    float RepMucusMultiplicator;
    float RepWallMultiplicator;
    float RepSelfMultiplicator;
    float AtracFoodMultiplicator;
    float AtracEmptyMultiplicator;
    float OscilInfluence;
}simulation;

//BLOB

void blobNewRound(cell **cellGrid, int CW, int CH, blob_blob *target_blob, int *BN, simulation sim);

bool IsStartAndEndLinked(int **tab,int CW,int CH,coord2D start, coord2D end);
bool IsAllLinker(int **tab,int CW,int CH,coord2D start, coord2D end);
// void blobFusion(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *mergedBlob);
// void blobDivision(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *newBlob);
int getBestStartingPoint(cell **cellGrid, int CW, int CH, int id, vector *SV, coord2D *SP, simulation sim);
// void getEscapeVector(cell **cellGrid, int CW, int CH, coord2D target, int id, vector *escapeVector, coord2D *escapePoint);
vector getNeyboorsVect(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius);
int getNeyboors(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius);
vector getBiomassCenter(cell **cellGrid, int CW, int CH, int id);
// coord2D getPeriphPoint(cell **cellGrid, int CW, int CH, int id, vector center, float targetAngle, float teta);
vector crunchSpeed(vector vect, int speed);
vector getOscilatorVect(cell **cellGrid, int CW, int CH, coord2D target, float targetOscillation, int id);
blob_blob newBlob(cell **cellGrid, int CW, int CH, coord2D SP, simulation sim);
void freeBlobs(blob_blob **blobs, int *n, int H);
cell newBlobCell(cell **cellGrid, int food, blob_cellType blob_type, int id, int ttl, int bm, int mucus_amount, coord2D spawn, float oscillation);
cell newCell(cellType type, int food_amount, int blob_bm, int mucus_amount);
cell newEmptyCell();
int newBlobID();
void newAnt(ant **tab, int *tabSize, coord2D coords, float Vx, float Vy, int ttl, float oscillation, int id, int ramRarety);
void vectorGeneratorRand(float *Vx, float *Vy, int speed);
void iniCellData(cell ***tab, int W, int H);
void freeCellData(cell ***tab, int W, int H);