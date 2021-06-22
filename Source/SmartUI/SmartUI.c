#include <stdlib.h> 
#include <stdio.h>	
#include <math.h>	
#include <string.h>
#include "../GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "SmartUI.h"

#define CURSOR_R 10

coord2D new2Dcoord(int x, int y){
    coord2D new;
    new.x = x;
    new.y = y;
    return new;
}

color newColor(int R, int G, int B){
    color new;
    new.R = R;
    new.G = G;
    new.B = B;
    return new;
}

text newText(color RGBIdle, color RGBhover, color RGBclick, int size, coord2D position, char *string, int weigth){
    text new;
    new.RGBIdle = RGBIdle;
    new.RGBhover = RGBhover;
    new.RGBclick = RGBclick;
    new.size = size;
    new.position = position;
    new.weigth = weigth;
    new.string = (char*) malloc(sizeof(string));
    strcpy(new.string, string);
    return new;
}

button newButton(coord2D centerPoint, int width, int height, color RGBIdle, color RGBhover, color RGBclick, text text, action action, bool IsToggleButton, bool TogggleStatus){
    button new;
    new.centerPoint = centerPoint;
    new.width = width;
    new.height = height;
    new.startPoint = new2Dcoord(centerPoint.x - (width / 2), centerPoint.y - (height / 2));
    new.endPoint = new2Dcoord(centerPoint.x + (width / 2), centerPoint.y + (height / 2));
    new.RGBIdle = RGBIdle;
    new.RGBhover = RGBhover;
    new.RGBclick = RGBclick;
    new.text = text;
    new.text.position = new2Dcoord(centerPoint.x - (tailleChaine(text.string, text.size) / 2), centerPoint.y - (text.size / 2));
    new.action = action;
    new.IsToggleButton = IsToggleButton;
    new.TogggleStatus = TogggleStatus;
    new.state = TogggleStatus ? Clicked : Idle;
    return new;
}

slider newSlider(coord2D centerPoint, int width, int min, int max, int step, color RGBIdle, color RGBhover, color RGBclick, action action, bool snap){
    slider new;
    new.startPoint = new2Dcoord(centerPoint.x - (width/2), centerPoint.y);
    new.endPoint = new2Dcoord(centerPoint.x + (width/2), centerPoint.y);
    new.centerPoint = centerPoint;
    new.width = width;
    new.min = min;
    new.max = max;
    new.step = step;
    new.RGBIdle = RGBIdle;
    new.RGBhover = RGBhover;
    new.RGBclick = RGBclick;
    new.value = min;
    new.snap = snap;
    new.state = Idle;
    new.cursor = new.startPoint;
    new.action = action;
    return new;
}


//FONCTIONS D'AFFICHAGE

