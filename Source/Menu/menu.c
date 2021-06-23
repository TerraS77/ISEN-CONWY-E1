#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../GfxLib/GfxLib.h"
#include "../GfxLib/BmpLib.h"
#include "../SmartUI/SmartUI.h"
#include "../BlobEngine/BlobEngine.h"
#include "menu.h"
#define MM_H 500
#define MM_W 1000

/*
.___  ___.  _______ .__   __.  __    __  
|   \/   | |   ____||  \ |  | |  |  |  | 
|  \  /  | |  |__   |   \|  | |  |  |  | 
|  |\/|  | |   __|  |  . `  | |  |  |  | 
|  |  |  | |  |____ |  |\   | |  `--'  | 
|__|  |__| |_______||__| \__|  \______/                                 
*/


// Initialise le menu de contrôle du Blob
void iniContextMenu(DonneesImageRGB **header, int *nTexts, text **texts, int *nSliders, slider **sliders, int *nButtons, button **buttons, int *nTexts2, text **texts2, int *nButtons2, button **buttons2, int *nSliders2, slider **sliders2, int MenuWidth, simulation sim)
{
	//Menu
	*header = lisBMPRGB("#Ressources/header.bmp");
	color RGBIdle = newColor(45, 45, 48);
	color RGBHover = newColor(55, 55, 58);
	color RGBClick = newColor(8, 86, 123);
	color RGBwhite = newColor(255, 255, 255);
	coord2D Origin = new2Dcoord(largeurFenetre() - MenuWidth, hauteurFenetre() - 80);

	// Menu "SETTINGS"
	//TXT
	*nTexts = 13;
	*texts = (text *)malloc(sizeof(text) * (*nTexts));
	(*texts)[0] = newText(RGBwhite, RGBwhite, RGBwhite, 45, Origin, "BLOB", 4);
	(*texts)[1] = newText(RGBwhite, RGBwhite, RGBwhite, 30, Origin, "ENGINE", 2);
	(*texts)[2] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "Vivant: 0", 2);
	(*texts)[3] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "Generation : 0", 2);
	(*texts)[4] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "X:", 2);
	(*texts)[5] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "Y:", 2);
	//TXT Slider
	(*texts)[6] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S1 :", 2);
	(*texts)[7] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S2 :", 2);
	(*texts)[8] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S2 :", 2);
	(*texts)[9] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S2 :", 2);
	(*texts)[10] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S2 :", 2);
	(*texts)[11] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S2 :", 2);
	(*texts)[12] = newText(RGBwhite, RGBwhite, RGBwhite, 20, Origin, "S7 :", 2);
	//SLIDER
	*nSliders = 7;
	*sliders = (slider *)malloc(sizeof(slider) * (*nSliders));
	(*sliders)[0] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 325), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[0].value = sim.ramificationRarity;
	(*sliders)[1] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 400), 200, 1, 20, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[1].value = sim.detectionRadius;
	(*sliders)[2] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 475), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[2].value = (*sliders)[2].max * sim.OscilInfluence;
	(*sliders)[3] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 550), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[3].value = (*sliders)[3].max * sim.AtracFoodMultiplicator;
	(*sliders)[4] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 625), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[4].value = (*sliders)[4].max * sim.RepMucusMultiplicator;
	(*sliders)[5] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 700), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[5].value = (*sliders)[5].max * sim.RepWallMultiplicator;
	(*sliders)[6] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 775), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders)[6].value = (*sliders)[6].max * sim.RepSelfMultiplicator;
	//BUTTONS
	*nButtons = 4;
	*buttons = (button *)malloc(sizeof(button) * (*nButtons));
	(*buttons)[2] = newButton(new2Dcoord(largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45), 45, 50, newColor(15, 15, 15), newColor(15, 15, 15), newColor(15, 15, 15), newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "", 2), MENU, false, false);
	(*buttons)[0] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 118), 100, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Simuler", 2), ChangeMenu, false, false);
	(*buttons)[1] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 200, hauteurFenetre() - 118), 100, 50, RGBClick, RGBClick, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Settings", 2), none, false, false);
	(*buttons)[3] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 43, hauteurFenetre() - 123), 45, 50, newColor(28, 28, 28), newColor(28, 28, 28), newColor(28, 28, 28), newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "", 2), menu_Main, false, false);

	// Menu "SIMULER"
	//BUTTONS
	*nButtons2 = 10;
	*buttons2 = (button *)malloc(sizeof(button) * (*nButtons2));
	(*buttons2)[0] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 710), 150, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Quitter", 2), Leave, false, false);
	(*buttons2)[1] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 90, hauteurFenetre() - 650), 100, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Pause", 2), TogglePause, true, true);
	(*buttons2)[2] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 200, hauteurFenetre() - 650), 100, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Reset", 2), RESET, false, false);
	(*buttons2)[3] = newButton(new2Dcoord(largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45), 45, 50, newColor(15, 15, 15), newColor(15, 15, 15), newColor(15, 15, 15), newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "", 2), MENU, false, false);
	(*buttons2)[4] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 90, hauteurFenetre() - 118), 100, 50, RGBClick, RGBClick, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Simuler", 2), none, false, false);
	(*buttons2)[5] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 200, hauteurFenetre() - 118), 100, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "Settings", 2), ChangeMenu, false, false);
	(*buttons2)[6] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 300), 80, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "B", 2), addType1, true, false);
	(*buttons2)[7] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 375), 80, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "W", 2), addType2, true, false);
	(*buttons2)[8] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 450), 80, 50, RGBIdle, RGBHover, RGBClick, newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "F", 2), addType3, true, false);
	(*buttons2)[9] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 43, hauteurFenetre() - 123), 45, 50, newColor(28, 28, 28), newColor(28, 28, 28), newColor(28, 28, 28), newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "", 2), menu_Main, false, false);
	//SLIDE
	*nSliders2 = 1;
	*sliders2 = (slider *)malloc(sizeof(slider));
	(*sliders2)[0] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 325), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders2)[0].value = 100;
	//TXT
	*nTexts2 = 3;
	*texts2 = (text *)malloc(sizeof(text) * (*nTexts2));
	(*texts2)[0] = newText(RGBwhite, RGBwhite, RGBwhite, 45, Origin, "BLOB", 4);
	(*texts2)[1] = newText(RGBwhite, RGBwhite, RGBwhite, 30, Origin, "ENGINE", 2);
	(*texts2)[2] = newText(RGBwhite, RGBwhite, RGBwhite, 25, Origin, "Vitesse : ", 2);
}

