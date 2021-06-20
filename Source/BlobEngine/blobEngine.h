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
    float oscillation;
}ant;

typedef struct{
    int id;
    coord2D *cells;
    int totalCells;
    ant *ants;
    int nAnts;
    bool isExpanding;
}blob_blob;

typedef struct{
    int ramificationRarity;
    int detectionRadius;
    float RepMucusMultiplicator;
    float RepWallMultiplicator;
    float RepSelfMultiplicator;
    float AtracFoodMultiplicator;
    float OscilInfluence;
}simulation;

//BLOB

void blobNewRound(cell **cellGrid, int CW, int CH, blob_blob *target_blob, int *BN, simulation sim);

// void blobFusion(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *mergedBlob);
// void blobDivision(cell **cellGrid, int CW, int CH, blob_blob *blob_target, blob_blob *newBlob);

blob_blob newBlob(cell **cellGrid, int CW, int CH, coord2D SP, simulation sim);
int newBlobID();
cell newEmptyCell();
cell newCell(cellType type, int food_amount, int blob_bm, int mucus_amount);
cell newBlobCell(cell **cellGrid, int food, blob_cellType blob_type, int id, int ttl, int bm, int mucus_amount, coord2D spawn, float oscillation);
void newAnt(ant **tab, int *tabSize, coord2D coords, float Vx, float Vy, int ttl, float oscillation);
void vectorGeneratorRand(float *Vx, float *Vy, int speed);
int getNeyboors(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius);
vector getOscilatorVect(cell **cellGrid, int CW, int CH, coord2D target, float targetOscillation, int id);
vector getNeyboorsVect(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius);
vector crunchSpeed(vector vect, int speed);
void iniCellData(cell ***tab, int W, int H);
void freeCellData(cell ***tab, int W, int H);