void cursor(float centreX, float centreY){
	const int Pas = 40;
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	float rayon = CURSOR_R;
	for (index = 0; index < Pas; ++index){
		const double angle = 2.*M_PI*index/Pas;
		triangle(centreX, centreY, centreX+rayon*cos(angle), centreY+rayon*sin(angle), centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
	}
}

void circle(float centreX, float centreY, float rayon)
{
	const int Pas = 40;
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	for (index = 0; index < Pas; ++index){
		const double angle = 2.*M_PI*index/Pas;
		triangle(centreX, centreY, centreX+rayon*cos(angle), centreY+rayon*sin(angle), centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
	}
}

void printUI(button *buttons, int arraySizeB, slider *sliders, int arraySizeS, text *texts, int arraySizeT)
{   
    for(int n = 0; n < arraySizeB; n++){
        button b = buttons[n];
        if(b.state != Hiden){
            switch (b.state)
            {
            case Idle:
                couleurCourante(b.RGBIdle.R, b.RGBIdle.G, b.RGBIdle.B);
                break;
            case Hover:
                couleurCourante(b.RGBhover.R, b.RGBhover.G, b.RGBhover.B);
                break;
            case Clicked:
                couleurCourante(b.RGBclick.R, b.RGBclick.G, b.RGBclick.B);
                break;
            }
            rectangle(b.startPoint.x, b.startPoint.y, b.endPoint.x,  b.endPoint.y);
            switch (b.state)
            {
            case Idle:
                couleurCourante(b.text.RGBIdle.R, b.text.RGBIdle.G, b.text.RGBIdle.B);
                break;
            case Hover:
                couleurCourante(b.text.RGBhover.R, b.text.RGBhover.G, b.text.RGBhover.B);
                break;
            case Clicked:
                couleurCourante(b.text.RGBclick.R, b.text.RGBclick.G, b.text.RGBclick.B);
                break;
            }
            epaisseurDeTrait(b.text.weigth);
            afficheChaine(b.text.string, b.text.size, b.text.position.x, b.text.position.y);
        }
    }
    for(int n = 0; n < arraySizeS; n++){
        slider s = sliders[n];
        if(s.state != Hiden){
            epaisseurDeTrait(6);
            couleurCourante(s.RGBhover.R, s.RGBhover.G, s.RGBhover.B);
            ligne(s.startPoint.x,s.startPoint.y,s.cursor.x,s.cursor.y);
            couleurCourante(s.RGBIdle.R, s.RGBIdle.G, s.RGBIdle.B);
            ligne(s.cursor.x,s.cursor.y,s.endPoint.x,s.endPoint.y);
            switch (s.state)
            {
            case Idle:
                couleurCourante(s.RGBhover.R, s.RGBhover.G, s.RGBhover.B);
                break;
            case Hover:
                couleurCourante(s.RGBhover.R + 10, s.RGBhover.G + 10, s.RGBhover.B + 10);
                break;
            case Clicked:
                couleurCourante(s.RGBclick.R, s.RGBclick.G, s.RGBclick.B);
                break;
            }
            cursor(s.cursor.x,s.cursor.y);
        }
    }
    for(int n = 0; n < arraySizeT; n++){
        text t = texts[n];
        couleurCourante(t.RGBIdle.R, t.RGBIdle.G, t.RGBIdle.B);
        epaisseurDeTrait(t.weigth);
        afficheChaine(t.string, t.size, t.position.x, t.position.y);
    }
}


//GESTION D'EVENTS

action whenClickedUI(button* buttons, int arraySizeB, slider* sliders, int arraySizeS, coord2D mouse)
{   
    action resultAction = none;
    for(int n = 0; n < arraySizeB; n++){
        if(mouse.x >= buttons[n].startPoint.x && mouse.y >= buttons[n].startPoint.y  && mouse.x <= buttons[n].endPoint.x &&  mouse.y <= buttons[n].endPoint.y && !buttons[n].IsToggleButton){
            buttons[n].state = Clicked;
            resultAction = buttons[n].action;
        }
    }
    for(int n = 0; n < arraySizeS; n++){
        if(sliders[n].state != Hiden && (sqrt(pow(mouse.x - sliders[n].cursor.x, 2) + pow(mouse.y - sliders[n].cursor.y, 2)) <= CURSOR_R 
        || (mouse.x >= sliders[n].startPoint.x && mouse.y >= (sliders[n].startPoint.y-CURSOR_R)  && mouse.x <= sliders[n].endPoint.x &&  mouse.y <= (sliders[n].startPoint.y + CURSOR_R)))){
            sliders[n].state = Clicked;
        }
    }
    return resultAction;
}

action whenReleasedUI(button *buttons, int arraySizeB, slider *sliders, int arraySizeS)
{   
    coord2D mouse = new2Dcoord(abscisseSouris(),ordonneeSouris());
    action resultAction = none;
    for(int n = 0; n < arraySizeB; n++) if(buttons[n].state == Clicked && !buttons[n].IsToggleButton) buttons[n].state = Idle;
    for(int n = 0; n < arraySizeB; n++){
        if(mouse.x >= buttons[n].startPoint.x && mouse.y >= buttons[n].startPoint.y  && mouse.x <= buttons[n].endPoint.x && mouse.y <= buttons[n].endPoint.y && buttons[n].IsToggleButton){
            buttons[n].TogggleStatus = !buttons[n].TogggleStatus;
            if(buttons[n].TogggleStatus) buttons[n].state = Clicked;
            else buttons[n].state = Hover;
            resultAction = buttons[n].action;
        }
    }
                    
    for(int n = 0; n < arraySizeS; n++) if(sliders[n].state == Clicked){
        sliders[n].state = Idle;
        resultAction = sliders[n].action;
    }
    return resultAction;
}

void whenHoverUI(button *buttons, int arraySizeB, slider *sliders, int arraySizeS, coord2D mouse)
{   
    for(int n = 0; n < arraySizeB; n++){
        if(mouse.x >= buttons[n].startPoint.x && mouse.y >= buttons[n].startPoint.y  && mouse.x <= buttons[n].endPoint.x &&  mouse.y <= buttons[n].endPoint.y && buttons[n].state != Hiden){
            if(buttons[n].state != Clicked) buttons[n].state = Hover;
        }
        else if(!buttons[n].TogggleStatus && buttons[n].state != Hiden ) buttons[n].state = Idle;
    }
    for(int n = 0; n < arraySizeS; n++){
        if(mouse.x >= sliders[n].startPoint.x && mouse.y >= sliders[n].startPoint.y  && mouse.x <= sliders[n].endPoint.x &&  mouse.y <= sliders[n].endPoint.y){
            if(sliders[n].state != Clicked && sliders[n].state != Hiden) sliders[n].state = Hover;
        }
        else if(sliders[n].state != Hiden && sliders[n].state != Clicked) sliders[n].state = Idle;
        if(sliders[n].state == Clicked){
            if(!sliders[n].snap){
                sliders[n].cursor.x = mouse.x;
                if(mouse.x > sliders[n].endPoint.x)sliders[n].cursor.x = sliders[n].endPoint.x;
                if(mouse.x < sliders[n].startPoint.x)sliders[n].cursor.x = sliders[n].startPoint.x;
                sliders[n].value = (sliders[n].cursor.x - sliders[n].startPoint.x)/(sliders[n].width/(sliders[n].max - sliders[n].min)) + sliders[n].min;
                sliders[n].value = sliders[n].value > sliders[n].max ? sliders[n].max : sliders[n].value < sliders[n].min ? sliders[n].min : sliders[n].value;
            }
        }
    }
}

//UPDATE ELEMENTS

void updateButton(button *b, coord2D centerPoint){
    b->centerPoint = centerPoint;
    b->startPoint = new2Dcoord(b->centerPoint.x - (b->width / 2), b->centerPoint.y - (b->height / 2));
    b->endPoint = new2Dcoord(b->centerPoint.x + (b->width / 2), b->centerPoint.y + (b->height / 2));
    b->text.position = new2Dcoord(b->centerPoint.x - (tailleChaine(b->text.string, b->text.size) / 2), b->centerPoint.y - (b->text.size / 2));
}

void updateSlider(slider *s, coord2D centerPoint){
    s->startPoint = new2Dcoord(centerPoint.x - (s->width/2), centerPoint.y);
    s->endPoint = new2Dcoord(centerPoint.x + (s->width/2), centerPoint.y);
    s->centerPoint = centerPoint;
    s->cursor.x = s->startPoint.x + (s->width/(s->max - s->min))*abs(s->value - s->min);
    s->cursor.y = centerPoint.y;
}

void updateText(text *t, coord2D position){
    t->position = position;
    // free(t->string);
    // t->string = (char*) malloc(sizeof(string));
    // strcpy(t->string, string);
}