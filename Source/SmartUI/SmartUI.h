typedef enum {Idle, Hover, Clicked, Hiden} status;
typedef enum {none, UpdateSpeed, TogglePause, Leave, RESET} action;

typedef struct{
    int x;
    int y;
}coord2D;

typedef struct{
    int R;
    int G;
    int B;
}color;

typedef struct{
    color RGBIdle;
    color RGBhover;
    color RGBclick;
    int size;
    coord2D position;
    char* string;
    int weigth;
}text;

typedef struct{
    coord2D startPoint;
    coord2D endPoint;
    coord2D centerPoint;
    color RGBIdle;
    color RGBhover;
    color RGBclick;
    text text;
    int width;
    int height;
    action action;
    bool IsToggleButton;
    bool TogggleStatus;
    status state;
}button;

typedef struct{
    coord2D startPoint;
    coord2D endPoint;
    coord2D centerPoint;
    coord2D cursor;
    int width;
    int min;
    int max;
    int step;
    color RGBIdle;
    color RGBhover;
    color RGBclick;
    action action;
    int value;
    bool snap;
    status state;
}slider;

coord2D new2Dcoord(int x, int y);
color newColor(int R, int G, int B);
text newText(color RGBIdle, color RGBhover, color RGBclick, int size, coord2D position, char *string, int weigth);
button newButton(coord2D centerPoint, int width, int height, color RGBIdle, color RGBhover, color RGBclick, text text, action action, bool IsToggleButton, bool TogggleStatus);
slider newSlider(coord2D centerPoint, int width, int min, int max, int step, color RGBIdle, color RGBhover, color RGBclick, action action, bool snap);
void printUI(button buttons[], int arraySize, slider sliders[], int arraySizeS, text texts[], int arraySizeT);
action whenClickedUI(button buttons[], int arraySize, slider sliders[], int arraySizeS, coord2D mouse);
action whenReleasedUI(button buttons[], int arraySize, slider sliders[], int arraySizeS);
void whenHoverUI(button buttons[], int arraySize, slider sliders[], int arraySizeS, coord2D mouse);
void updateButton(button *b, coord2D centerPoint);
void updateSlider(slider *s, coord2D centerPoint);
void updateText(text *t, coord2D position);