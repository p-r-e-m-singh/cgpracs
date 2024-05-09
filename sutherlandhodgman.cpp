#include <iostream>
#include <vector>
#include <cmath>
#include <graphics.h> // Assuming graphics.h is available in your environment
using namespace std;

// Structure to represent a point
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Function to find intersection point of two lines
Point computeIntersection(Point p1, Point p2, Point q1, Point q2) {
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;
    int x3 = q1.x, y3 = q1.y;
    int x4 = q2.x, y4 = q2.y;

    int denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    int px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
    int py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;

    return Point(px, py);
}

// Function to perform polygon clipping using Sutherland-Hodgman algorithm
vector<Point> sutherlandHodgman(const vector<Point>& polygon, const vector<Point>& clipper) {
    vector<Point> output;
    for (size_t i = 0; i < clipper.size(); ++i) {
        size_t j = (i + 1) % clipper.size();
        vector<Point> temp;

        for (size_t k = 0; k < polygon.size(); ++k) {
            size_t l = (k + 1) % polygon.size();
            int val1 = (clipper[j].x - clipper[i].x) * (polygon[k].y - clipper[i].y) - 
                       (clipper[j].y - clipper[i].y) * (polygon[k].x - clipper[i].x);
            int val2 = (clipper[j].x - clipper[i].x) * (polygon[l].y - clipper[i].y) - 
                       (clipper[j].y - clipper[i].y) * (polygon[l].x - clipper[i].x);

            if (val1 >= 0 && val2 >= 0) {
                temp.push_back(polygon[l]);
            } else if (val1 >= 0 && val2 < 0) {
                temp.push_back(computeIntersection(polygon[k], polygon[l], clipper[i], clipper[j]));
            } else if (val1 < 0 && val2 >= 0) {
                temp.push_back(computeIntersection(polygon[k], polygon[l], clipper[i], clipper[j]));
                temp.push_back(polygon[l]);
            }
        }
        polygon = temp;
    }

    output = polygon;
    return output;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    vector<Point> polygon = {Point(100, 100), Point(300, 100), Point(300, 300), Point(100, 300)};
    vector<Point> clipper = {Point(150, 150), Point(250, 150), Point(250, 250), Point(150, 250)};

    // Perform polygon clipping
    vector<Point> clippedPolygon = sutherlandHodgman(polygon, clipper);

    // Draw clipped polygon
    for (size_t i = 0; i < clippedPolygon.size(); ++i) {
        size_t next = (i + 1) % clippedPolygon.size();
        line(clippedPolygon[i].x, clippedPolygon[i].y, clippedPolygon[next].x, clippedPolygon[next].y);
    }

    getch();
    closegraph();

    return 0;
}
