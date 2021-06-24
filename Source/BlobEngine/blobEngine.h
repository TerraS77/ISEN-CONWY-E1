/* 

    .______    __        ______   .______       _______ .__   __.   _______  __  .__   __.  _______  
    |   _  \  |  |      /  __  \  |   _  \     |   ____||  \ |  |  /  _____||  | |  \ |  | |   ____| 
    |  |_)  | |  |     |  |  |  | |  |_)  |    |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__   
    |   _  <  |  |     |  |  |  | |   _  <     |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|  
    |  |_)  | |  `----.|  `--'  | |  |_)  |    |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____ 
    |______/  |_______| \______/  |______/     |_______||__| \__|  \______| |__| |__| \__| |_______|

	Version 1.0 (24/06/2021) : Optimisation de Blob Engine                                                                 
*/



#include "../SmartUI/SmartUI.h"

// Types de cellules
typedef enum{cell_empty, cell_block, cell_food, cell_blob, cell_mucus}cellType;
typedef enum{blob_none, blob_harvest, blob_kernel, blob_vein, blob_plasma}blob_cellType;

//Vecteurs
typedef struct{
    float x;
    float y;
}vector;

//Cellule
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


//Agents
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

//Blob
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

//Paramètres de la simulation
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


//Branche de simulation principale
void blobNewRound(cell **cellGrid, int CW, int CH, blob_blob *target_blob, int *BN, simulation sim);

//Tests de simplification
bool IsStartAndEndLinked(int **tab,int CW,int CH,coord2D start, coord2D end);
bool IsAllLinker(int **tab,int CW,int CH,coord2D start, coord2D end);

//Choix d'un poinnt de départ et d'un vecteur initial pour l'agent suivant
int getBestStartingPoint(cell **cellGrid, int CW, int CH, int id, vector *SV, coord2D *SP, simulation sim);

//Vecteur de réaction associé aux voinsins spécifiés
vector getNeyboorsVect(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius);
vector getOscilatorVect(cell **cellGrid, int CW, int CH, coord2D target, float targetOscillation, int id);

//Nombre de voisins spécifiés
int getNeyboors(cell **cellGrid, int CW, int CH, coord2D target, cellType type, int radius);

//coordonées en float du centre de biomasse du blob
vector getBiomassCenter(cell **cellGrid, int CW, int CH, int id);

//Constructeurs et destructeurs
blob_blob newBlob(cell **cellGrid, int CW, int CH, coord2D SP, simulation sim);
int newBlobID();
cell newBlobCell(cell **cellGrid, int food, blob_cellType blob_type, int id, int ttl, int bm, int mucus_amount, coord2D spawn, float oscillation);
void freeBlobs(blob_blob **blobs, int *n, int H);
cell newCell(cellType type, int food_amount, int blob_bm, int mucus_amount);
cell newEmptyCell();

//Création d'un agent
void newAnt(ant **tab, int *tabSize, coord2D coords, float Vx, float Vy, int ttl, float oscillation, int id, int ramRarety);

//Opérations sur les vecteurs
void vectorGeneratorRand(float *Vx, float *Vy, int speed);
vector crunchSpeed(vector vect, int speed);

//Constructeur et destructeur de la grille de cellules
void iniCellData(cell ***tab, int W, int H);
void freeCellData(cell ***tab, int W, int H);