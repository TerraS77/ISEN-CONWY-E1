#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include <dirent.h>
#include "../GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "../ConwayEngine/ConwayEngine.h"
#include "../SmartUI/SmartUI.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1200
#define HauteurFenetre 800
#define MATRIX_H 500
#define MATRIX_W 1000

void gestionEvenement(EvenementGfx evenement);
void iniCellData(int ***tab, int DataSizeX, int DataSizeY);
void freeCellData(int ***tab, int W, int H);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("SMART GRID", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
	//Matrice de données
	static int DataSizeX = MATRIX_W;
	static int DataSizeY = MATRIX_H;
	static int **CellData = NULL;
	static int tickCount = 0;

	//Drag&Snap et Zoom
	static int DeltaX = 0;
	static int DeltaY = 0;
	static bool RCD = false;
	static int XDRC = 0;
	static int YDRC = 0;

	//Affichage
	static int CellSize = 10;
	static int CellInBetween = 1;
	static int HcellCap;
	static int WcellCap;

	//Menu Elements
	static bool pause = true;
	static int MenuWidth = 290;
	static bool MenuStatus = false;
	static DonneesImageRGB *header = NULL;
	static button *buttons = NULL;
	static slider *sliders = NULL;
	static text *texts = NULL;
	static int nButtons = 0;
	static int nSliders = 0;
	static int nTexts = 0;
	static unsigned long int generationNumber = 0;
	static int vivant=0;
	static int gen=0;
	static int positionX=0;
	static int positionY=0;
	static int seuil=0;
	static int tick = 0;


	switch (evenement){
		case Initialisation:
			;
			//Menu
			header = lisBMPRGB("#Ressources/header.bmp");
			color RGBIdle = newColor(45,45,48);
			color RGBHover = newColor(55,55,58);
			color RGBClick = newColor(8,86,123);
			color RGBwhite = newColor(255,255,255);
			coord2D Origin = new2Dcoord(largeurFenetre() - MenuWidth, hauteurFenetre() - 80);

			//TXT
			nTexts = 6;
			texts = malloc(sizeof(text)*nTexts);
			texts[0] = newText(RGBwhite, RGBwhite, RGBwhite, 50, new2Dcoord(largeurFenetre() - MenuWidth + 20, hauteurFenetre() - 50), "CONWAY'S", 4);
			texts[1] = newText(RGBwhite, RGBwhite, RGBwhite, 25, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 80), "Game of Life", 2);
			texts[2]=newText(RGBwhite,RGBwhite,RGBwhite, 25,new2Dcoord(largeurFenetre()-MenuWidth +30,hauteurFenetre() - 180),"Vivant: 0", 2);
			texts[3] =newText(RGBwhite,RGBwhite,RGBwhite, 25,new2Dcoord(largeurFenetre()-MenuWidth +30,hauteurFenetre() - 225),"Generation : 0", 2);
			texts[4] =newText(RGBwhite,RGBwhite,RGBwhite, 25,new2Dcoord(largeurFenetre()-MenuWidth +30,hauteurFenetre() - 270),"X:", 2);
			texts[5] =newText(RGBwhite,RGBwhite,RGBwhite, 25,new2Dcoord(largeurFenetre()-MenuWidth +150,hauteurFenetre() - 270),"Y:", 2);
			
			//SLIDER
			nSliders = 1;
			sliders = malloc(sizeof(slider)*nSliders);
			sliders[0] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150,hauteurFenetre() - 400), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed,false);
			sliders[0].value= 100;

			//BUTTONS
			nButtons = 3;
			buttons = malloc(sizeof(button)*nButtons);
			buttons[0]=newButton(new2Dcoord(largeurFenetre() - MenuWidth + 150,hauteurFenetre() - 760), 150, 50, RGBIdle,RGBHover, RGBClick,newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 25, new2Dcoord(0,0), "Quitter", 2), Leave, false, false);
			buttons[1]=newButton(new2Dcoord(largeurFenetre() - MenuWidth + 90,hauteurFenetre() - 700), 100, 50, RGBIdle,RGBHover, RGBClick,newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 25, new2Dcoord(0,0), "Pause", 2), TogglePause, true, true);
			buttons[2]=newButton(new2Dcoord(largeurFenetre() - MenuWidth + 200,hauteurFenetre() - 700), 100, 50, RGBIdle,RGBHover, RGBClick,newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 25, new2Dcoord(0,0), "Reset", 2), RESET, false, false);
			//Data
			iniCellData(&CellData, DataSizeX, DataSizeY);
			DeltaX = DataSizeX/4;
			DeltaY = DataSizeY/4;
			demandeTemporisation(30);
        break;
		
		case Temporisation: ;

			//Data process
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
			
			if(HcellCap > DataSizeY || WcellCap > DataSizeX){
				printf("ERREUR CRITIQUE : AFFICHAGE SUR L'AXE %s COMPROMIS\n", HcellCap > DataSizeY ? "Y" : "X");
				exit(EXIT_FAILURE);
			}

			seuil = 1 / ((float) (sliders->value + 1.0) / (float) sliders->max);
			if(!pause){ 
				tick++;
				if(tick>=seuil) tick = 0;
				if(tick==0){
					conwayTransform(CellData, DataSizeX, DataSizeY);
					gen++;
				} 
			}

			//Menu
			if(MenuStatus){
				vivant = Vivant(CellData,DataSizeX,DataSizeY);
				char string[64];
				sprintf(string,"Cellules: %d",vivant);
				texts[2]=newText(newColor(255,255,255),newColor(255,255,255),newColor(255,255,255), 25,new2Dcoord(largeurFenetre()-MenuWidth +30,hauteurFenetre() - 180),string, 2);
				char string2[64];
				sprintf(string2,"Generation: %d",gen);
				texts[3] =newText(newColor(255,255,255),newColor(255,255,255),newColor(255,255,255), 25,new2Dcoord(largeurFenetre()-MenuWidth +30,hauteurFenetre() - 225),string2, 2);
				float fx2 = abscisseSouris() / (CellSize + CellInBetween);
				float fy2 = ordonneeSouris() / (CellSize + CellInBetween);
				int Sx2 = floorf(fx2) + DeltaX;
				int Sy2 = floorf(fy2) + DeltaY;
				char string3[100];
				sprintf(string3,"X: %d",Sx2);
				texts[4] =newText(newColor(255,255,255),newColor(255,255,255),newColor(255,255,255), 25,new2Dcoord(largeurFenetre()-MenuWidth +30,hauteurFenetre() - 270),string3, 2);
				char string4[100];
				sprintf(string4,"Y: %d",Sy2);
				texts[5] =newText(newColor(255,255,255),newColor(255,255,255),newColor(255,255,255), 25,new2Dcoord(largeurFenetre()-MenuWidth +150,hauteurFenetre() - 270),string4, 2);
				whenHoverUI(buttons, nButtons, sliders, nSliders, new2Dcoord(abscisseSouris(),ordonneeSouris()));
				updateText(&texts[0], new2Dcoord(largeurFenetre() - MenuWidth + 20, hauteurFenetre() - 50));
				updateText(&texts[1], new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 80));
				updateSlider(&sliders[0],new2Dcoord(largeurFenetre() - MenuWidth + 150,hauteurFenetre() - 400));
				updateButton(&buttons[0], (new2Dcoord(largeurFenetre() - MenuWidth + 150,hauteurFenetre() - 760)));
				updateButton(&buttons[1], (new2Dcoord(largeurFenetre() - MenuWidth + 90,hauteurFenetre() - 700)));
				updateButton(&buttons[2], (new2Dcoord(largeurFenetre() - MenuWidth + 200,hauteurFenetre() - 700)));

			}
			rafraichisFenetre();
			break;
		 
		case Affichage:
			effaceFenetre (0, 0, 0);
			//Affichage des cellules, en se basant sur les données de transformation de "ZOOM" et "Drag&Snap"
			for (int y = DeltaY; y < (HcellCap + (1 + DeltaY)); y++){
				for (int x = DeltaX; x < (WcellCap + (1 + DeltaX)); x++){
					int LBCx = x * (CellSize + CellInBetween) + CellInBetween - (DeltaX * (CellSize + CellInBetween));
					int LBCy = (y + 1) * (CellSize + CellInBetween) - (DeltaY * (CellSize + CellInBetween));
					int RTCx = (x + 1) * (CellSize + CellInBetween) - (DeltaX * (CellSize + CellInBetween));
					int RTCy = y * (CellSize + CellInBetween) + CellInBetween - (DeltaY * (CellSize + CellInBetween));
					CellData[y][x] == 0 ? couleurCourante(20, 20, 20) : couleurCourante(255, 255, 255);
					if(CellData[y][x] || pause) rectangle(LBCx, LBCy, RTCx, RTCy);
				}
			}
			couleurCourante(28, 28, 28);
			if(MenuStatus){
				rectangle(largeurFenetre()-MenuWidth,hauteurFenetre(),largeurFenetre(),0);
				ecrisImage(largeurFenetre()-MenuWidth, hauteurFenetre()-210, header->largeurImage, header->hauteurImage, header->donneesRGB);
				printUI(buttons, nButtons, sliders, nSliders, texts, nTexts);
			}
			//Menu
			break;

		case BoutonSouris:
			; //Aproximation de la position de la souris sur la grille
			float fx = abscisseSouris() / (CellSize + CellInBetween);
			float fy = ordonneeSouris() / (CellSize + CellInBetween);

			if (etatBoutonSouris() == GaucheAppuye){
				//Indentification de la ceullule cible
				int Sx = floorf(fx) + DeltaX;
				int Sy = floorf(fy) + DeltaY;
				//Safe check pour les coordonées en dehors de la grille et inversion de l'état.
				if ((Sx < DataSizeX) && (Sy < DataSizeY) && (abscisseSouris() < largeurFenetre() - (MenuStatus ? MenuWidth : 0)) && (ordonneeSouris() < hauteurFenetre()))
					if (((Sx) < DataSizeX) && ((Sy) < DataSizeY) && ((Sx) >= 0) && ((Sy) >= 0)) CellData[Sy][Sx] = !CellData[Sy][Sx];
			}

			//Zoom : IN & OUT (ScrollUp et ScrollDown addons pour gfxlib)
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

			//Drag&Snap : Traitement de la position du curseur si le clic droit et maintenu.
			if(etatBoutonSouris() == DroiteAppuye){
				XDRC = abscisseSouris() / (CellSize + CellInBetween);
				YDRC = ordonneeSouris() / (CellSize + CellInBetween);
				RCD = true;
			}

			//Drag&Snap : Relachement du clic
			if(etatBoutonSouris() == DroiteRelache) RCD = false;


			if (etatBoutonSouris() == GaucheAppuye){
				switch (whenClickedUI(buttons,nButtons,sliders, nSliders, new2Dcoord(abscisseSouris(),ordonneeSouris()))){
					case RESET :
						gen=0;
						iniCellData(&CellData, DataSizeX, DataSizeY);
						break;
					case Leave :
						freeCellData(&CellData,DataSizeX, DataSizeY);
						exit(EXIT_SUCCESS);
						break;
				}
			}

			if(etatBoutonSouris() == GaucheRelache && whenReleasedUI(buttons,nButtons,sliders,nSliders) == TogglePause) pause = !pause;
			//Zoom : Calcul du déplacement sur la grille
			if(NeedScrollUpdate){
				HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
				DeltaX += floorf(fx) - floorf(abscisseSouris() / (CellSize + CellInBetween));
				DeltaY += floorf(fy) - floorf(ordonneeSouris() / (CellSize + CellInBetween));
				if(DeltaX < 0) DeltaX = 0;
				if(DeltaX + WcellCap + 1 >= DataSizeX) DeltaX = DataSizeX - WcellCap - 1;
				if(DeltaY < 0) DeltaY = 0;
				if(DeltaY + HcellCap + 1 >= DataSizeY) DeltaY = DataSizeY - HcellCap - 1;
			}

			whenHoverUI(buttons, nButtons,sliders, nSliders, new2Dcoord(abscisseSouris(),ordonneeSouris()));
			rafraichisFenetre();
			break;

		case Souris:
			//Drag&Snap quand le clic droit est maintenu
			if(RCD){
				DeltaX += floorf(XDRC) - floorf(abscisseSouris() / (CellSize + CellInBetween));
				DeltaY += floorf(YDRC) - floorf(ordonneeSouris() / (CellSize + CellInBetween));
				XDRC = abscisseSouris() / (CellSize + CellInBetween);
				YDRC = ordonneeSouris() / (CellSize + CellInBetween);
				if(DeltaX < 0) DeltaX = 0;
				if(DeltaX + WcellCap + 1 >= DataSizeX) DeltaX = DataSizeX - WcellCap - 1;
				if(DeltaY < 0) DeltaY = 0;
				if(DeltaY + HcellCap + 1 >= DataSizeY) DeltaY = DataSizeY - HcellCap - 1;
			}
			break;
		case Clavier:
			//Système Start/Stop (initialement stop)
			if(caractereClavier() == 32){
				pause = !pause;
				buttons[1].TogggleStatus = pause;
				buttons[1].state = buttons[1].TogggleStatus ? Clicked : Idle;
			}
			break;
		case Redimensionnement:
			//Mise à jour de la fenêtre
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
			rafraichisFenetre();
			break;
	}
}

//Allocation dynamique et initialisation à 0 de la matrice
void iniCellData(int ***tab, int W, int H){
	*tab = (int**) malloc(sizeof(int*)*H);
	if(*tab == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<H; y++){
		(*tab)[y] = (int*) malloc(sizeof(int)*W);
		if((*tab)[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 2:%d)", y);
			for(int Y = 0; Y<y; Y++) free((*tab)[Y]);
			free(*tab);
			exit(EXIT_FAILURE);
		}
	}
	for(int x = 0; x<W; x++) for(int y = 0; y<H; y++) (*tab)[y][x] = 0;
}

//Libération de la mémoire
void freeCellData(int ***tab, int W, int H){
	for(int y = 0; y<H; y++) free((*tab)[y]);
	free(*tab);
}