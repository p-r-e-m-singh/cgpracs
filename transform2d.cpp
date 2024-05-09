#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Structure to represent a point
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Function to translate a point by (dx, dy)
void translate(Point& p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
}

// Function to scale a point by (sx, sy) with respect to a fixed point
void scale(Point& p, int sx, int sy, Point fixed) {
    p.x = fixed.x + (p.x - fixed.x) * sx;
    p.y = fixed.y + (p.y - fixed.y) * sy;
}

// Function to rotate a point by angle degrees with respect to a fixed point
void rotate(Point& p, double angle, Point fixed) {
    double rad = angle * M_PI / 180.0;
    int x = p.x - fixed.x;
    int y = p.y - fixed.y;
    p.x = fixed.x + (x * cos(rad) - y * sin(rad));
    p.y = fixed.y + (x * sin(rad) + y * cos(rad));
}

// Function to reflect a point about a line defined by two points A and B
void reflect(Point& p, Point A, Point B) {
    int dx = B.x - A.x;
    int dy = B.y - A.y;
    int x = p.x - A.x;
    int y = p.y - A.y;
    int dist = dx * dx + dy * dy;
    int dot = x * dx + y * dy;
    p.x = A.x + (2 * dot * dx - 2 * dy * (x * dy - y * dx)) / dist;
    p.y = A.y + (2 * dot * dy - 2 * dx * (y * dx - x * dy)) / dist;
}

// Function to draw a polygon
void drawPolygon(const vector<Point>& polygon) {
    for (size_t i = 0; i < polygon.size(); ++i) {
        size_t next = (i + 1) % polygon.size();
        line(polygon[i].x, polygon[i].y, polygon[next].x, polygon[next].y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    vector<Point> original = {{100, 100}, {200, 100}, {200, 200}, {100, 200}};
    vector<Point> transformed = original; // Make a copy for transformations

    int choice;
    do {
        cout << "Choose a transformation:" << endl;
        cout << "1. Translate" << endl;
        cout << "2. Scale" << endl;
        cout << "3. Rotate" << endl;
        cout << "4. Reflect" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int dx, dy;
                cout << "Enter translation factor (dx dy): ";
                cin >> dx >> dy;
                for (auto& p : transformed)
                    translate(p, dx, dy);
                cleardevice();
                drawPolygon(transformed);
                break;
            }
            case 2: {
                int sx, sy;
                Point fixed;
                cout << "Enter scaling factors (sx sy): ";
                cin >> sx >> sy;
                cout << "Enter fixed point (x y): ";
                cin >> fixed.x >> fixed.y;
                for (auto& p : transformed)
                    scale(p, sx, sy, fixed);
                cleardevice();
                drawPolygon(transformed);
                break;
            }
            case 3: {
                double angle;
                Point fixed;
                cout << "Enter angle of rotation (in degrees): ";
                cin >> angle;
                cout << "Enter fixed point (x y): ";
                cin >> fixed.x >> fixed.y;
                for (auto& p : transformed)
                    rotate(p, angle, fixed);
                cleardevice();
                drawPolygon(transformed);
                break;
            }
            case 4: {
                Point A, B;
                cout << "Enter points defining the line (Ax Ay Bx By): ";
                cin >> A.x >> A.y >> B.x >> B.y;
                for (auto& p : transformed)
                    reflect(p, A, B);
                cleardevice();
                drawPolygon(transformed);
                break;
            }
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    closegraph();
    return 0;
}
