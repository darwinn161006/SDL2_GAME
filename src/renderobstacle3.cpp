#include "../include(headerfile)/RenderObstacle3.hpp"
#include <iostream>

RenderObstacle3::RenderObstacle3(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer)
    : x(p_x), y(p_y), size(p_size), baseSpeed(0.01f), renderer(p_renderer), spawnCount(0) {
    spawnTime = SDL_GetTicks();
    texture = IMG_LoadTexture(renderer, "../res/graphic/obstacle3.png");
    if (!texture) {
        std::cerr << "Failed to load obstacle3 texture: " << SDL_GetError() << std::endl;
    }
}

RenderObstacle3::~RenderObstacle3() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void RenderObstacle3::update() {
    y -= baseSpeed;

    if (y + size < 0) {
        y = 720;
        x = rand() % (1280 - size);
        spawnTime = SDL_GetTicks();

        spawnCount++;
        if (spawnCount % 3 == 0) {
            baseSpeed += 0.01f;
            std::cout << "RenderObstacle3 speed increased to: " << baseSpeed << std::endl;
        }
    }
}

void RenderObstacle3::render() {
    if (texture) {
        SDL_Rect obstacleRect = { static_cast<int>(x), static_cast<int>(y), size, size };
        SDL_RenderCopy(renderer, texture, nullptr, &obstacleRect);
    } else {
        std::cerr << "RenderObstacle3: Texture is null!" << std::endl;
    }
}

bool RenderObstacle3::checkCollision(float characterX, float characterY, int characterW, int characterH) {
    return (characterX + characterW > x && characterX < x + size &&
            characterY + characterH > y && characterY < y + size);
}

void RenderObstacle3::reset(float p_x, float p_y) {
    x = p_x;
    y = p_y;
    spawnTime = SDL_GetTicks();
    spawnCount = 0;
    baseSpeed = 0.01f;
    std::cout << "RenderObstacle3 has been reset to position (" << x << ", " << y << ")." << std::endl;
}