// Afficher le menu de contrôle
void printContextMenu(button *buttons, slider *sliders, text *texts, button *buttons2, slider *sliders2, text *texts2, int MenuWidth, int nSliders, int nButtons, int nTexts, int nSliders2, int nButtons2, int nTexts2, int vivant, int Sx2, int Sy2, int gen, simulation *sim, bool menuType, DonneesImageRGB *header)
{
	if (MenuWidth > 0)
	{
		// Return to MENU
		updateButton(&buttons2[9], (new2Dcoord(largeurFenetre() - MenuWidth + 33, hauteurFenetre() - 123))); // Return to menu
		updateButton(&buttons[3], (new2Dcoord(largeurFenetre() - MenuWidth + 33, hauteurFenetre() - 123))); // Return to menu

		couleurCourante(28, 28, 28);
		rectangle(largeurFenetre() - MenuWidth, hauteurFenetre(), largeurFenetre(), 0);

		// Cellules vivantes
		vivant = 0;
		char string[64];
		sprintf(string, "Cellules: %d", vivant);
		texts[2] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 180), string, 2);
		// Génération
		char string2[64];
		sprintf(string2, "Generation: %d", gen);
		texts[3] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 210), string2, 2);
		// X
		char string3[25];
		sprintf(string3, "X: %d", Sx2);
		texts[4] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 240), string3, 2);
		// Y
		char string4[25];
		sprintf(string4, "Y: %d", Sy2);
		texts[5] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 240), string4, 2);
		// Vitesse
		char string5[25];
		sprintf(string5, "Vitesse : %.2f", (float)(((float)sliders2->value / 100)));
		texts2[2] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 200), string5, 2);
		// ramificationRarity
		char string8[25];
		sim->ramificationRarity = sliders[0].value + 5;
		sprintf(string8, "ramRarity : %d", sim->ramificationRarity);
		texts[6] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 280), string8, 2);
		// detectionRadius
		char string7[25];
		sim->detectionRadius = sliders[1].value;
		sprintf(string7, "detectionRadius : %d", sim->detectionRadius);
		texts[7] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 355), string7, 2);
		// Oscillation
		char string12[25];
		sim->OscilInfluence = (float)sliders[2].value / (float)sliders[2].max;
		sprintf(string12, "OscillationInf : %.2f", sim->OscilInfluence);
		texts[8] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 430), string12, 2);
		// AtracFood
		char string6[25];
		sim->AtracFoodMultiplicator = (float)sliders[3].value / (float)sliders[3].max;
		sprintf(string6, "attracFood : %.2f", sim->AtracFoodMultiplicator);
		texts[9] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 505), string6, 2);
		// RepMucus
		char string9[25];
		sim->RepMucusMultiplicator = (float)sliders[4].value / (float)sliders[4].max;
		sprintf(string9, "RepMucus : %.2f", sim->RepMucusMultiplicator);
		texts[10] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 580), string9, 2);
		// RepWall
		char string10[25];
		sim->RepWallMultiplicator = (float)sliders[5].value / (float)sliders[5].max;
		sprintf(string10, "RepWall : %.2f", sim->RepWallMultiplicator);
		texts[11] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 655), string10, 2);
		// RepSelf
		char string11[25];
		sim->RepSelfMultiplicator = (float)sliders[6].value / (float)sliders[6].max;
		sprintf(string11, "RepSelf : %.2f", sim->RepSelfMultiplicator);
		texts[12] = newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 20, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 730), string11, 2);

		// Menu "SETTINGS"
		whenHoverUI(buttons, nButtons, sliders, nSliders, new2Dcoord(abscisseSouris(), ordonneeSouris()));
		updateText(&texts[0], new2Dcoord(largeurFenetre() - MenuWidth + 50, hauteurFenetre() - 48));		 // Conway
		updateText(&texts[1], new2Dcoord(largeurFenetre() - MenuWidth + 130, hauteurFenetre() - 82));		 // Game of life
		updateSlider(&sliders[0], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 305));	 // ramificationRarity
		updateSlider(&sliders[1], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 380));	 // detectionRadius
		updateSlider(&sliders[2], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 455));	 // Oscillation
		updateSlider(&sliders[3], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 530));	 // AtracFood
		updateSlider(&sliders[4], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 605));	 // RepMucus
		updateSlider(&sliders[5], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 680));	 // RepWall
		updateSlider(&sliders[6], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 755));	 // RepSelf
		updateButton(&buttons[0], (new2Dcoord(largeurFenetre() - MenuWidth + 120, hauteurFenetre() - 118))); // Menu 1
		updateButton(&buttons[1], (new2Dcoord(largeurFenetre() - MenuWidth + 230, hauteurFenetre() - 118))); // Menu 2
		updateButton(&buttons[2], (new2Dcoord(largeurFenetre() - MenuWidth + 33, hauteurFenetre() - 123)));  // Return to menu

		// Menu "SIMULER"
		whenHoverUI(buttons2, nButtons2, sliders2, nSliders2, new2Dcoord(abscisseSouris(), ordonneeSouris()));
		updateText(&texts2[0], new2Dcoord(largeurFenetre() - MenuWidth + 50, hauteurFenetre() - 48));		  // Coneway
		updateText(&texts2[1], new2Dcoord(largeurFenetre() - MenuWidth + 130, hauteurFenetre() - 82));		  // Game of life
		updateSlider(&sliders2[0], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 225));	  // Vitesse
		updateButton(&buttons2[0], (new2Dcoord(largeurFenetre() - MenuWidth + 150, 40))); // Leave
		updateButton(&buttons2[1], (new2Dcoord(largeurFenetre() - MenuWidth + 90, 100)));  // Pause
		updateButton(&buttons2[2], (new2Dcoord(largeurFenetre() - MenuWidth + 200, 100))); // Reset
		updateButton(&buttons2[3], (new2Dcoord(largeurFenetre() - MenuWidth + 33, hauteurFenetre() - 123)));  // Return to menu
		updateButton(&buttons2[4], (new2Dcoord(largeurFenetre() - MenuWidth + 120, hauteurFenetre() - 118))); // Menu 1
		updateButton(&buttons2[5], (new2Dcoord(largeurFenetre() - MenuWidth + 230, hauteurFenetre() - 118))); // Menu 2
		updateButton(&buttons2[6], (new2Dcoord(largeurFenetre() - MenuWidth + 60, hauteurFenetre() - 300)));  // addType1
		updateButton(&buttons2[7], (new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 300))); // addType2
		updateButton(&buttons2[8], (new2Dcoord(largeurFenetre() - MenuWidth + 240, hauteurFenetre() - 300))); // addType3

		// Bouton retour
		if (menuType == false){
			ecrisImage(largeurFenetre() - MenuWidth, hauteurFenetre() - 210, header->largeurImage, header->hauteurImage, header->donneesRGB);
			printUI(buttons, nButtons, sliders, nSliders, texts, nTexts);
		}else{
			ecrisImage(largeurFenetre() - MenuWidth, hauteurFenetre() - 210, header->largeurImage, header->hauteurImage, header->donneesRGB);
			printUI(buttons2, nButtons2, sliders2, nSliders2, texts2, nTexts2);
		}	
	}
	updateButton(&buttons[2], ((new2Dcoord(largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45))));  // Menu Arrow
	updateButton(&buttons2[3], ((new2Dcoord(largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45)))); // Menu Arrow

	//KeyAnim 
	if (MenuWidth == 290){couleurCourante(255, 255, 255);triangle(largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45);triangle(largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 70);}
	else if (MenuWidth > 200 && MenuWidth < 290){couleurCourante(255, 255, 255);triangle(largeurFenetre() - MenuWidth - 40, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45);triangle(largeurFenetre() - MenuWidth - 40, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 70);}
	else if (MenuWidth > 150 && MenuWidth < 200){couleurCourante(255, 255, 255);triangle(largeurFenetre() - MenuWidth - 80, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45);triangle(largeurFenetre() - MenuWidth - 80, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 70);}
	else if (MenuWidth > 75 && MenuWidth < 150){couleurCourante(255, 255, 255);triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 35, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 45, hauteurFenetre() - 45);triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 45, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 35, hauteurFenetre() - 70);}
	else{couleurCourante(255, 255, 255);triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45);triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 70);}

	//MENU ICON	
	for (int j=0; j<3; j++) {
		for (int i=0; i<3; i++) {
			rectangle(largeurFenetre() - MenuWidth + 25 + i*12, hauteurFenetre() - 105 - 12*j, largeurFenetre() - MenuWidth + 25 - 8 + i*12, hauteurFenetre() - 105 - 8 - 12*j);
		}
	}

}

