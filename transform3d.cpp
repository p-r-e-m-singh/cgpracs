#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Structure to represent a 3D point
struct Point3D {
    double x, y, z;
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

// Function to translate a 3D point by (dx, dy, dz)
void translate(Point3D& p, double dx, double dy, double dz) {
    p.x += dx;
    p.y += dy;
    p.z += dz;
}

// Function to scale a 3D point by (sx, sy, sz) with respect to a fixed point
void scale(Point3D& p, double sx, double sy, double sz, Point3D fixed) {
    p.x = fixed.x + (p.x - fixed.x) * sx;
    p.y = fixed.y + (p.y - fixed.y) * sy;
    p.z = fixed.z + (p.z - fixed.z) * sz;
}

// Function to rotate a 3D point by angle degrees around the x-axis
void rotateX(Point3D& p, double angle) {
    double rad = angle * M_PI / 180.0;
    double y = p.y;
    double z = p.z;
    p.y = y * cos(rad) - z * sin(rad);
    p.z = y * sin(rad) + z * cos(rad);
}

// Function to rotate a 3D point by angle degrees around the y-axis
void rotateY(Point3D& p, double angle) {
    double rad = angle * M_PI / 180.0;
    double x = p.x;
    double z = p.z;
    p.x = x * cos(rad) + z * sin(rad);
    p.z = -x * sin(rad) + z * cos(rad);
}

// Function to rotate a 3D point by angle degrees around the z-axis
void rotateZ(Point3D& p, double angle) {
    double rad = angle * M_PI / 180.0;
    double x = p.x;
    double y = p.y;
    p.x = x * cos(rad) - y * sin(rad);
    p.y = x * sin(rad) + y * cos(rad);
}

// Function to perform parallel projection
Point3D parallelProjection(Point3D p, double d) {
    return Point3D(p.x, p.y, d);
}

// Function to perform perspective projection
Point3D perspectiveProjection(Point3D p, double d) {
    return Point3D(p.x / (1 + p.z / d), p.y / (1 + p.z / d), p.z);
}

// Function to draw a 3D object
void drawObject(const vector<Point3D>& object) {
    for (size_t i = 0; i < object.size(); ++i) {
        size_t next = (i + 1) % object.size();
        line(object[i].x, object[i].y, object[next].x, object[next].y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    vector<Point3D> original = {{100, 100, 100}, {200, 100, 100}, {200, 200, 100}, {100, 200, 100},
                                {100, 100, 200}, {200, 100, 200}, {200, 200, 200}, {100, 200, 200}};
    vector<Point3D> transformed = original; // Make a copy for transformations

    int choice;
    do {
        cout << "Choose a transformation:" << endl;
        cout << "1. Translate" << endl;
        cout << "2. Scale" << endl;
        cout << "3. Rotate X-axis" << endl;
        cout << "4. Rotate Y-axis" << endl;
        cout << "5. Rotate Z-axis" << endl;
        cout << "6. Parallel Projection" << endl;
        cout << "7. Perspective Projection" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double dx, dy, dz;
                cout << "Enter translation factors (dx dy dz): ";
                cin >> dx >> dy >> dz;
                for (auto& p : transformed)
                    translate(p, dx, dy, dz);
                break;
            }
            case 2: {
                double sx, sy, sz;
                Point3D fixed;
                cout << "Enter scaling factors (sx sy sz): ";
                cin >> sx >> sy >> sz;
                cout << "Enter fixed point (x y z): ";
                cin >> fixed.x >> fixed.y >> fixed.z;
                for (auto& p : transformed)
                    scale(p, sx, sy, sz, fixed);
                break;
            }
            case 3: {
                double angle;
                cout << "Enter angle of rotation around X-axis (in degrees): ";
                cin >> angle;
                for (auto& p : transformed)
                    rotateX(p, angle);
                break;
            }
            case 4: {
                double angle;
                cout << "Enter angle of rotation around Y-axis (in degrees): ";
                cin >> angle;
                for (auto& p : transformed)
                    rotateY(p, angle);
                break;
            }
            case 5: {
                double angle;
                cout << "Enter angle of rotation around Z-axis (in degrees): ";
                cin >> angle;
                for (auto& p : transformed)
                    rotateZ(p, angle);
                break;
            }
            case 6: {
                double d_parallel;
                cout << "Enter distance for parallel projection: ";
                cin >> d_parallel;
                for (auto& p : transformed)
                    p = parallelProjection(p, d_parallel);
                break;
            }
            case 7: {
                double d_perspective;
                cout << "Enter distance for perspective projection: ";
                cin >> d_perspective;
                for (auto& p : transformed)
                    p = perspectiveProjection(p, d_perspective);
                break;
            }
            case 8:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        // Clear the screen
        cleardevice();

        // Draw the transformed object
        drawObject(transformed);

        // Delay for visualization
        delay(1000);

    } while (choice != 8);

    closegraph();
    return 0;
}
