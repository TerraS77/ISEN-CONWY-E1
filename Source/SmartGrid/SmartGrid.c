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

#include <time.h>

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1200
#define HauteurFenetre 800
#define MATRIX_H 500
#define MATRIX_W 1000

void gestionEvenement(EvenementGfx evenement);
void iniCellData(int ***tab, int DataSizeX, int DataSizeY);
void freeCellData(int ***tab, int W, int H);

void maze(int ***tab);
//void save(int **tab, int W, int H);
//void load(int **tab, int W, int H, int mode);

void iniColors(color ***tab, int W, int H);
void freeColors(color ***tab, int W, int H);
void save(int **tabCell, int W, int H, color **tabCol);
void load(int **tabCell, int W, int H, color **tabCol, int mode);
void initRandom(int **tabCell, int W, int H, color **tabCol);

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
	static bool MenuStatus = true;
	static DonneesImageRGB *header = NULL;
	static button *buttons = NULL;
	static slider *sliders = NULL;
	static text *texts = NULL;
	static int nButtons = 0;
	static int nSliders = 0;
	static int nTexts = 0;
	static unsigned long int generationNumber = 0;

	static int mode = 1;
	static float fx;
	static float fy;
	static int Sx;
	static int Sy;

	static int W_temp;
	static int H_temp;

	static color **Colors;


	switch (mode){
	case 0:
		switch (evenement){
		case Initialisation:
			iniCellData(&CellData, DataSizeX, DataSizeY);
			iniColors(&Colors, DataSizeX, DataSizeY);
			HcellCap = 70; //100
			WcellCap = 70; //100
			CellSize = 3;
			CellInBetween = 0;
			W_temp = WcellCap * (CellSize + CellInBetween);
			H_temp = HcellCap * (CellSize + CellInBetween);
			//load(CellData, 21, 21, mode);
			load(CellData, DataSizeX, DataSizeY, Colors, mode);

			color green = newColor(81,255,118);
			color yellow = newColor(255,250,54);
			color red = newColor(195,0,28);
			color grey = newColor(20, 20, 20);
			color dark = newColor(20, 20, 20);
			color background = newColor(255,250,242);
			color color_button = background;

			nButtons = 9;
			buttons = malloc(sizeof(button)*nButtons);
			buttons[0] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp,color_button, color_button, color_button, 
				newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 35, new2Dcoord(0,0),"", 1), 
				menu1, false, false);
			buttons[1] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp, color_button, color_button, color_button, 
				newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 35, new2Dcoord(0,0),"", 1), 
				menu2, false, false);
			buttons[2] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp, color_button, color_button, color_button, 
				newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 35, new2Dcoord(0,0),"", 1), 
				menu3, false, false);
			buttons[3] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp, color_button, color_button, color_button, 
				newText(newColor(255,255,255), newColor(255,255,255), newColor(255,255,255), 35, new2Dcoord(0,0),"", 1), 
				menu4, false, false);

			buttons[4] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(grey, grey, grey, 35, 
				new2Dcoord(largeurFenetre() * 1/3 + (W_temp)/2 - 6,  hauteurFenetre() * 0.55),"Simu. 1", 3), 
				menu1, false, false);
			buttons[5] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(grey, grey, grey, 35, 
				new2Dcoord(largeurFenetre() * 11/17 + (W_temp)/2 - 6,  hauteurFenetre() * 0.50),"Simu. 2", 3), 
				menu2, false, false);
			buttons[6] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(grey, grey, grey, 35, 
				new2Dcoord(largeurFenetre() * 1/3 + (W_temp)/2 - 6,  hauteurFenetre() * 0.22),"Simu. 3", 3), 
				menu3, false, false);
			buttons[7] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(grey, grey, grey, 35, 
				new2Dcoord(largeurFenetre() * 11/17 + (W_temp)/2 - 6,  hauteurFenetre() * 0.22),"Simu. 4", 3), 
				menu4, false, false);

			buttons[8] = newButton(
				new2Dcoord(largeurFenetre() * 0.5, hauteurFenetre() * 0.90), 
				W_temp, 40, background, background, background, 
				newText(red, red, red, 50, 
				new2Dcoord(largeurFenetre() * 0.5,  hauteurFenetre() * 0.90),"MENU", 5), 
				menu1, false, false);
			demandeTemporisation(30);
			break;

		case Temporisation:
			//Button grid
			updateButton(&buttons[0], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween));
			updateButton(&buttons[1], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween));
			updateButton(&buttons[2], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween));
			updateButton(&buttons[3], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween));

			//Simu. ...
			updateButton(&buttons[4], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween - H_temp/2 - buttons[4].height/2));
			updateButton(&buttons[5], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween - H_temp/2 - buttons[5].height/2));
			updateButton(&buttons[6], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween - H_temp/2 - buttons[6].height/2));
			updateButton(&buttons[7], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween - H_temp/2 - buttons[7].height/2));
			
			updateButton(&buttons[8], new2Dcoord(largeurFenetre() * 0.5, hauteurFenetre() * 0.90));
			rafraichisFenetre();
			break;
		
		case Affichage:
			effaceFenetre(255,250,242);
			printUI(buttons, nButtons, sliders, nSliders, texts, nTexts);
			for (int i = 0; i < 2; i++){
				for (int j = 0; j < 2; j++){
					for (int y = 0; y < HcellCap; y++){
						for (int x = 0; x < WcellCap; x++){
							int LBCx = largeurFenetre() * (1 + i)/3 - W_temp/2 + (x * (CellSize + CellInBetween) + CellInBetween - (CellSize + CellInBetween));
							int LBCy = hauteurFenetre() * (3 + j * 5)/12 - H_temp/2 + ((y + 1) * (CellSize + CellInBetween) - (CellSize + CellInBetween));
							int RTCx = largeurFenetre() * (1 + i)/3  - W_temp/2 + ((x + 1) * (CellSize + CellInBetween) - (CellSize + CellInBetween));
							int RTCy = hauteurFenetre() * (3 + j * 5)/12 - H_temp/2 + (y * (CellSize + CellInBetween) + CellInBetween - (CellSize + CellInBetween));
							CellData[y][x] == 0 ? couleurCourante(20, 20, 20) : couleurCourante(Colors[y][x].R, Colors[y][x].G, Colors[y][x].B);
							if(CellData[y][x] || pause) rectangle(LBCx, LBCy, RTCx, RTCy);
						}
					}
				}
			}
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye){
				switch (whenClickedUI(buttons, 9, sliders, 0, new2Dcoord(abscisseSouris(), ordonneeSouris()))){
				case menu1:
					printf("Menu1\n");
					break;
				case menu2:
					printf("Menu2\n");
					break;
				case menu3:
					printf("Menu3\n");
					break;
				case menu4:
					printf("Menu4\n");
					break;
				
				default:
					break;
				}
			}
			rafraichisFenetre();
			break;

		case Souris:
			break;

		case Clavier:
			switch(caractereClavier()){
			case 'q':
			case 'Q':
				freeCellData(&CellData, DataSizeX, DataSizeY);
				freeColors(&Colors, DataSizeX, DataSizeY);
				termineBoucleEvenements();
				break;
			default:
				break;
			}
			break;

		case Redimensionnement:
			break;
		}
		break;
	
	case 1: //Conway
		switch (evenement){
		case Initialisation:
			//Menu
			header = lisBMPRGB("#Ressources/header.bmp");
			color RGBIdle = newColor(45,45,48);
			color RGBHover = newColor(55,55,58);
			color RGBClick = newColor(8,86,123);
			color RGBwhite = newColor(255,255,255);
			coord2D Origin = new2Dcoord(largeurFenetre() - MenuWidth, hauteurFenetre() - 80);

			nTexts = 2;
			texts = malloc(sizeof(text)*nTexts);
			texts[0] = newText(RGBwhite, RGBwhite, RGBwhite, 50, new2Dcoord(largeurFenetre() - MenuWidth + 20, hauteurFenetre() - 50), "CONWAY'S", 4);
			texts[1] = newText(RGBwhite, RGBwhite, RGBwhite, 25, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 80), "Game of Life", 2);

			//Data
			iniCellData(&CellData, DataSizeX, DataSizeY);
			iniColors(&Colors, DataSizeX, DataSizeY);
			DeltaX = DataSizeX/4;
			DeltaY = DataSizeY/4;
			demandeTemporisation(30);
			break;

		case Temporisation:
			//Data process
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
			if(HcellCap > DataSizeY || WcellCap > DataSizeX){
				printf("ERREUR CRITIQUE : AFFICHAGE SUR L'AXE %s COMPROMIS\n", HcellCap > DataSizeY ? "Y" : "X");
				exit(EXIT_FAILURE);
			}
			if(!pause) conwayTransform(CellData, DataSizeX, DataSizeY);

			//Menu
			whenHoverUI(buttons, nButtons, sliders, nSliders, new2Dcoord(abscisseSouris(),ordonneeSouris()));
			if(MenuStatus){
				updateText(&texts[0], new2Dcoord(largeurFenetre() - MenuWidth + 20, hauteurFenetre() - 50));
				updateText(&texts[1], new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 80));
			}
			rafraichisFenetre();
			break;
		
		case Affichage:
			effaceFenetre (0, 0, 0);
			//Affichage des cellules, en se basant sur les données de transformation de "ZOOM" et "Drag&Snap"
			for (int y = DeltaY; y < (HcellCap + 1 + DeltaY); y++){
				for (int x = DeltaX; x < (WcellCap + 1 + DeltaX); x++){
					int LBCx = x * (CellSize + CellInBetween) + CellInBetween - (DeltaX * (CellSize + CellInBetween));
					int LBCy = (y + 1) * (CellSize + CellInBetween) - (DeltaY * (CellSize + CellInBetween));
					int RTCx = (x + 1) * (CellSize + CellInBetween) - (DeltaX * (CellSize + CellInBetween));
					int RTCy = y * (CellSize + CellInBetween) + CellInBetween - (DeltaY * (CellSize + CellInBetween));
					CellData[y][x] == 0 ? couleurCourante(20, 20, 20) : couleurCourante(Colors[y][x].R, Colors[y][x].G, Colors[y][x].B);
					if(CellData[y][x] || pause) rectangle(LBCx, LBCy, RTCx, RTCy);
				}
			}
			couleurCourante(28, 28, 28);
			if(MenuStatus){
				rectangle(largeurFenetre()-MenuWidth,hauteurFenetre(),largeurFenetre(),0);
				ecrisImage(largeurFenetre()-MenuWidth, hauteurFenetre()-210, header->largeurImage, header->hauteurImage, header->donneesRGB);
				printUI(buttons, nButtons, sliders, nSliders, texts, nTexts);
			}
			break;

		case BoutonSouris:
			//Aproximation de la position de la souris sur la grille
			fx = abscisseSouris() / (CellSize + CellInBetween);
			fy = ordonneeSouris() / (CellSize + CellInBetween);

			if (etatBoutonSouris() == GaucheAppuye){
				//Indentification de la ceullule cible
				Sx = floorf(fx) + DeltaX;
				Sy = floorf(fy) + DeltaY;
				//Safe check pour les coordonées en dehors de la grille et inversion de l'état.
				if ((Sx < DataSizeX) && (Sy < DataSizeY) && (abscisseSouris() < largeurFenetre() - (MenuStatus ? MenuWidth : 0)) && (ordonneeSouris() < hauteurFenetre()))
					if (((Sx) < DataSizeX) && ((Sy) < DataSizeY) && ((Sx) >= 0) && ((Sy) >= 0)) {
					CellData[Sy][Sx] = !CellData[Sy][Sx];
					printf("%d\n", CellData[Sy][Sx]);
					if (CellData[Sy][Sy] != 1){
						Colors[Sy][Sx].R = 255;
						Colors[Sy][Sx].G = 255;
						Colors[Sy][Sx].B = 255;
					}
					else {
						Colors[Sy][Sx].R = 20;
						Colors[Sy][Sx].G = 20;
						Colors[Sy][Sx].B = 20;
					}
					printf("%d:%d:%d\n", Colors[Sy][Sx].R, Colors[Sy][Sx].G, Colors[Sy][Sx].B);
				}
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

			//Zoom : Calcul du déplacement sur la grille
			if(NeedScrollUpdate){
				HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
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
			//Drag&Snap quand le clic droit est maintenu
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
			switch (caractereClavier()){
			case 32:
				pause = !pause;
				break;

			case 'a':
			case 'A':
				maze(&CellData);
				break;

			case 'l':
			case 'L':
				load(CellData, DataSizeX, DataSizeY, Colors, mode);
				break;

			case 'q':
			case 'Q':
				freeCellData(&CellData, DataSizeX, DataSizeY);
				freeColors(&Colors, DataSizeX, DataSizeY);
				termineBoucleEvenements();
				break;

			case 'r':
			case 'R':
				freeCellData(&CellData, DataSizeX, DataSizeY);
				freeColors(&Colors, DataSizeX, DataSizeY);
				iniCellData(&CellData, DataSizeX, DataSizeY);
				iniColors(&Colors, DataSizeX, DataSizeY);
				break;

			case 's':
			case 'S':
				save(CellData, 100, 100, Colors);
				break;
			case 'w':
			case 'W':
				initRandom(CellData, DataSizeX, DataSizeY, Colors);
				break;
			}
			break;

		case Redimensionnement:
			//Mise à jour de la fenêtre
			HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
			WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
			rafraichisFenetre();
			break;
		}
		break;
		
	default:
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
void freeColors(color ***tab, int W, int H){
	for(int y = 0; y<H; y++) free((*tab)[y]);
	free(*tab);
}

void maze(int ***tab){
	int taille = 499;
	for(int  i = 0; i < taille; i++){
		for (int j = 0; j < taille; j++){
			//if(i == 0 || i == taille -1 || j == 0 || j == taille - 1) (*tab)[i][j] = 1;
			if(i % 2 != 1 || j == 0 || j == taille - 1 || j % 2 == 0) (*tab)[i][j] = 1;
			else (*tab)[i][j] = 0;
		}
	}
	(*tab)[taille - 2][0] = 0;
	(*tab)[1][taille - 1] = 0;
}


//Allocation dynamique et initialisation à 0 de la matrice
void iniColors(color ***tab, int W, int H){
	*tab = (color**) malloc(sizeof(color*)*H);
	if(*tab == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<H; y++){
		(*tab)[y] = (color*) malloc(sizeof(color)*W);
		if((*tab)[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniCellData 2:%d)", y);
			for(int Y = 0; Y<y; Y++) free((*tab)[Y]);
			free(*tab);
			exit(EXIT_FAILURE);
		}
	}
	for(int x = 0; x<W; x++) for(int y = 0; y<H; y++) (*tab)[y][x] = newColor(0, 0, 0);
}

void save(int **tabCell, int W, int H, color **tabCol){
	FILE* fic = NULL;
	char name[20];
    char source[40] = "./#Ressources/";

    printf("SAVE ENGINE - Nom de votre fichier : ");
    scanf("%s", name);
    strcat(source,name);
    strcat(source,".cnw");
	fic = fopen(source, "w");

	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if(tabCell[i][j] == 1){
				printf("{%d;%d}%d/%d/%d;\n", i, j, tabCol[i][j].R, tabCol[i][j].G, tabCol[i][j].B);
				fprintf(fic, "{%d;%d}%d/%d/%d;\n", i, j, tabCol[i][j].R, tabCol[i][j].G, tabCol[i][j].B);
			}
		}
	}

	fclose(fic);
	printf("Le fichier %s a ete enregistre ! \n", name);
}

