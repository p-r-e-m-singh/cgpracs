#include <iostream>
#include <graphics.h>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a point
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Function to draw a horizontal line between two points
void drawHorizontalLine(int x1, int y, int x2) {
    for (int x = x1; x <= x2; x++) {
        putpixel(x, y, WHITE);
    }
}

// Function to find minimum and maximum x coordinates
void findMinMaxX(const vector<Point>& polygon, int& min_x, int& max_x) {
    min_x = polygon[0].x;
    max_x = polygon[0].x;
    for (size_t i = 1; i < polygon.size(); i++) {
        if (polygon[i].x < min_x)
            min_x = polygon[i].x;
        if (polygon[i].x > max_x)
            max_x = polygon[i].x;
    }
}

// Function to fill the polygon using the scan-line fill algorithm
void scanLineFill(const vector<Point>& polygon) {
    int min_y = polygon[0].y, max_y = polygon[0].y;
    int min_x, max_x;
    findMinMaxX(polygon, min_x, max_x);

    for (size_t i = 1; i < polygon.size(); i++) {
        if (polygon[i].y < min_y)
            min_y = polygon[i].y;
        if (polygon[i].y > max_y)
            max_y = polygon[i].y;
    }

    for (int y = min_y; y <= max_y; y++) {
        vector<int> intersectingPoints;
        for (size_t i = 0; i < polygon.size(); i++) {
            size_t next = (i + 1) % polygon.size();
            if ((polygon[i].y <= y && polygon[next].y >= y) || (polygon[i].y >= y && polygon[next].y <= y)) {
                if (polygon[i].y != polygon[next].y) {
                    int x = static_cast<int>(polygon[i].x + (static_cast<double>(y - polygon[i].y) / (polygon[next].y - polygon[i].y)) * (polygon[next].x - polygon[i].x));
                    intersectingPoints.push_back(x);
                }
            }
        }

        sort(intersectingPoints.begin(), intersectingPoints.end());
        for (size_t i = 0; i < intersectingPoints.size(); i += 2) {
            drawHorizontalLine(intersectingPoints[i], y, intersectingPoints[i + 1]);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    vector<Point> polygon = {{200, 100}, {300, 200}, {200, 300}, {100, 200}};

    // Draw the polygon
    for (size_t i = 0; i < polygon.size(); i++) {
        size_t next = (i + 1) % polygon.size();
        line(polygon[i].x, polygon[i].y, polygon[next].x, polygon[next].y);
    }

    // Fill the polygon
    scanLineFill(polygon);

    getch();
    closegraph();
    return 0;
}
