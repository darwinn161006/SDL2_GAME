#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include(headerfile)/RenderDuck.hpp"

using namespace std;

RenderDuck::RenderDuck(float p_x, float p_y, int p_w, int p_h, SDL_Texture* p_spritesheet, int p_hitbox_margin)
    : x(p_x), y(p_y), w(p_w), h(p_h), spritesheet(p_spritesheet), frameIndex(0), frameCount(11),
      frameTime(150), timeSinceLastFrame(0), prevX(p_x), prevY(p_y), hitbox_margin(p_hitbox_margin) {
    currentFrame = {0, 0, w, h};
}

void RenderDuck::handleInput(SDL_Event& event, bool isPlayerTwo) {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int y_max = screenHeight - h+ 50; // Lower boundary
    int y_min = 100;               // Upper boundary
    int x_max = screenWidth - w; // Right boundary
    int x_min = 0;               // Left boundary

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            // Movement keys for Player Two (WASD)
            case SDLK_w:
                if (isPlayerTwo && y - 100 >= y_min) {
                    y -= 100; // Move up
                }
                break;

            case SDLK_s:
                if (isPlayerTwo && y + 100 <= y_max) {
                    y += 100; // Move down
                }
                break;

            case SDLK_a:
                if (isPlayerTwo && x - 100 >= x_min) {
                    x -= 100; // Move left
                }
                break;

            case SDLK_d:
                if (isPlayerTwo && x + 100 <= x_max) {
                    x += 100; // Move right
                }
                break;

            // Movement keys for Player One (Arrow keys)
            case SDLK_UP:
                if (!isPlayerTwo && y - 100 >= y_min) {
                    y -= 100; // Move up
                }
                break;

            case SDLK_DOWN:
                if (!isPlayerTwo && y + 100 <= y_max) {
                    y += 100; // Move down
                }
                break;

            case SDLK_LEFT:
                if (!isPlayerTwo && x - 100 >= x_min) {
                    x -= 100; // Move left
                }
                break;

            case SDLK_RIGHT:
                if (!isPlayerTwo && x + 100 <= x_max) {
                    x += 100; // Move right
                }
                break;

            default:
                break;
        }
    }
}

void RenderDuck::update() {
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - timeSinceLastFrame >= frameTime) {
        frameIndex = (frameIndex + 1) % frameCount;
        currentFrame.x = frameIndex * w;
        timeSinceLastFrame = currentTime;
    }
}

void RenderDuck::render(SDL_Renderer* renderer) {
    if (!spritesheet) {
        cerr << "Error: No spritesheet loaded for RenderDuck." << endl;
        return;
    }
    SDL_Rect destRect = {
        static_cast<int>(x), static_cast<int>(y), w, h
    };
    SDL_RenderCopy(renderer, spritesheet, &currentFrame, &destRect);
}

SDL_Rect RenderDuck::getHitbox() const {
    return {
        static_cast<int>(x) + hitbox_margin,
        static_cast<int>(y) + hitbox_margin,
        static_cast<int>(w) - 3 * hitbox_margin,
        static_cast<int>(h) - 3 * hitbox_margin
    };
}

void RenderDuck::reset(float newX, float newY) {
    x = newX;
    y = newY;
    prevX = newX;
    prevY = newY;
    frameIndex = 0;
    timeSinceLastFrame = 0;
}
