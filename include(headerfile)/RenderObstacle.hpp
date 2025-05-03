#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderObstacle {
public:
    RenderObstacle(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer);
    ~RenderObstacle();

    void update();
    void render();
    bool checkCollision(float characterX, float characterY, int characterW, int characterH);
    void reset(float p_x, float p_y);
    float x, y; // Position

private:
    int size;
    float baseSpeed;       // Base speed of the obstacle
    int spawnCount;        // Number of times the obstacle has spawned
    Uint32 spawnTime;      // Time when the obstacle was spawned

    SDL_Texture* texture;  // Texture for the obstacle
    SDL_Renderer* renderer;
};
