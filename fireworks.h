#ifndef FIREWORKS_H
#define FIREWORKS_H

#include "raylib.h"

#define MAX_PARTICLES 600
#define MAX_FIREWORKS 5
#define GRAVITY 0.05f
#define AIR_FRICTION 0.95f

typedef struct {
    float x, y;
    float prev_x, prev_y;
    float vx, vy;
    float age;
    float max_age;
    Color base_color;
    bool active;
} Particle;

typedef struct {
    float x, y;
    float prev_x, prev_y;
    float vy;
    Color color;
    bool exploded;
    bool active;
    Particle particles[MAX_PARTICLES];
} Firework;

void UpdateFireworks(Firework fireworks[], int max_fireworks, int screenWidth, int screenHeight);
void DrawFireworks(Firework fireworks[], int max_fireworks);

#endif