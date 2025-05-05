#include "../include(headerfile)/RenderObstacle4.hpp"
#include <iostream>

RenderObstacle4::RenderObstacle4(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer)
    : x(p_x), y(p_y), size(p_size), baseSpeed(0.02f), renderer(p_renderer), spawnCount(0) {
    spawnTime = SDL_GetTicks();
    texture = IMG_LoadTexture(renderer, "../res/graphic/obstacle4.png");
    if (!texture) {
        std::cerr << "Failed to load obstacle4 texture: " << SDL_GetError() << std::endl;
    }
}

RenderObstacle4::~RenderObstacle4() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void RenderObstacle4::update() {
    x += baseSpeed;

    if (x > 1280) {
        x = -size;
        y = rand() % (720 - size);
        spawnTime = SDL_GetTicks();

        spawnCount++;
        if (spawnCount % 3 == 0) {
            baseSpeed += 0.01f;
            std::cout << "RenderObstacle4 speed increased to: " << baseSpeed << std::endl;
        }
    }
}

void RenderObstacle4::render() {
    if (texture) {
        SDL_Rect obstacleRect = { static_cast<int>(x), static_cast<int>(y), size, size };
        SDL_RenderCopy(renderer, texture, nullptr, &obstacleRect);
    } else {
        std::cerr << "RenderObstacle4: Texture is null!" << std::endl;
    }
}

bool RenderObstacle4::checkCollision(float characterX, float characterY, int characterW, int characterH) {
    return (characterX + characterW > x && characterX < x + size &&
            characterY + characterH > y && characterY < y + size);
}

void RenderObstacle4::reset(float p_x, float p_y) {
    x = p_x;
    y = p_y;
    spawnTime = SDL_GetTicks();
    spawnCount = 0;
    baseSpeed = 0.02f;
    std::cout << "RenderObstacle4 has been reset to position (" << x << ", " << y << ")." << std::endl;
}
