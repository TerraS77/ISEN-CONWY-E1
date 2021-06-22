/*

.___  ___.  _______ .__   __.  __    __  
|   \/   | |   ____||  \ |  | |  |  |  | 
|  \  /  | |  |__   |   \|  | |  |  |  | 
|  |\/|  | |   __|  |  . `  | |  |  |  | 
|  |  |  | |  |____ |  |\   | |  `--'  | 
|__|  |__| |_______||__| \__|  \______/  
                                         
*/

#include "menu.h"

// Initialise le menu de contrôle du Blob
void IniMenu(DonneesImageRGB **header, int *nTexts, text **texts, int *nSliders, slider **sliders, int *nButtons, button **buttons, int *nTexts2, text **texts2, int *nButtons2, button **buttons2, int *nSliders2, slider **sliders2, int MenuWidth, simulation sim)
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
	(*texts)[0] = newText(RGBwhite, RGBwhite, RGBwhite, 50, Origin, "Blob", 4);
	(*texts)[1] = newText(RGBwhite, RGBwhite, RGBwhite, 25, Origin, "Engine", 2);
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
	(*buttons)[3] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 43, hauteurFenetre() - 123), 45, 50, newColor(28, 28, 28), newColor(28, 28, 28), newColor(28, 28, 28), newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "", 2), BackToMenu, false, false);

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
	(*buttons2)[9] = newButton(new2Dcoord(largeurFenetre() - MenuWidth + 43, hauteurFenetre() - 123), 45, 50, newColor(28, 28, 28), newColor(28, 28, 28), newColor(28, 28, 28), newText(newColor(255, 255, 255), newColor(255, 255, 255), newColor(255, 255, 255), 25, new2Dcoord(0, 0), "", 2), BackToMenu, false, false);
	//SLIDE
	*nSliders2 = 1;
	*sliders2 = (slider *)malloc(sizeof(slider));
	(*sliders2)[0] = newSlider(new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 325), 200, 0, 200, 1, RGBIdle, RGBHover, RGBClick, UpdateSpeed, false);
	(*sliders2)[0].value = 100;
	//TXT
	*nTexts2 = 3;
	*texts2 = (text *)malloc(sizeof(text) * (*nTexts2));
	(*texts2)[0] = newText(RGBwhite, RGBwhite, RGBwhite, 50, new2Dcoord(largeurFenetre() - MenuWidth + 20, hauteurFenetre() - 50), "Blob", 4);
	(*texts2)[1] = newText(RGBwhite, RGBwhite, RGBwhite, 25, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 80), "Engine", 2);
	(*texts2)[2] = newText(RGBwhite, RGBwhite, RGBwhite, 25, new2Dcoord(largeurFenetre() - MenuWidth + 30, hauteurFenetre() - 350), "Vitesse : ", 2);
}

