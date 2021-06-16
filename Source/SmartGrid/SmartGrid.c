#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "../GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "../ConwayEngine/ConwayEngine.h"
#include "../SmartUI/SmartUI.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600
#define MATRIX_H 500
#define MATRIX_W 1000

void gestionEvenement(EvenementGfx evenement);
void iniCellData(int ***tab, int DataSizeX, int DataSizeY);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("SMART GRID", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
	static int DataSizeX = MATRIX_W;
	static int DataSizeY = MATRIX_H;
	static int HcellCap; //Nombre de celulles pouvant être affichées en hauteur
	static int WcellCap; //Nombre de celulles pouvant être affichées en largeur 
	static int **CellData = NULL; //Matrice de donnée
	static int CellSize = 10; //Taille d'une cellule en pixel
	static int CellInBetween = 1; //Taille de l'espace inter cellules  en pixel
	static int DeltaX = 0;
	static int DeltaY = 0;
	static bool pause = true;
	static bool RCD = false;
	static int XDRC = 0;
	static int YDRC = 0;
	switch (evenement)
	{
		case Initialisation:
			iniCellData(&CellData, DataSizeX, DataSizeY);
			DeltaX = DataSizeX/4;
			DeltaY = DataSizeY/4;
			demandeTemporisation(60);
        break;
		
		case Temporisation: ;
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			if(HcellCap > DataSizeY || WcellCap > DataSizeX) printf("ERREUR CRITIQUE : AFFICHAGE SUR L'AXE %s COMPROMIS\n", HcellCap > DataSizeY ? "Y" : "X");
			if(!pause) ConnwayTransform(CellData, DataSizeX, DataSizeY);
			rafraichisFenetre();
			break;
		
		case Affichage:
			effaceFenetre (0, 0, 0);
			for (int y = DeltaY; y < (HcellCap + 1 + DeltaY); y++){
				for (int x = DeltaX; x < (WcellCap + 1 + DeltaX); x++){
					int LBCx = x * (CellSize + CellInBetween) + CellInBetween - (DeltaX * (CellSize + CellInBetween));
					int LBCy = (y + 1) * (CellSize + CellInBetween) - (DeltaY * (CellSize + CellInBetween));
					int RTCx = (x + 1) * (CellSize + CellInBetween) - (DeltaX * (CellSize + CellInBetween));
					int RTCy = y * (CellSize + CellInBetween) + CellInBetween - (DeltaY * (CellSize + CellInBetween));
					CellData[y][x] == 0 ? couleurCourante(20, 20, 20) : couleurCourante(255, 255, 255);
					rectangle(LBCx, LBCy, RTCx, RTCy);
				}
			}
			break;

		case BoutonSouris:;
			float fx = abscisseSouris() / (CellSize + CellInBetween);
			float fy = ordonneeSouris() / (CellSize + CellInBetween);
			if (etatBoutonSouris() == GaucheAppuye){
				//Indentification de la ceullule cible
				int Sx = floorf(fx) + DeltaX;
				int Sy = floorf(fy) + DeltaY;
				//Safe check pour les coordonées en dehors de la grille et inversion de l'état.
				if ((Sx < DataSizeX) && (Sy < DataSizeY))
					if (((Sx) < DataSizeX) && ((Sy) < DataSizeY) && ((Sx) >= 0) && ((Sy) >= 0)) CellData[Sy][Sx] = !CellData[Sy][Sx];
			}
			//AddOn Zoom sur la grille
			bool NeedScrollUpdate = false;
			if (etatBoutonSouris() == ScrollUp && CellSize < 50 && !RCD){
				CellSize *= 1.4;
				NeedScrollUpdate = true;
			}
			if (etatBoutonSouris() == ScrollDown && CellSize > 4 && !RCD){
				CellSize *= 0.6;
				if(CellSize < 4) CellSize = 4;
				NeedScrollUpdate = true;
			}

			if(etatBoutonSouris() == DroiteAppuye){
				XDRC = abscisseSouris() / (CellSize + CellInBetween);
				YDRC = ordonneeSouris() / (CellSize + CellInBetween);
				RCD = true;
			}
			
			if(etatBoutonSouris() == DroiteRelache) RCD = false;

			if(NeedScrollUpdate){
				HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				DeltaX += floorf(fx) - floorf(abscisseSouris() / (CellSize + CellInBetween));
				DeltaY += floorf(fy) - floorf(ordonneeSouris() / (CellSize + CellInBetween));
				if(DeltaX < 0) DeltaX = 0;
				if(DeltaX + WcellCap >= DataSizeX) DeltaX = DataSizeX - WcellCap;
				if(DeltaY < 0) DeltaY = 0;
				if(DeltaY + HcellCap >= DataSizeY) DeltaY = DataSizeY - HcellCap;
			}

			rafraichisFenetre();
			break;
		case Souris:
			if(RCD){
				DeltaX += floorf(XDRC) - floorf(abscisseSouris() / (CellSize + CellInBetween));
				DeltaY += floorf(YDRC) - floorf(ordonneeSouris() / (CellSize + CellInBetween));
				XDRC = abscisseSouris() / (CellSize + CellInBetween);
				YDRC = ordonneeSouris() / (CellSize + CellInBetween);
				if(DeltaX < 0) DeltaX = 0;
				if(DeltaX + WcellCap - 1 >= DataSizeX) DeltaX = DataSizeX - WcellCap;
				if(DeltaY < 0) DeltaY = 0;
				if(DeltaY + HcellCap - 1 >= DataSizeY) DeltaY = DataSizeY - HcellCap;
			}
			break;
		case Clavier:
			//Système Start/Stop (initialement stop)
			if(caractereClavier() == 32) pause = !pause;
			break;
		case Redimensionnement:
			//Mise à jour de la fenêtre
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			rafraichisFenetre();
			break;
	}
}

//Initialisation à 0 de la matrice
void iniCellData(int ***tab, int W, int H){
	*tab = (int**) malloc(sizeof(int*)*H);
	for(int y = 0; y<H; y++) (*tab)[y] = (int*) malloc(sizeof(int)*W);
	for(int x = 0; x<W; x++) for(int y = 0; y<H; y++) (*tab)[y][x] = 0;
}