//Write a progam to implement mid-point circle drawing algorithm.

#include <graphics.h>

using namespace std;

void circlemidpoint(int x, int y, int r)
{
    int p = 1 - r;
    int x1 = 0, y1 = r;

    while (x1 <= y1)
    {
        putpixel(x + x1, y + y1, WHITE);
        putpixel(x - x1, y + y1, WHITE);
        putpixel(x + x1, y - y1, WHITE);
        putpixel(x - x1, y - y1, WHITE);
        putpixel(x + y1, y + x1, WHITE);
        putpixel(x - y1, y + x1, WHITE);
        putpixel(x + y1, y - x1, WHITE);
        putpixel(x - y1, y - x1, WHITE);

        if (p < 0)
        {
            p += 2 * x1 + 3;
        }
        else
        {
            p += 2 * (x1 - y1) + 5;
            y1--;
        }

        x1++;
    }
}

void drawcircle(int x, int y, int r, int color)
{
    setcolor(color);
    circlemidpoint(x, y, r);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");

    drawcircle(100, 100, 50, RED);

    getch();
    closegraph();

    return 0;
}
