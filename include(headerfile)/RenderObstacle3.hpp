#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderObstacle3 {
public:
    RenderObstacle3(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer);
    ~RenderObstacle3();

    void update();
    void render();
    bool checkCollision(float characterX, float characterY, int characterW, int characterH);
    void reset(float p_x, float p_y);
    float x, y;

private:

    int size;
    float baseSpeed;
    int spawnCount;
    Uint32 spawnTime;

    SDL_Texture* texture;
    SDL_Renderer* renderer;
};
