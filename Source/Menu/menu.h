/*

.___  ___.  _______ .__   __.  __    __  
|   \/   | |   ____||  \ |  | |  |  |  | 
|  \  /  | |  |__   |   \|  | |  |  |  | 
|  |\/|  | |   __|  |  . `  | |  |  |  | 
|  |  |  | |  |____ |  |\   | |  `--'  | 
|__|  |__| |_______||__| \__|  \______/  
                                         
*/

// Affiche le menu de contrôle du Blob
void printContextMenu(button *buttons, slider *sliders, text *texts, button *buttons2, slider *sliders2, text *texts2, int MenuWidth, int nSliders, int nButtons, int nTexts, int nSliders2, int nButtons2, int nTexts2, int vivant, int Sx2, int Sy2, int gen, simulation *sim, bool menuType, DonneesImageRGB *header);

// Initialise le menu de contrôle du Blob
void iniContextMenu(DonneesImageRGB **header, int *nTexts, text **texts, int *nSliders, slider **sliders, int *nButtons, button **buttons, int *nTexts2, text **texts2, int *nButtons2, button **buttons2, int *nSliders2, slider **sliders2, int MenuWidth, simulation sim);

void mainMenu(EvenementGfx evenement, action *Action, int *DataSizeX, int *DataSizeY);
void iniGridData(int ***tab, int W, int H); //Initialise toutes les cellules en cellules mortes
void iniColors(color ***tab, int W, int H); //Initialise le tableau associé aux couleurs des cellules
void initRandom(int **tabCell, int W, int H, color **tabCol); //Mets un peu de couleurs dans la matrice

void freeGridData(int ***tab, int W, int H); //Libère les données
void freeColors(color ***tab, int W, int H); //Libère les données

void save(int **tabCell, int W, int H, color **tabCol); //Sauvegarde la matrice dans un fichier .cnw
void load(int **tabCell, int W, int H, color **tabCol, action Action); //Charge la matrice depuis un fichier .cnw

void loadBMP(int **tabCell, color **tabCol); //Sauvegarde la matrice dans un fichier .bmp
void saveBMP(int **tabCell, int W, int H, color **tabCol); //Charge la matrice depuis un fichier .bmp