void mainMenu(EvenementGfx evenement, action *Action, int *DataSizeX, int *DataSizeY)
{
	//Matrice de données
	static int **CellData = NULL;

	//Affichage
	static int CellSize = 10;
	static int CellInBetween = 1;
	static int HcellCap;
	static int WcellCap;

	//Menu Elements
	static bool pause = true;
	static button *buttons = NULL;
	static slider *sliders = NULL;
	static text *texts = NULL;
	static int nButtons = 0;
	static int nSliders = 0;
	static int nTexts = 0;
	static int loaded = 0;
	static int W_temp;
	static int H_temp;

	static color **Colors;
	
	color RGBIdle = newColor(45,45,48);
	color RGBHover = newColor(55,55,58);
	color RGBClick = newColor(8,86,123);
	color RGBwhite = newColor(255,255,255);
	color background = newColor(28,28,28);
	color color_button = background;

	static int ombre = 10;
	static int border = 3;
	static DonneesImageRGB *header = NULL;
	switch (evenement){
		case Initialisation:;
			loaded = 0;
			*DataSizeX = MM_W;
			*DataSizeY = MM_H;
			iniGridData(&CellData, *DataSizeX, *DataSizeY);
			iniColors(&Colors, *DataSizeX, *DataSizeY);

			HcellCap = 100;
			WcellCap = 100;
			CellSize = 3;
			CellInBetween = 0;
			W_temp = WcellCap * (CellSize + CellInBetween);
			H_temp = HcellCap * (CellSize + CellInBetween);
			load(CellData, *DataSizeX, *DataSizeY, Colors, *Action);

			nButtons = 12;
			buttons = malloc(sizeof(button)*nButtons);
			buttons[0] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp,RGBIdle, RGBHover, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Laby, false, false);
			buttons[1] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp, RGBIdle, RGBHover, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Env, false, false);
			buttons[2] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp, RGBIdle, RGBHover, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Void, false, false);
			buttons[3] = newButton(
				new2Dcoord(0, 0), 
				W_temp, H_temp, RGBIdle, RGBHover, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Sandbox, false, false);
			buttons[4] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, 
				new2Dcoord(largeurFenetre() * 1/3 + (W_temp)/2 - 6,  hauteurFenetre() * 0.55),"Labyrinthe", 2), 
				menu_Laby, false, false);
			buttons[5] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, 
				new2Dcoord(largeurFenetre() * 11/17 + (W_temp)/2 - 6,  hauteurFenetre() * 0.50),"Environnement", 2), 
				menu_Env, false, false);
			buttons[6] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, 
				new2Dcoord(largeurFenetre() * 1/3 + (W_temp)/2 - 6,  hauteurFenetre() * 0.22),"Vide", 2), 
				menu_Void, false, false);
			buttons[7] = newButton(
				new2Dcoord(0, 0), 
				W_temp, 40, background, background, background, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, 
				new2Dcoord(largeurFenetre() * 11/17 + (W_temp)/2 - 6,  hauteurFenetre() * 0.22),"Custom", 2), 
				menu_Sandbox, false, false);
			buttons[9] = newButton(
				new2Dcoord(0, 0), 
				W_temp + border, H_temp + border,color_button, RGBClick, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Laby, false, false);
			buttons[10] = newButton(
				new2Dcoord(0, 0), 
				W_temp + border, H_temp + border, color_button, RGBClick, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Env, false, false);
			buttons[11] = newButton(
				new2Dcoord(0, 0), 
				W_temp + border, H_temp + border, color_button, RGBClick, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Void, false, false);
			buttons[8] = newButton(
				new2Dcoord(0, 0), 
				W_temp + border, H_temp + border, color_button, RGBClick, color_button, 
				newText(RGBwhite, RGBwhite, RGBwhite, 35, new2Dcoord(0,0),"", 1), 
				menu_Sandbox, false, false);
			
			nTexts = 2;
			texts = malloc(sizeof(button)*nTexts);
			texts[0] = newText(RGBwhite, RGBwhite, RGBwhite, 60, new2Dcoord(0,0),"BLOB", 5);
			texts[1] = newText(RGBwhite, RGBwhite, RGBwhite, 40, new2Dcoord(0,0),"ENGINE", 3);

			header = lisBMPRGB("#Ressources/header.bmp");

			demandeTemporisation(5);
			break;

		case Temporisation:
			updateButton(&buttons[0], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween));
			updateButton(&buttons[1], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween));
			updateButton(&buttons[2], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween));
			updateButton(&buttons[3], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween));
			updateButton(&buttons[4], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween - H_temp/2 - buttons[4].height/2));
			updateButton(&buttons[5], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 8/12 - CellSize - CellInBetween - H_temp/2 - buttons[5].height/2));
			updateButton(&buttons[6], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween - H_temp/2 - buttons[6].height/2));
			updateButton(&buttons[7], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween, hauteurFenetre() * 3/12 - CellSize - CellInBetween - H_temp/2 - buttons[7].height/2));
			updateButton(&buttons[9], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween + ombre, hauteurFenetre() * 8/12 - CellSize - CellInBetween + ombre));
			updateButton(&buttons[10], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween + ombre, hauteurFenetre() * 8/12 - CellSize - CellInBetween + ombre));
			updateButton(&buttons[11], new2Dcoord(largeurFenetre() * 1/3 - CellSize - CellInBetween + ombre, hauteurFenetre() * 3/12 - CellSize - CellInBetween + ombre));
			updateButton(&buttons[8], new2Dcoord(largeurFenetre() * 2/3 - CellSize - CellInBetween + ombre, hauteurFenetre() * 3/12 - CellSize - CellInBetween + ombre));
			updateText(&texts[0], new2Dcoord(50, hauteurFenetre() - 60));
			updateText(&texts[1], new2Dcoord(150, hauteurFenetre() - 110));
			whenHoverUI(buttons, nButtons, sliders, nSliders, new2Dcoord(abscisseSouris(), ordonneeSouris()));
			for (int i = 0; i < nButtons; i++){
				if(buttons[i].state == 1){
					switch (i){
					case 0:
					case 4:
						buttons[0].state = 1;
						buttons[4].state = 1;
						break;
					case 1:
					case 5:
						buttons[1].state = 1;
						buttons[5].state = 1;
						break;
					case 2:
					case 6:
						buttons[2].state = 1;
						buttons[6].state = 1;
						break;
					case 3:
					case 7:
						buttons[3].state = 1;
						buttons[7].state = 1;
						break;
					default:
						break;
					}
				}
			}
			loaded = 1;
			rafraichisFenetre();
			break;
		case Affichage:
			effaceFenetre(28,28,28);
			if(loaded){
				ecrisImage(0, hauteurFenetre() - header->hauteurImage, header->largeurImage, header->hauteurImage, header->donneesRGB);
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
				couleurCourante(255,0,0);
				circle(largeurFenetre()-40, hauteurFenetre()-40, 28);
				sqrt(pow(abscisseSouris()-(largeurFenetre()-40), 2) + pow(ordonneeSouris()-(hauteurFenetre()-40), 2)) <= 29 ? couleurCourante(255,0,0) : couleurCourante(28, 28, 28);
				circle(largeurFenetre()-40, hauteurFenetre()-40, 26);
				sqrt(pow(abscisseSouris()-(largeurFenetre()-40), 2) + pow(ordonneeSouris()-(hauteurFenetre()-40), 2)) <= 29 ? couleurCourante(255, 255, 255) : couleurCourante(255,0,0);
				epaisseurDeTrait(4);
				ligne(largeurFenetre()-54, hauteurFenetre()-54, largeurFenetre()-26, hauteurFenetre()-26);
				ligne(largeurFenetre()-26, hauteurFenetre()-54, largeurFenetre()-54, hauteurFenetre()-26);
			}
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye){
				switch (whenClickedUI(buttons, nButtons, sliders, nSliders, new2Dcoord(abscisseSouris(), ordonneeSouris()))){
					case menu_Laby:
						printf("menu_Laby\n");
						free(buttons);
						freeGridData(&CellData, *DataSizeX, *DataSizeY);
						freeColors(&Colors, *DataSizeX, *DataSizeY);
						free(texts);
						libereDonneesImageRGB(&header);
						*Action = menu_Laby;
						break;
					case menu_Env:
						printf("menu_Env\n");
						free(buttons);
						freeGridData(&CellData, *DataSizeX, *DataSizeY);
						freeColors(&Colors, *DataSizeX, *DataSizeY);
						free(texts);
						libereDonneesImageRGB(&header);
						*Action = menu_Env;
						break;
					case menu_Void:
						printf("menu_Void\n");
						*Action = menu_Void;
						free(buttons);
						freeGridData(&CellData, *DataSizeX, *DataSizeY);
						freeColors(&Colors, *DataSizeX, *DataSizeY);
						free(texts);
						libereDonneesImageRGB(&header);
						break;
					case menu_Sandbox:
						printf("menu_Sandbox\n");
						*Action = menu_Sandbox;
						free(buttons);
						freeGridData(&CellData, *DataSizeX, *DataSizeY);
						freeColors(&Colors, *DataSizeX, *DataSizeY);
						free(texts);
						libereDonneesImageRGB(&header);
						break;
					default:
						break;
				}
				if (sqrt(pow(abscisseSouris()-(largeurFenetre()-40), 2) + pow(ordonneeSouris()-(hauteurFenetre()-40), 2)) <= 30){
					printf("Quitter\n");
					free(buttons);
					freeGridData(&CellData, *DataSizeX, *DataSizeY);
					freeColors(&Colors, *DataSizeX, *DataSizeY);
					free(texts);
					libereDonneesImageRGB(&header);
					termineBoucleEvenements();
				}
			}
			rafraichisFenetre();
			break;
		case Souris:
			rafraichisFenetre();
			break;
	}
}

