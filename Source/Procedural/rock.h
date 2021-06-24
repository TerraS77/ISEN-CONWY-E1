/*

    .___  ___.      ___       __  ___  _______    .___  ___.  _______         ___         .______        ______     ______  __  ___ 
    |   \/   |     /   \     |  |/  / |   ____|   |   \/   | |   ____|       /   \        |   _  \      /  __  \   /      ||  |/  / 
    |  \  /  |    /  ^  \    |  '  /  |  |__      |  \  /  | |  |__         /  ^  \       |  |_)  |    |  |  |  | |  ,----'|  '  /  
    |  |\/|  |   /  /_\  \   |    <   |   __|     |  |\/|  | |   __|       /  /_\  \      |      /     |  |  |  | |  |     |    <   
    |  |  |  |  /  _____  \  |  .  \  |  |____    |  |  |  | |  |____     /  _____  \     |  |\  \----.|  `--'  | |  `----.|  .  \  
    |__|  |__| /__/     \__\ |__|\__\ |_______|   |__|  |__| |_______|   /__/     \__\    | _| `._____| \______/   \______||__|\__\ 

    Version 1.0 (24/06/2021) : Création du générateur d'environnement                                                                                                                   
*/

// Créer des rochers
void makeRock( int ***tab,int W,int H);

// Créer des trous
void bakeHole( int ***tab, int W, int H);

// Créer un tableau stockant tout l'environnement généré
void RockPanel (int nC, int **CellData, int DataSizeX, int DataSizeY);

// Détecte les voisins vivants
int getAliveNeyboors(int **tab, int x, int y, int xmax, int ymax);