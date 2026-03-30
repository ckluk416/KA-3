#include "fireworks.h"
#include "line.h"
#include <math.h>

Color GetRandomBrightColor() {
    Color colors[5] = { RED, GOLD, LIME, VIOLET, SKYBLUE };
    return colors[GetRandomValue(0, 4)];
}

void ExplodeFirework(Firework* fw) {
    fw->exploded = true;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        fw->particles[i].active = true;
        fw->particles[i].x = fw->x;
        fw->particles[i].y = fw->y;
        fw->particles[i].prev_x = fw->x;
        fw->particles[i].prev_y = fw->y;
        
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float speed = GetRandomValue(10, 80) / 10.0f; 
        
        fw->particles[i].vx = cos(angle) * speed;
        fw->particles[i].vy = sin(angle) * speed;
        
        fw->particles[i].max_age = (float)GetRandomValue(40, 90);
        fw->particles[i].age = fw->particles[i].max_age;
        fw->particles[i].base_color = fw->color;
    }
}

void UpdateFireworks(Firework fireworks[], int max_fireworks, int screenWidth, int screenHeight) {
    if (GetRandomValue(0, 100) < 3) {
        for (int i = 0; i < max_fireworks; i++) {
            if (!fireworks[i].active) {
                fireworks[i].active = true;
                fireworks[i].exploded = false;
                fireworks[i].x = (float)GetRandomValue(100, screenWidth - 100);
                fireworks[i].y = (float)screenHeight;
                fireworks[i].prev_x = fireworks[i].x;
                fireworks[i].prev_y = fireworks[i].y;
                fireworks[i].vy = (float)GetRandomValue(-85, -60) / 10.0f;
                fireworks[i].color = GetRandomBrightColor();
                break;
            }
        }
    }

    for (int i = 0; i < max_fireworks; i++) {
        if (fireworks[i].active) {
            if (!fireworks[i].exploded) {
                fireworks[i].prev_x = fireworks[i].x;
                fireworks[i].prev_y = fireworks[i].y;
                fireworks[i].y += fireworks[i].vy;
                fireworks[i].vy += GRAVITY; 

                if (fireworks[i].vy >= -1.0f) {
                    ExplodeFirework(&fireworks[i]);
                }
            } else {
                bool hasActiveParticles = false;
                for (int p = 0; p < MAX_PARTICLES; p++) {
                    Particle* prt = &fireworks[i].particles[p];
                    if (prt->active) {
                        hasActiveParticles = true;
                        
                        prt->prev_x = prt->x;
                        prt->prev_y = prt->y;
                        
                        prt->vy += GRAVITY;       
                        prt->vx *= AIR_FRICTION; 
                        prt->vy *= AIR_FRICTION;  
                        
                        prt->x += prt->vx;
                        prt->y += prt->vy;
                        
                        prt->age -= 1.0f;
                        if (prt->age <= 0) prt->active = false;
                    }
                }
                if (!hasActiveParticles) fireworks[i].active = false;
            }
        }
    }
}

void DrawFireworks(Firework fireworks[], int max_fireworks) {
    for (int i = 0; i < max_fireworks; i++) {
        if (fireworks[i].active) {
            if (!fireworks[i].exploded) {
                DrawLineBresenham((int)fireworks[i].prev_x, (int)fireworks[i].prev_y, 
                                  (int)fireworks[i].x, (int)fireworks[i].y, WHITE);
            } else {
                for (int p = 0; p < MAX_PARTICLES; p++) {
                    Particle* prt = &fireworks[i].particles[p];
                    if (prt->active) {
                        float lifeRatio = prt->age / prt->max_age;
                        Color drawColor;
                        
                        if (lifeRatio > 0.8f && GetRandomValue(0, 10) > 7) {
                            drawColor = WHITE;
                        } else {
                            drawColor = prt->base_color;
                        }
                        drawColor.a = (unsigned char)(255 * lifeRatio);

                        DrawLineBresenham((int)prt->prev_x, (int)prt->prev_y, 
                                          (int)prt->x, (int)prt->y, drawColor);
                    }
                }
            }
        }
    }
}