// Afficher le menu de contrôle
void displayBlobUI(button *buttons, slider *sliders, text *texts, button *buttons2, slider *sliders2, text *texts2, int MenuWidth, int nSliders, int nButtons, int nTexts, int nSliders2, int nButtons2, int nTexts2, int vivant, int Sx2, int Sy2, int gen, simulation *sim, bool menuType, DonneesImageRGB *header)
{
	printf("MENU WIDTH = %d", MenuWidth);
	updateButton(&buttons[2], ((new2Dcoord(largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45))));  // Menu Arrow
	updateButton(&buttons2[3], ((new2Dcoord(largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45)))); // Menu Arrow
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
		updateText(&texts[0], new2Dcoord(largeurFenetre() - MenuWidth + 140, hauteurFenetre() - 50));		 // Conway
		updateText(&texts[1], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 80));		 // Game of life
		updateSlider(&sliders[0], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 305));	 // ramificationRarity
		updateSlider(&sliders[1], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 380));	 // detectionRadius
		updateSlider(&sliders[2], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 455));	 // Oscillation
		updateSlider(&sliders[3], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 530));	 // AtracFood
		updateSlider(&sliders[4], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 605));	 // RepMucus
		updateSlider(&sliders[5], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 680));	 // RepWall
		updateSlider(&sliders[6], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 755));	 // RepSelf
		updateButton(&buttons[0], (new2Dcoord(largeurFenetre() - MenuWidth + 120, hauteurFenetre() - 118)));	 // Menu 1
		updateButton(&buttons[1], (new2Dcoord(largeurFenetre() - MenuWidth + 230, hauteurFenetre() - 118))); // Menu 2
		updateButton(&buttons[2], (new2Dcoord(largeurFenetre() - MenuWidth + 33, hauteurFenetre() - 123))); // Return to menu

		// Menu "SIMULER"
		whenHoverUI(buttons2, nButtons2, sliders2, nSliders2, new2Dcoord(abscisseSouris(), ordonneeSouris()));
		updateText(&texts2[0], new2Dcoord(largeurFenetre() - MenuWidth + 140, hauteurFenetre() - 50));		  // Coneway
		updateText(&texts2[1], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 80));		  // Game of life
		updateSlider(&sliders2[0], new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 225));	  // Vitesse
		updateButton(&buttons2[0], (new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 710))); // Leave
		updateButton(&buttons2[1], (new2Dcoord(largeurFenetre() - MenuWidth + 90, hauteurFenetre() - 650)));  // Pause
		updateButton(&buttons2[2], (new2Dcoord(largeurFenetre() - MenuWidth + 200, hauteurFenetre() - 650))); // Reset
		updateButton(&buttons2[4], (new2Dcoord(largeurFenetre() - MenuWidth + 120, hauteurFenetre() - 118)));  // Menu 1
		updateButton(&buttons2[5], (new2Dcoord(largeurFenetre() - MenuWidth + 230, hauteurFenetre() - 118))); // Menu 2
		updateButton(&buttons2[6], (new2Dcoord(largeurFenetre() - MenuWidth + 60, hauteurFenetre() - 300)));  // addType1
		updateButton(&buttons2[7], (new2Dcoord(largeurFenetre() - MenuWidth + 150, hauteurFenetre() - 300))); // addType2
		updateButton(&buttons2[8], (new2Dcoord(largeurFenetre() - MenuWidth + 240, hauteurFenetre() - 300))); // addType3

		// Bouton retour
		if (menuType == false){
				ecrisImage(largeurFenetre() - MenuWidth, hauteurFenetre() - 210, header->largeurImage, header->hauteurImage, header->donneesRGB);
				printUI(buttons, nButtons, sliders, nSliders, texts, nTexts);
			}
		else{
				ecrisImage(largeurFenetre() - MenuWidth, hauteurFenetre() - 210, header->largeurImage, header->hauteurImage, header->donneesRGB);
				printUI(buttons2, nButtons2, sliders2, nSliders2, texts2, nTexts2);
			}
	}
	if (MenuWidth == 290)
		{
			couleurCourante(255, 255, 255);
			triangle(largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45);
			triangle(largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 70);
		}
		else if (MenuWidth > 200 && MenuWidth < 290)
		{
			couleurCourante(255, 255, 255);
			triangle(largeurFenetre() - MenuWidth - 40, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45);
			triangle(largeurFenetre() - MenuWidth - 40, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 70);
		}
		else if (MenuWidth > 150 && MenuWidth < 200)
		{
			couleurCourante(255, 255, 255);
			triangle(largeurFenetre() - MenuWidth - 80, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45);
			triangle(largeurFenetre() - MenuWidth - 80, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 60, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 70);
		}
		else if (MenuWidth > 75 && MenuWidth < 150)
		{
			couleurCourante(255, 255, 255);
			triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 35, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 45, hauteurFenetre() - 45);
			triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 45, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 35, hauteurFenetre() - 70);
		}
		else
		{
			couleurCourante(255, 255, 255);
			triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 20, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45);
			triangle(largeurFenetre() - MenuWidth - 70, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 50, hauteurFenetre() - 45, largeurFenetre() - MenuWidth - 30, hauteurFenetre() - 70);
		}

		// rectangle(largeurFenetre() - MenuWidth + 20, hauteurFenetre() - 15, largeurFenetre() - MenuWidth + 84, hauteurFenetre() - 79);
		for (int j=0; j<3; j++) {
			for (int i=0; i<3; i++) {
				rectangle(largeurFenetre() - MenuWidth + 25 + i*12, hauteurFenetre() - 105 - 12*j, largeurFenetre() - MenuWidth + 25 - 8 + i*12, hauteurFenetre() - 105 - 8 - 12*j);
			}
		}
}