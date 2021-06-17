typedef enum{empty, block, food, blob, fb}cellType;
typedef enum{none, food, kernel, vein, plasma}blob_cellType;

typedef struct{
    cellType type;
    int food_amount;
    blob_cellType blob_type;
    int blob_id;
    int blob_ttl;
    int blob_bm;
    int blob_nutr;
    color color;
}cell;

typedef struct{
    coord2D coord2D;
    float x;
    float y;
    float vector.x;
    float vector.y;
    coord2D *path;
    int t;
    int ttl;
}blob_agent;

typedef struct{
    cellType type;
    int food_amount;
    blob_cellType blob_type;
    int blob_id;
    int blob_ttl;
    int blob_bm;
    int blob_nutr;
    int blob_request_bm;
    int blob_request_nutr;
    coord2D coord2D;
}blob_cell;

typedef struct{
    int id;
    blob_cell *cells;
    int totalCells;
    int harvest_totalFood;
    int harvest_foodPR;
    int stock_totalNutr;
    int stock_nutrPR;
    int biomass_totalBiomass;
    int biomass_biomassPR;
    blob_agent *agents;
    int nAgents;
}blob;

typdef struct{
    float TranCap; //Multip. de transport par unité de biomasse
    float FoodCons; //Multip. de consomation de nutriments par unitées de biomasse
    float VeinCap; //Capacitée de transport des corps veneux
    int TranSpeed; //Nombre d'itérations de transport par tours
    int SeuilCredit; //Seuil d'endettement pouvant causer la mort d'une entitée.
    int TTLCredit; //Nombre de tours qu'une cellule peut passée en dépassant le seuil.
}simulation;

//BLOB
blob newBlob(cell **cellGrid, int CW, int CW, blob *blob, int *BN, coord2D SP, int ttf, int ttnutr, int ttbio);
blob_cell newBlobCell(cell **cellGrid, cellType type, int food, blob_cellType blob_type, int id, int ttl, int bm, int nutr, coord2D spawn);
    
cell newCell(cellType type, int food_amount, blob_cellType blob_type, int blob_id, int blob_ttl, int blob_bm, int blob_nutr);
cell newEmptyCell();

void blobNewRound(cell **cellGrid, int CW, int CW, blob *blob);
void blobFusion(cell **cellGrid, int CW, int CW, blob *blob, blob *mergedBlob);
void blobDivision(cell **cellGrid, int CW, int CW, blob *blob, blob *newBlob);
int getNeyboorsByType(cell **cellGrid, int CW, int CW, coord2D target, cellType type);
int newBlobID();
