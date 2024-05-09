#include <iostream>
#include <graphics.h>

// Structure to represent a point
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Function to draw a point
void drawPoint(int x, int y) {
    putpixel(x, y, WHITE);
}

// Function to draw Hermite curve
void drawHermiteCurve(Point P0, Point P1, Point R0, Point R1) {
    double t;
    Point P;
    for (int i = 0; i <= 1000; i++) {
        t = i / 1000.0;
        double h1 = 2 * t * t * t - 3 * t * t + 1;
        double h2 = -2 * t * t * t + 3 * t * t;
        double h3 = t * t * t - 2 * t * t + t;
        double h4 = t * t * t - t * t;
        P.x = h1 * P0.x + h2 * P1.x + h3 * R0.x + h4 * R1.x;
        P.y = h1 * P0.y + h2 * P1.y + h3 * R0.y + h4 * R1.y;
        drawPoint(P.x, P.y);
    }
}

// Function to draw Bezier curve
void drawBezierCurve(Point P0, Point P1, Point P2, Point P3) {
    double t;
    Point P;
    for (int i = 0; i <= 1000; i++) {
        t = i / 1000.0;
        double b0 = (1 - t) * (1 - t) * (1 - t);
        double b1 = 3 * t * (1 - t) * (1 - t);
        double b2 = 3 * t * t * (1 - t);
        double b3 = t * t * t;
        P.x = b0 * P0.x + b1 * P1.x + b2 * P2.x + b3 * P3.x;
        P.y = b0 * P0.y + b1 * P1.y + b2 * P2.y + b3 * P3.y;
        drawPoint(P.x, P.y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Hermite curve
    Point P0(100, 100), P1(300, 100), R0(150, 50), R1(250, 150);
    drawHermiteCurve(P0, P1, R0, R1);

    // Bezier curve
    Point P2(100, 200), P3(300, 200);
    drawBezierCurve(P0, P1, P2, P3);

    getch();
    closegraph();
    return 0;
}
