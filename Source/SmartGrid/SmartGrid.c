#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <stdbool.h>
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include <time.h>
#include "../GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GfxLib/ESLib.h"
#include "../BlobEngine/BlobEngine.h"
#include "../Menu/menu.h"
#include "../Procedural/maze.h"
#include "../Procedural/rock.h"
//#include "../SmartUI/SmartUI.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1500
#define HauteurFenetre 1000
#define MATRIX_H 500
#define MATRIX_W 1000
#define LAB_SIZE 5

void gestionEvenement(EvenementGfx evenement);

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
	static cell **CellData = NULL;

	//BLOB
	static blob_blob *blobs = NULL;
	static int blobNumber = 0;
	static int selection = 'b';

	//SIM
	static simulation sim;

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
	static bool pauseCache = true;
	static int MenuWidth = 290;
	static bool MenuStatus = true;
	static DonneesImageRGB *header = NULL;
	static button *buttons = NULL;
	static slider *sliders = NULL;
	static text *texts = NULL;
	static button *buttons2 = NULL;
	static slider *sliders2 = NULL;
	static text *texts2 = NULL;
	static int nButtons = 0;
	static int nSliders = 0;
	static int nTexts = 0;
	static int nButtons2 = 0;
	static int nSliders2 = 0;
	static int nTexts2 = 0;
	static int vivant=0;
	static int gen=0;
	static int seuil=0;
	static int tick = 0;
	static int addType = 0;
	static bool menuType = true;
	
	//Mouse coords
	static float fx;
	static float fy;
	static int Sx;
	static int Sy;

	//Menu Tech
	static action menuOutput = menu_Main;
	static action OutputCache = menu_Main;

	//UPDATE MAIN DATA ET AFFICHAGE
	fx = abscisseSouris() / (CellSize + CellInBetween);
	fy = ordonneeSouris() / (CellSize + CellInBetween);
	Sx = floorf(fx) + DeltaX;
	Sy = floorf(fy) + DeltaY;
	HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
	WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
	if(DeltaX < 0) DeltaX = 0;
	if(DeltaX + WcellCap + 1 >= DataSizeX) DeltaX = DataSizeX - WcellCap - 1;
	if(DeltaY < 0) DeltaY = 0;
	if(DeltaY + HcellCap + 1 >= DataSizeY) DeltaY = DataSizeY - HcellCap - 1;
	while(HcellCap > DataSizeY || WcellCap > DataSizeX){
		CellSize++;
		HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
		WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
		DeltaX += floorf(fx) - floorf(abscisseSouris() / (CellSize + CellInBetween));
		DeltaY += floorf(fy) - floorf(ordonneeSouris() / (CellSize + CellInBetween));
		if(DeltaX < 0) DeltaX = 0;
		if(DeltaX + WcellCap + 1 >= DataSizeX) DeltaX = DataSizeX - WcellCap - 1;
		if(DeltaY < 0) DeltaY = 0;
		if(DeltaY + HcellCap + 1 >= DataSizeY) DeltaY = DataSizeY - HcellCap - 1;
	}
	// Laby
	static int **WallGrid = NULL;

	if(OutputCache != menuOutput){
		FreePointer(&buttons);
		FreePointer(&sliders);
		FreePointer(&texts);
		FreePointer(&buttons2);
		FreePointer(&sliders2);
		FreePointer(&texts2);
		if(blobs != NULL) freeBlobs(&blobs, &blobNumber, DataSizeY);
		if(CellData != NULL) freeCellData(&CellData, DataSizeX, DataSizeY);
		if(WallGrid != NULL) freeGridData(&WallGrid, DataSizeX, DataSizeY);
		evenement = Initialisation;
		OutputCache = menuOutput;
	}

	if(menuOutput == menu_Main){
		mainMenu(evenement, &menuOutput, &DataSizeX, &DataSizeY);
	}else{
		switch (evenement){
			case Initialisation:
				srand(time(NULL));
				switch(menuOutput){
					case menu_Laby :
						DataSizeX = 395;
						DataSizeY = 395;
						iniCellData(&CellData, DataSizeX, DataSizeY);
						iniGridData(&WallGrid, DataSizeX, DataSizeY);
						mazeEngine(WallGrid, DataSizeX, DataSizeY, LAB_SIZE);
						sim.AtracFoodMultiplicator = 1;
						sim.detectionRadius = 3;
						sim.OscilInfluence = 0.3;
						sim.ramificationRarity = 15;
						sim.RepMucusMultiplicator = 0.2;
						sim.RepSelfMultiplicator = 0.7;
						sim.RepWallMultiplicator = 0.7;
						sim.AtracEmptyMultiplicator = 0.5;
						break;
					case menu_Env :
						DataSizeX = 600;
						DataSizeY = 400;
						iniCellData(&CellData, DataSizeX, DataSizeY);
						iniGridData(&WallGrid, DataSizeX, DataSizeY);
						RockPanel(120, WallGrid, DataSizeX, DataSizeY);
						sim.AtracFoodMultiplicator = 1;
						sim.detectionRadius = 4;
						sim.OscilInfluence = 0.15;
						sim.ramificationRarity = 20;
						sim.RepMucusMultiplicator = 0.2;
						sim.RepSelfMultiplicator = 0.4;
						sim.RepWallMultiplicator = 0.7;
						sim.AtracEmptyMultiplicator = 0.3;
						break;
					case menu_Void :
						DataSizeX = 1000;
						DataSizeY = 500;
						iniGridData(&WallGrid, DataSizeX, DataSizeY);
						iniCellData(&CellData, DataSizeX, DataSizeY);
						sim.AtracFoodMultiplicator = 1;
						sim.detectionRadius = 4;
						sim.OscilInfluence = 0.15;
						sim.ramificationRarity = 20;
						sim.RepMucusMultiplicator = 0.2;
						sim.RepSelfMultiplicator = 0.4;
						sim.RepWallMultiplicator = 0.7;
						sim.AtracEmptyMultiplicator = 0.3;
						break;
					case menu_Sandbox :
						DataSizeX = 395;
						DataSizeY = 395;
						int **EnvData = NULL;
						iniGridData(&WallGrid, DataSizeX, DataSizeY);
						iniGridData(&EnvData, DataSizeX, DataSizeY);
						iniCellData(&CellData, DataSizeX, DataSizeY);
						mazeEngine(WallGrid, DataSizeX, DataSizeY, LAB_SIZE);
						RockPanel(120, EnvData, DataSizeX, DataSizeY);
						for(int x = 0; x < DataSizeX; x++) for(int y = 0; y < DataSizeY; y++) if(EnvData[y][x]) WallGrid[y][x] = 0;
						sim.AtracFoodMultiplicator = 1;
						sim.detectionRadius = 4;
						sim.OscilInfluence = 0.15;
						sim.ramificationRarity = 20;
						sim.RepMucusMultiplicator = 0.2;
						sim.RepSelfMultiplicator = 0.4;
						sim.RepWallMultiplicator = 0.7;
						sim.AtracEmptyMultiplicator = 0.3;
						break;
				}
				if(menuOutput != menu_Void) for(int x = 0; x < DataSizeX; x++) for(int y = 0; y < DataSizeY; y++) if(WallGrid[y][x]) CellData[y][x] = newCell(cell_block, 0, 0, 0);
				DeltaX = DataSizeX/4;
				DeltaY = DataSizeY/4;
				if(blobs != NULL) free(blobs);
				blobs = (blob_blob*) malloc(sizeof(blob_blob));
				//MENU
				iniContextMenu(&header, &nTexts, &texts, &nSliders, &sliders, &nButtons, &buttons, &nTexts2, &texts2, &nButtons2, &buttons2, &nSliders2, &sliders2, MenuWidth, sim);
				demandeTemporisation(1);
			break;
			
			case Temporisation: ;
				//Update cell capacity
				HcellCap = (hauteurFenetre() - CellInBetween) / (CellSize + CellInBetween);
				WcellCap = (largeurFenetre() - CellInBetween - (MenuStatus ? MenuWidth : 0)) / (CellSize + CellInBetween);
				if(addType == 2 && etatBoutonSouris() == GaucheAppuye)
							for (int y = 0; y < DataSizeY; y++)
								for (int x = 0; x < DataSizeX; x++)
									if(sqrt(pow(Sx - x, 2)+pow(Sy - y, 2)) < 3)
										CellData[y][x] = newCell(cell_block, 0, -1, -1);

				//>>>Gestion de la simulation et APPEL<<<
				//==========================================================================================================================
				seuil = 1 / ((float) (sliders2->value + 0.1) / (float) sliders2->max);
				if(!pause){
					tick++;
					if(tick>=seuil) tick = 0;
					if(tick==0){
						for(int i = 0; i < blobNumber; i++) blobNewRound(CellData, DataSizeX, DataSizeY, &blobs[i], &blobNumber, sim);
						gen++;
					}
				}
				//==========================================================================================================================

				//Menu
				if(MenuStatus==true && MenuWidth<290) MenuWidth+=50;
				else if (MenuStatus==false && MenuWidth>0) MenuWidth-=50;
				vivant = 0;
				for(int x = 0; x < DataSizeX; x++) for(int y = 0; y <DataSizeY; y++) if(CellData[y][x].type == cell_blob) vivant++;
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
						//COLOR SELECTION
						int colorGrad = CellData[y][x].blob_bm > 230 ? 230 : CellData[y][x].blob_bm;
						CellData[y][x].blob_bm < 0 ? couleurCourante(20, 20, 20) : couleurCourante(colorGrad + 20, colorGrad + 20, 20);
						if(CellData[y][x].food_amount>0) couleurCourante(colorGrad + 20, colorGrad + 20, 250 - colorGrad);
						if(CellData[y][x].type == cell_food) couleurCourante(20, 20, 255);
						if(CellData[y][x].type == cell_block) couleurCourante(240, 240, 240);
						if(CellData[y][x].type == cell_mucus){
							int CG = CellData[y][x].mucus_amount < 100 ? CellData[y][x].mucus_amount : 100;
							couleurCourante(20+CG, 20+CG, 20+CG);
						}
						//PRINTING
						if(CellData[y][x].type != cell_empty || pause) rectangle(LBCx, LBCy, RTCx, RTCy);
					}
				}
				//Menu
				printContextMenu(buttons, sliders, texts, buttons2, sliders2, texts2, MenuWidth, nSliders, nButtons, nTexts, nSliders2, nButtons2, nTexts2, vivant, Sx, Sy, gen, &sim, menuType, header);
				break;

			case BoutonSouris:
				; //Aproximation de la position de la souris sur la grille
				if (etatBoutonSouris() == GaucheAppuye){
					//Safe check pour les coordonées en dehors de la grille et inversion de l'état.
					if(((largeurFenetre() - MenuWidth -70< abscisseSouris()) &&	((hauteurFenetre() - 70)<ordonneeSouris())));
					else if ((Sx < DataSizeX) && (Sy < DataSizeY) && (abscisseSouris() < largeurFenetre() - (MenuStatus ? MenuWidth : 0)) && (ordonneeSouris() < hauteurFenetre()))
					if (((Sx) < DataSizeX) && ((Sy) < DataSizeY) && ((Sx) >= 0) && ((Sy) >= 0)){
						if(addType == 1 && getNeyboors(CellData, DataSizeX, DataSizeY,new2Dcoord(Sx,Sy),cell_block,3)<16 && CellData[Sy][Sx].type == cell_empty){
							blobNumber++;
							blobs = (blob_blob*) realloc(blobs, sizeof(blob_blob)*blobNumber);
							blobs[blobNumber-1] = newBlob(CellData, DataSizeX, DataSizeY, new2Dcoord(Sx, Sy), sim);
						}
						if(addType == 3)
							for (int y = 0; y < DataSizeY; y++)
								for (int x = 0; x < DataSizeX; x++)
									if(sqrt(pow(Sx - x, 2)+pow(Sy - y, 2)) < 5 && CellData[y][x].type == cell_empty)
										CellData[y][x] = newCell(cell_food, 200, -1, -1);
					}
				}

				//Zoom : IN & OUT (ScrollUp et ScrollDown addons pour gfxlib)
				bool NeedScrollUpdate = false;
				if (etatBoutonSouris() == ScrollUp && CellSize < 50 && !RCD){
					CellSize *= 1.4;
					if(CellSize == 3) CellSize++;
					CellInBetween = 1;
					NeedScrollUpdate = true;
				}
				if (etatBoutonSouris() == ScrollDown && CellSize >= 1 && !RCD){
					CellSize *= 0.6;
					if(CellSize < 3){
						CellSize = 3;
						CellInBetween = 0;
					}
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
					if (menuType == false){
						switch (whenClickedUI(buttons, nButtons, sliders, nSliders, new2Dcoord(abscisseSouris(), ordonneeSouris()))){
							case RESET:
								gen = 0;
								iniCellData(&CellData, DataSizeX, DataSizeY);
								break;
							case Leave:
								freeCellData(&CellData, DataSizeX, DataSizeY);
								exit(EXIT_SUCCESS);
								break;
							case MENU:
								MenuStatus = !MenuStatus;
								break;
							case ChangeMenu:
								menuType = !menuType;
								break;
							case menu_Main:
								menuOutput = menu_Main;
								break;
						}
					}else{
						switch (whenClickedUI(buttons2, nButtons2, sliders2, nSliders2, new2Dcoord(abscisseSouris(), ordonneeSouris()))){
							case RESET:
								gen = 0;
								iniCellData(&CellData, DataSizeX, DataSizeY);
								blobs = (blob_blob*) realloc(blobs, sizeof(blob_blob));
								blobNumber = 0;
								for(int x = 0; x < DataSizeX; x++) for(int y = 0; y < DataSizeY; y++) if(WallGrid[y][x]) CellData[y][x] = newCell(cell_block, 0, 0, 0);
								break;
							case Leave:
								freeCellData(&CellData, DataSizeX, DataSizeY);
								exit(EXIT_SUCCESS);
								break;
							case MENU:
								MenuStatus = !MenuStatus;
								break;
							case ChangeMenu:
								menuType = !menuType;
								break;
							case menu_Main:
								menuOutput = menu_Main;
								break;
						}
					}
				}
				if (etatBoutonSouris() == GaucheRelache){
					if (menuType == false){
						switch (whenReleasedUI(buttons, nButtons, sliders, nSliders)){
							case TogglePause:
								pause = !pause;
								break;
						}
					}else{
						switch (whenReleasedUI(buttons2, nButtons2, sliders2, nSliders2)){
							case TogglePause:
								pause = !pause;
								break;
							case addType1:
								if (addType == 1) addType = 0;
								else addType = 1;
								buttons2[7].TogggleStatus = false;
								buttons2[8].TogggleStatus = false;
								break;
							case addType2:
								if (addType == 2) addType = 0;
								else addType = 2;
								buttons2[6].TogggleStatus = false;
								buttons2[8].TogggleStatus = false;
								break;
							case addType3:
								if (addType == 3) addType = 0;
								else addType = 3;
								buttons2[6].TogggleStatus = false;
								buttons2[7].TogggleStatus = false;
								break;
						}
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
				if (caractereClavier() == 32)
				{
					pause = !pause;
					buttons[1].TogggleStatus = pause;
					buttons[1].state = buttons[1].TogggleStatus ? Clicked : Idle;
					buttons2[1].TogggleStatus = pause;
					buttons2[1].state = buttons2[1].TogggleStatus ? Clicked : Idle;
				}
				if (caractereClavier() == 'b')
				{
					if (addType == 1)
					{
						addType = 0;
						buttons2[6].TogggleStatus = false;
						buttons2[6].state = Idle;
					}
					else
					{
						addType = 1;
						buttons2[6].TogggleStatus = true;
						buttons2[6].state = Clicked;
						buttons2[7].TogggleStatus = false;
						buttons2[7].state = Idle;
						buttons2[8].TogggleStatus = false;
						buttons2[8].state = Idle;
					}
				}
				else if (caractereClavier() == 'w')
				{
					if (addType == 2)
					{
						addType = 0;
						buttons2[7].TogggleStatus = false;
						buttons2[7].state = Idle;
					}
					else
					{
						addType = 2;
						buttons2[6].TogggleStatus = false;
						buttons2[6].state = Idle;
						buttons2[7].TogggleStatus = true;
						buttons2[7].state = Clicked;
						buttons2[8].TogggleStatus = false;
						buttons2[8].state = Idle;
					}
				}
				else if (caractereClavier() == 'f')
				{
					if (addType == 3)
					{
						addType = 0;
						buttons2[8].TogggleStatus = false;
						buttons2[8].state = Idle;
					}
					else
					{
						addType = 3;
						buttons2[6].TogggleStatus = false;
						buttons2[6].state = Idle;
						buttons2[7].TogggleStatus = false;
						buttons2[7].state = Idle;
						buttons2[8].TogggleStatus = true;
						buttons2[8].state = Clicked;
					}
				}
				break;
			case Redimensionnement:
				//Mise à jour de la fenêtre
				rafraichisFenetre();
				break;
		}
	}
}