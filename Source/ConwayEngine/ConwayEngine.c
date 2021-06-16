#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600
#define MATRIX_H 500
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
	static int DeltaX = MATRIX_W/4;
	static int DeltaY = MATRIX_H/4;
	static bool pause = true;
	static bool RCD = false;
	static int XDRC = 0;
	static int YDRC = 0;
	switch (evenement)
	{
		case Initialisation:
			//Initialisation de la matrice de données
			iniCellData(CellData);
			//Calcul de la capacité d'affichage avec la taille de fenêtre courante
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			//Lancement de la routine
			demandeTemporisation(60);
        break;

		case Temporisation: ;
			//Mise à jour de la capacité d'affichage avec la taille de fenêtre courante
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			//Log si le nombre de cellules potentielles > cellules réelles
			if(HcellCap > MATRIX_H || WcellCap > MATRIX_W) printf("ERREUR CRITIQUE : AFFICHAGE SUR L'AXE %s COMPROMIS\n", HcellCap > MATRIX_H ? "Y" : "X");
			//Calcul et application de t+1 (Si la pause n'est pas active)
			if(!pause){
				for(int x = 0; x<MATRIX_W; x++){
					for(int y = 0; y<MATRIX_H; y++){
						//Récupération de voisins
						int AN = getAliveNeyboors(CellData, x, y, MATRIX_W, MATRIX_H);
						//Calcul de l'état à t+1 pour chaque cellules et stockage dans le cache 
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
				//Merging du cache
				for(int x = 0; x<1000; x++) for(int y = 0; y<MATRIX_H; y++) CellData[y][x] = CellDataCache[y][x];
			}
			rafraichisFenetre();
			break;
		
		case Affichage:
			effaceFenetre (0, 0, 0);
			//Affichage de la grille, avec :
			//x,y les coordonnées dans la matrices
			//LBCx, LBCy les coordonnées du point infèrieur gauche du carré dans la fenêtre
			//RTCx, RTCy les coordonnées du point supèrieur droit du carré dans la fenêtre
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
				if ((Sx < MATRIX_W) && (Sy < MATRIX_H))
					if (((Sx) < MATRIX_W) && ((Sy) < MATRIX_H) && ((Sx) >= 0) && ((Sy) >= 0)) CellData[Sy][Sx] = !CellData[Sy][Sx];
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
			
			if(etatBoutonSouris() == DroiteRelache){
				RCD = false;
			}

			if(NeedScrollUpdate){
				HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				WcellCap = (largeurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				DeltaX += floorf(fx) - floorf(abscisseSouris() / (CellSize + CellInBetween));
				DeltaY += floorf(fy) - floorf(ordonneeSouris() / (CellSize + CellInBetween));
				if(DeltaX < 0) DeltaX = 0;
				if(DeltaX + WcellCap >= MATRIX_W) DeltaX = MATRIX_W - WcellCap;
				if(DeltaY < 0) DeltaY = 0;
				if(DeltaY + HcellCap >= MATRIX_H) DeltaY = MATRIX_H - HcellCap;
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
				if(DeltaX + WcellCap - 1 >= MATRIX_W) DeltaX = MATRIX_W - WcellCap;
				if(DeltaY < 0) DeltaY = 0;
				if(DeltaY + HcellCap - 1 >= MATRIX_H) DeltaY = MATRIX_H - HcellCap;
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
void iniCellData(int tab[][MATRIX_W]){
	for(int x = 0; x<MATRIX_W; x++) for(int y = 0; y<MATRIX_H; y++) tab[y][x] = 0;
}

//Calcul des voisins vivants
int getAliveNeyboors(int tab[][MATRIX_W], int x, int y, int xmax, int ymax){
	int AN = 0;
	for(int ty = -1; ty < 2 ; ty++){
		for(int tx = -1; tx < 2; tx++){
			if((x+tx) > 0 && (x+tx) < xmax && (y+ty) > 0 && (y+ty) < ymax) 
				if(tab[y+ty][x+tx] == 1) AN++;
		}
	}
	return (AN-tab[y][x]);
};