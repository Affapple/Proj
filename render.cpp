#include "render.hh"
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int POV = 90;
const double PI = SDL_acos(-1);

Camera camera;
std::vector<Line> listObjects;

void initCamera() {
    camera.pos = {0, 0};
    camera.direction = 0;
    camera.FOV = PI/3;
    camera.distanceToPlane = SCREEN_HEIGHT / 2 / SDL_tan(camera.FOV / 2);
}

bool initWindow(SDL_Window** window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initalize SDL! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }
    *window = SDL_CreateWindow(
            "SDL tutorial", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN
        );

    if (*window == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }    

    return true;
}


void update(SDL_Window** window,
            SDL_Renderer** renderer) {
    for (int i = 0; i < listObjects.size(); i++) {
        Line line = listObjects[i];
        draw(renderer, line);
    }
    //Update Screen
    SDL_RenderPresent(*renderer);
}

void draw(SDL_Renderer** renderer, Line line) {
    Point povStart = calculatePerspective(line.start);
    Point povEnd = calculatePerspective(line.end);
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    int output = SDL_RenderDrawLine(*renderer, povStart.x, povStart.y,
                                  povEnd.x, povEnd.y);
    if (output != 0) {
        printf("Error: %s", SDL_GetError());
    }
}

Point calculatePerspective(Point p) {
    Point point = {.x = 0, .y = SCREEN_HEIGHT/2};

    Point camToPoint = Point{
        .x = p.x - camera.pos.x,
        .y = p.y - camera.pos.y
    };

    Point vector = Point {
        .x = camera.distanceToPlane / SDL_cos(camera.FOV/2),
        .y = 0,
    };
    rotateVector(&vector, camera.direction - camera.FOV/2);
    Point camScreenRight = Point{
        .x = camera.pos.x + vector.x,
        .y = camera.pos.y + vector.y
    };

    double v1Length = SDL_sqrt(dotProduct(camToPoint, camToPoint));
    double v2Length = SDL_sqrt(dotProduct(camScreenRight, camScreenRight));
    double cosineAngle = dotProduct(camToPoint, camScreenRight) / (v1Length * v2Length); 
    double angle = SDL_acos(
        cosineAngle
    );
    point.x = SCREEN_WIDTH - (
                                camera.distanceToPlane
                                / SDL_cos(camera.FOV/2)
                             )
                             * SDL_sin(angle) 
                             / SDL_sin(PI/2 + camera.FOV/2 - angle);
    return point;
}


double dotProduct(Point v1, Point v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

void rotateVector(Point* vector, double angle) {
    int x = vector->x;
    int y = vector->y;

    vector->x = x * SDL_cos(angle) - y * SDL_sin(angle);
    vector->y = x * SDL_sin(angle) + y * SDL_cos(angle);
}

void addObjects() {
    Line l1 = Line {
        .start = Point {
            .x = 800,
            .y = 300
        },
        .end = Point {
            .x = 800,
            .y = 400
        }
    };
    Line l2 = Line {
        .start = Point {
            .x = 800,
            .y = -400
        },
        .end = Point {
            .x = 900,
            .y = -200
        }
    };
    listObjects.push_back(l1);
    listObjects.push_back(l2);
}

void close(SDL_Window** window) {
    SDL_DestroyWindow(*window);
    SDL_Quit();
}