//Allocation dynamique et initialisation à 0 de la matrice
void iniGridData(int ***tab, int W, int H){
	*tab = (int**) malloc(sizeof(int*)*H);
	if(*tab == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniGridData 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<H; y++){
		(*tab)[y] = (int*) malloc(sizeof(int)*W);
		if((*tab)[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniGridData 2:%d)", y);
			for(int Y = 0; Y<y; Y++) free((*tab)[Y]);
			free(*tab);
			exit(EXIT_FAILURE);
		}
	}
	for(int x = 0; x<W; x++) for(int y = 0; y<H; y++) (*tab)[y][x] = 0;
}

//Libération de la mémoire
void freeGridData(int ***tab, int W, int H){
	for(int y = 0; y<H; y++) free((*tab)[y]);
	free(*tab);
	*tab = NULL;
}

void freeColors(color ***tab, int W, int H){
	for(int y = 0; y<H; y++) free((*tab)[y]);
	free(*tab);
	*tab = NULL;
}

//Allocation dynamique et initialisation à 0 de la matrice
void iniColors(color ***tab, int W, int H){
	*tab = (color**) malloc(sizeof(color*)*H);
	if(*tab == NULL){
		printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniGridData 1:0)");
		exit(EXIT_FAILURE);
	}
	for(int y = 0; y<H; y++){
		(*tab)[y] = (color*) malloc(sizeof(color)*W);
		if((*tab)[y] == NULL){
			printf("ERREUR CRITIQUE : Allocation mémoire sans solution (iniGridData 2:%d)", y);
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

	system("clear");
	system("ls ./#Ressources/*.cnw --format=single-column | cut -c 15- ");
    printf("SAVE CNW - Nom de votre fichier : ");
    scanf("%s", name);
    strcat(source,name);
    strcat(source,".cnw");
	fic = fopen(source, "w");

	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if(tabCell[i][j] == 1){
				fprintf(fic, "{%d;%d}%d/%d/%d;\n", i, j, tabCol[i][j].R, tabCol[i][j].G, tabCol[i][j].B);
			}
		}
	}

	fclose(fic);
	printf("Le fichier %s a ete enregistre ! \n", name);
}

