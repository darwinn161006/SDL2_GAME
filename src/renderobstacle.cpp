#include "../include(headerfile)/RenderObstacle.hpp"
#include <iostream>


RenderObstacle::RenderObstacle(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer)
    : x(p_x), y(p_y), size(p_size), baseSpeed(0.01f), renderer(p_renderer), spawnCount(0) {
    spawnTime = SDL_GetTicks();
    texture = IMG_LoadTexture(renderer, "../res/graphic/obstacle.png");
    if (!texture) {
        std::cerr << "Failed to load obstacle texture: " << SDL_GetError() << std::endl;
    }
}


RenderObstacle::~RenderObstacle() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}


void RenderObstacle::update() {
    x -= baseSpeed;


    if (x + size < 0) {
        x = 1280;
        y = rand() % (720 - size);
        spawnTime = SDL_GetTicks();

        spawnCount++;
        if (spawnCount % 3 == 0) {
            baseSpeed += 0.01f;
            std::cout << "RenderObstacle speed increased to: " << baseSpeed << std::endl;
        }
    }
}


void RenderObstacle::render() {
    if (texture) {
        SDL_Rect obstacleRect = { static_cast<int>(x), static_cast<int>(y), size, size };
        SDL_RenderCopy(renderer, texture, nullptr, &obstacleRect);
    } else {
        std::cerr << "RenderObstacle: Texture is null!" << std::endl;
    }
}

bool RenderObstacle::checkCollision(float characterX, float characterY, int characterW, int characterH) {
    return (characterX + characterW > x && characterX < x + size &&
            characterY + characterH > y && characterY < y + size);
}


void RenderObstacle::reset(float p_x, float p_y) {
    x = p_x;
    y = p_y;
    spawnTime = SDL_GetTicks();
    spawnCount = 0;
    baseSpeed = 0.01f;
    std::cout << "RenderObstacle has been reset to position (" << x << ", " << y << ")." << std::endl;
}
