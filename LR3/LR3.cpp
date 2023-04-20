
#include "graphics.h"
#pragma comment(lib,"LibBGI.lib")

#include <limits.h>
using namespace std;
byte window[900][600];

void fill(int x, int y);
struct coords {
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;
};
void drawLine(int x1, int y1, int x2, int y2, int color = 15) {
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = 0;
    int deltaErr = ((deltaX > deltaY) ? deltaY : deltaX) + 1;
    putpixel(x2, y2, color);
    if (deltaX > deltaY) {
        for (x1; x1 != x2; (x2 > x1) ? x1++ : x1--) {
            putpixel(x1, y1, color);
            error += deltaErr;
            if (error >= deltaX + 1) {
                y1 += signY;
                error = error - (deltaX + 1);
            }
        }
    }
    else {
        for (y1; y1 != y2; (y2 > y1) ? y1++ : y1--) {
            putpixel(x1, y1, color);
            error += deltaErr;
            if (error >= deltaY + 1) {
                x1 += signX;
                error = error - (deltaY + 1);
            }
        }
    }
    setcolor(15);
}
void drawFigure(struct coords* figure) {
    drawLine(figure->x1, figure->y1, figure->x2, figure->y2);
    drawLine(figure->x2, figure->y2, figure->x3, figure->y3);
    drawLine(figure->x3, figure->y3, figure->x4, figure->y4);
    drawLine(figure->x4, figure->y4, figure->x1, figure->y1);
    
    fill((figure->x1+ figure->x2+ figure->x3)/3, (figure->y1+ figure->y2+ figure->y3)/3);
    swapbuffers();
    
    
}
void rotate(struct coords* figure, int angle) {
    float ox = (figure->x1 + figure->x2 + figure->x3 + figure->x4) / 4;
    float oy = (figure->y1 + figure->y2 + figure->y3 + figure->y4) / 4;
    float s = sin(angle * 3.14 / 180);
    float c = cos(angle * 3.14 / 180);
    float x = 0;
    float y = 0;
    x = figure->x1;
    y = figure->y1;
    figure->x1 = (x - ox) * c - (y - oy) * s + ox;
    figure->y1 = (x - ox) * s + (y - oy) * c + oy;
    x = figure->x2;
    y = figure->y2;
    figure->x2 = (x - ox) * c - (y - oy) * s + ox;
    figure->y2 = (x - ox) * s + (y - oy) * c + oy;
    x = figure->x3;
    y = figure->y3;
    figure->x3 = (x - ox) * c - (y - oy) * s + ox;
    figure->y3 = (x - ox) * s + (y - oy) * c + oy;
    x = figure->x4;
    y = figure->y4;
    figure->x4 = (x - ox) * c - (y - oy) * s + ox;
    figure->y4 = (x - ox) * s + (y - oy) * c + oy;
}
void scale(struct coords* figure, float coef) {
    int ox = (figure->x1 + figure->x2 + figure->x3 + figure->x4) / 4;
    int oy = (figure->y1 + figure->y2 + figure->y3 + figure->y4) / 4;
    figure->x1 = (figure->x1 - ox) * coef + ox;
    figure->y1 = (figure->y1 - oy) * coef + oy;
    figure->x2 = (figure->x2 - ox) * coef + ox;
    figure->y2 = (figure->y2 - oy) * coef + oy;
    figure->x3 = (figure->x3 - ox) * coef + ox;
    figure->y3 = (figure->y3 - oy) * coef + oy;
    figure->x4 = (figure->x4 - ox) * coef + ox;
    figure->y4 = (figure->y4 - oy) * coef + oy;
}
void shift(struct coords* figure, float dx, float dy) {
    figure->x1 = figure->x1 + dx;
    figure->y1 = figure->y1 + dy;
    figure->x2 = figure->x2 + dx;
    figure->y2 = figure->y2 + dy;
    figure->x3 = figure->x3 + dx;
    figure->y3 = figure->y3 + dy;
    figure->x4 = figure->x4 + dx;
    figure->y4 = figure->y4 + dy;
}
void fill(int x, int y) {
    if (getpixel(x, y) == 0) {
        putpixel(x, y, 15); 
        fill(x, y - 1);
        fill(x - 1, y);
        fill(x + 1, y);
        fill(x, y + 1);
    }   
}
int main()
{

    struct coords figure = { 240, 240, 300, 150, 400, 300, 100, 300 };
    initwindow(900, 500, "LAB3", 0, 0, true);
    outtext(_strdup("Стрелки - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; 0 - Выход."));
    drawFigure(&figure);
   
    
    int c;
    do {
        c = (char)getch();
        clearviewport();
        outtext(_strdup("Стрелки - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; 0 - Выход."));
        switch (c) {
        case (KEY_UP):
            shift(&figure, 0, -2);
            break;
        case (KEY_DOWN):
            shift(&figure, 0, 2);
            break;
        case (KEY_LEFT):
            shift(&figure, -2, 0);
            break;
        case (KEY_RIGHT):
            shift(&figure, 2, 0);
            break;
        case 'i':
            scale(&figure, 1.05);
            break;
        case 'o':
            scale(&figure, 0.95);
            break;
        case 'r':
            rotate(&figure, 10);
            break;

        }
        drawFigure(&figure);
    } while (c != '0');

}