//Ouvre la sauvegarde de la matrice
void load(int **tabCell, int W, int H, color **tabCol, int mode){
	FILE* fic = NULL;
	char name[20];
    char source[40] = "./#Ressources/";
	int i_temp = 0;
	int j_temp = 0;
	int R = 0;
	int V = 0;
	int B = 0;

	if(mode == 1){
		system("clear");
		system("ls ./#Ressources/*.cnw --format=single-column | cut -c 15- ");
		
		printf("LOAD ENGINE - Nom de votre fichier : ");
		scanf("%s", name);
		strcat(source, name);
	}
	else strcat(source, "baptiste2");

	strcat(source,".cnw");
	fic = fopen(source, "r");

    const size_t line_size = 300;
    char* line = malloc(line_size);
    while (fgets(line, line_size, fic) != NULL) {
        sscanf(line, "{%d;%d}%d/%d/%d;\n", &i_temp, &j_temp, &R, &V, &B);
		tabCol[i_temp][j_temp].R = R;
		tabCol[i_temp][j_temp].G = V;
		tabCol[i_temp][j_temp].B = B;
		tabCell[i_temp][j_temp] = 1;
    }

	free(line);
	fclose(fic);
	if(mode == 1) printf("Le fichier %s a ete charge ! \n", name);
}

//Initialise en mode Random
void initRandom(int **tabCell, int W, int H, color **tabCol){
	srand(time(NULL));
	int r = rand();
	for(int x = 0; x<W; x++) {
		for(int y = 0; y<H; y++) {
			r = rand() % 2;
			if (r == 1) {
				tabCell[y][x] = 1;
				tabCol[y][x].R = rand() % 255;
				tabCol[y][x].G = rand() % 255;
				tabCol[y][x].B = rand() % 255;
				//printf("Etat : %d\tCouleur : %d/%d/%d\n", tabCell[y][x], tabCol[y][x].R, tabCol[y][x].G, tabCol[y][x].B);
			}
		}
	}
}