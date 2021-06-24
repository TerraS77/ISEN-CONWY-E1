/*

    .___  ___.  _______ .__   __.  __    __  
    |   \/   | |   ____||  \ |  | |  |  |  | 
    |  \  /  | |  |__   |   \|  | |  |  |  | 
    |  |\/|  | |   __|  |  . `  | |  |  |  | 
    |  |  |  | |  |____ |  |\   | |  `--'  | 
    |__|  |__| |_______||__| \__|  \______/  

    Version 1.1 (24/06/2021) : Refonte du menu principal
    Version 1.0 (23/06/2021) : Regroupement de tous les menus dans un fichier                         
*/

// Affiche le menu de contrôle du Blob
void printContextMenu(button *buttons, slider *sliders, text *texts, button *buttons2, slider *sliders2, text *texts2, int MenuWidth, int nSliders, int nButtons, int nTexts, int nSliders2, int nButtons2, int nTexts2, int vivant, int Sx2, int Sy2, int gen, simulation *sim, bool menuType, DonneesImageRGB *header);

// Initialise le menu de contrôle du Blob
void iniContextMenu(DonneesImageRGB **header, int *nTexts, text **texts, int *nSliders, slider **sliders, int *nButtons, button **buttons, int *nTexts2, text **texts2, int *nButtons2, button **buttons2, int *nSliders2, slider **sliders2, int MenuWidth, simulation sim);

// Menu Principal
void mainMenu(EvenementGfx evenement, action *Action, int *DataSizeX, int *DataSizeY);

//Initialise toutes les cellules en cellules mortes
void iniGridData(int ***tab, int W, int H);

//Initialise le tableau associé aux couleurs des cellules
void iniColors(color ***tab, int W, int H);

void freeGridData(int ***tab, int W, int H); //Libère les données
void freeColors(color ***tab, int W, int H); //Libère les données

// Libère les pointeurs
void FreePointer(void **pointer);