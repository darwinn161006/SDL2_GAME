#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct RenderDuck
{
    RenderDuck(float p_x, float p_y, int p_w, int p_h, SDL_Texture* p_spritesheet, int p_hitbox_margin = 20);
    void handleInput(SDL_Event& event, bool isPlayerTwo);
    void update();
    void render(SDL_Renderer* renderer);

    SDL_Rect getHitbox() const;

    float prevX, prevY;
    float x, y;
    int w, h;
    SDL_Texture* spritesheet;
    SDL_Rect currentFrame;
    int frameIndex;
    int frameCount;
    int frameTime;
    int timeSinceLastFrame;
    void reset(float newX, float newY);
    int hitbox_margin;
};
