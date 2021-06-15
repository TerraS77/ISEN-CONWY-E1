#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600
#define MATRIX_H 1000
#define MATRIX_W 1000

void gestionEvenement(EvenementGfx evenement);
void iniCellData(int tab[][1000]);
int getAliveNeyboors(int tab[][1000], int x, int y, int xmax, int ymax);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("SMART GRID", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
	static int HcellCap; //Nombre de celulles pouvant être affichées en hauteur
	static int WcellCap; //Nombre de celulles pouvant être affichées en largeur 
	static int CellData[MATRIX_H][MATRIX_W]; //Matrice de donnée
	static int CellDataCache[MATRIX_H][MATRIX_W]; //Cache de la matrice (utilisé pour t+1 à partir de t)
	static int CellSize = 10; //Taille d'une cellule en pixel
	static int CellInBetween = 1; //Taille de l'espace inter cellules  en pixel
	static bool pause = true;
	switch (evenement)
	{
		case Initialisation:
			//Initialisation de la matrice de données
			iniCellData(CellData);
			//Calcul de la capacité d'affichage avec la taille de fenêtre courante
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			//Lancement de la routine
			demandeTemporisation(100);
        break;

		case Temporisation: ;
			//Mise à jour de la capacité d'affichage avec la taille de fenêtre courante
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			if(!pause){
				for(int x = 0; x<WcellCap; x++){
					for(int y = 0; y<HcellCap; y++){
						int AN = getAliveNeyboors(CellData, x, y, WcellCap, HcellCap);
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
				for(int x = 0; x<1000; x++) for(int y = 0; y<MATRIX_H; y++) CellData[y][x] = CellDataCache[y][x];
			}
			rafraichisFenetre();
			break;
		
		case Affichage:
			effaceFenetre (0, 0, 0);
			for(int y = 0; y < HcellCap; y++){
				for(int x = 0; x < WcellCap; x++){
					int LBCx = x*(CellSize + CellInBetween)+CellInBetween;
					int LBCy = (y+1)*(CellSize + CellInBetween);
					int RYCx = (x+1)*(CellSize + CellInBetween);
					int RYCy = y*(CellSize + CellInBetween)+CellInBetween;
					CellData[y][x] == 0 ? couleurCourante(0,0,0) : couleurCourante(255, 255, 255);
					rectangle(LBCx,LBCy,RYCx,RYCy);
				}
			}
		break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye){
				float fx = abscisseSouris() / (CellSize + CellInBetween);
				float fy = ordonneeSouris() / (CellSize + CellInBetween);
				int Sx = floorf(fx);
				int Sy = floorf(fy);
				if((Sx < MATRIX_W) && (Sy < MATRIX_H)){
					if(((Sx) < MATRIX_W) && ((Sy) < MATRIX_H) && ((Sx) >= 0) && ((Sy) >= 0)) CellData[Sy][Sx] = !CellData[Sy][Sx];
				}
			}
			if(etatBoutonSouris() == ScrollUp && CellSize < 50) CellSize += 5;
			if(etatBoutonSouris() == ScrollDown && CellSize > 5)  CellSize -= 5;
			break;
		case Clavier:
			if(caractereClavier() == 32) pause = !pause;
			break;
		case Redimensionnement:
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			break;
	}
}

void iniCellData(int tab[][MATRIX_W]){
	for(int x = 0; x<MATRIX_W; x++) for(int y = 0; y<MATRIX_H; y++) tab[y][x] = 0;
}

int getAliveNeyboors(int tab[][MATRIX_W], int x, int y, int xmax, int ymax){
	int AN = 0;
	// if(tab[y][x] == 1) printf("========\n%d, %d :\n", x, y);
	for(int ty = -1; ty < 2 ; ty++){
		for(int tx = -1; tx < 2; tx++){
			// if(tab[y][x] == 1) printf("> %d/%d = %d\n", x+tx, y+ty, tab[y+ty][x+tx]);
			if((x+tx) > 0 && (x+tx) < xmax && (y+ty) > 0 && (y+ty) < ymax) if(tab[y+ty][x+tx] == 1) AN++;
		}
	}
	// if(tab[y][x] == 1) printf("AN : %d\n", AN-tab[y][x]);
	return (AN-tab[y][x]);
};