//Ouvre la sauvegarde de la matrice
void load(int **tabCell, int W, int H, color **tabCol, action Action){
	FILE* fic = NULL;
	char name[20];
    char source[40] = "./#Ressources/";
	int i_temp = 0;
	int j_temp = 0;
	int R = 0;
	int V = 0;
	int B = 0;

	if(Action == 2){
		system("clear");
		system("ls ./#Ressources/*.cnw --format=single-column | cut -c 15- ");
		
		printf("LOAD CNW - Nom de votre fichier : ");
		scanf("%s", name);
		strcat(source, name);
	}
	else strcat(source, "baptiste");

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
	if(Action == 2) printf("Le fichier %s a ete charge ! \n", name);
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

void loadBMP(int **tabCell, color **tabCol){
	char name[20];
    char source[40] = "./#Ressources/";

	system("clear");
	system("ls ./#Ressources/*.bmp --format=single-column | cut -c 15- ");
    printf("LOAD BMP - Nom de votre fichier : ");
    scanf("%s", name);
    strcat(name, ".bmp");
    strcat(source, name);

	DonneesImageRGB *image = NULL;
	image = lisBMPRGB(source);

    for(int i=0;i<image->hauteurImage;i++){
        for(int j=0;j<image->largeurImage;j++){
			tabCol[i][j].R = image->donneesRGB[(j+i*image->hauteurImage)*3+2];
			tabCol[i][j].G = image->donneesRGB[(j+i*image->hauteurImage)*3+1];
			tabCol[i][j].B = image->donneesRGB[(j+i*image->hauteurImage)*3];
			tabCell[i][j] = 1;
        }
    }
	libereDonneesImageRGB(&image);
	printf("Le fichier %s a ete charge ! \n", name);
}

void saveBMP(int **tabCell, int W, int H, color **tabCol){
	char name[20];
    char source[40] = "./#Ressources/";

	system("clear");
	system("ls ./#Ressources/*.bmp --format=single-column | cut -c 15- ");
    printf("SAVE BMP - Nom de votre fichier : ");
    scanf("%s", name);
    strcat(name, ".bmp");
    strcat(source, name);

	
	DonneesImageRGB *image = NULL;
	image = lisBMPRGB("./#Ressources/matrice.bmp");

	H = image->hauteurImage;
	W = image->largeurImage;

	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if(tabCell[i][j] == 1){
				image->donneesRGB[(j+i*image->hauteurImage)*3+2] = tabCol[i][j].R;
				image->donneesRGB[(j+i*image->hauteurImage)*3+1] = tabCol[i][j].G;
				image->donneesRGB[(j+i*image->hauteurImage)*3] = tabCol[i][j].B;
			}
			else {
				image->donneesRGB[(j+i*image->hauteurImage)*3+2] = 0;
				image->donneesRGB[(j+i*image->hauteurImage)*3+1] = 0;
				image->donneesRGB[(j+i*image->hauteurImage)*3] = 0;
			}
		}
	}
	libereDonneesImageRGB(&image);
	printf("Le fichier %s a ete enregistre ! \n", name);
}

void FreePointer(void **pointer) 
{
	if(*pointer != NULL){
		free(*pointer);
		*pointer=NULL;
	}
}
