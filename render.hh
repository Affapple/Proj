#include <SDL.h>
#include <stdio.h>
#include <vector>

struct Point {
    double x;
    double y;
};
struct Line
{
    Point start;
    Point end;
};
struct Camera {
    /// @brief Current position of camera
    Point pos;

    /// @brief Direction where camera is pointing
    double direction;
    
    /// @brief Field of View of camera
    double FOV;

    /// @brief Distance of camera to plane of render = SCREEN_HEIGHT/2/tan(fov/2)
    double distanceToPlane;
};

bool initWindow(SDL_Window** window);
void initCamera();
void close(SDL_Window** window);
void addObjects();
void rotateVector(Point* vector, double angle);
double dotProduct(Point v1, Point v2);
Point calculatePerspective(Point p);
void draw(SDL_Renderer** renderer, Line line);
void update(SDL_Window** window,
            SDL_Renderer** renderer);