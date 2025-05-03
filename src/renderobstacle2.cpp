#include "../include(headerfile)/RenderObstacle2.hpp"
#include <iostream>


RenderObstacle2::RenderObstacle2(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer)
    : x(p_x), y(p_y), size(p_size), baseSpeed(0.01f), renderer(p_renderer), spawnCount(0) {
    spawnTime = SDL_GetTicks();
    texture = IMG_LoadTexture(renderer, "../res/graphic/obstacle2.jpg");
    if (!texture) {
        std::cerr << "Failed to load obstacle2 texture: " << SDL_GetError() << std::endl;
    }
}


RenderObstacle2::~RenderObstacle2() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}


void RenderObstacle2::update() {
    Uint32 currentTime = SDL_GetTicks();
    float elapsedSeconds = (currentTime - spawnTime) / 1000.0f;

    y += baseSpeed;


    if (y > 720) {
        y = -size;
        x = rand() % (1280 - size);
        spawnTime = SDL_GetTicks();

        spawnCount++;
        if (spawnCount % 3 == 0) {
            baseSpeed += 0.01f;
            std::cout << "RenderObstacle2 speed increased to: " << baseSpeed << std::endl;
        }
    }
}


void RenderObstacle2::render() {
    if (texture) {
        SDL_Rect obstacleRect = { static_cast<int>(x), static_cast<int>(y), size, size };
        SDL_RenderCopy(renderer, texture, nullptr, &obstacleRect);
    } else {
        std::cerr << "RenderObstacle2: Texture is null!" << std::endl;
    }
}


bool RenderObstacle2::checkCollision(float characterX, float characterY, int characterW, int characterH) {
    return (characterX + characterW > x && characterX < x + size &&
            characterY + characterH > y && characterY < y + size);
}


void RenderObstacle2::reset(float p_x, float p_y) {
    x = p_x;
    y = p_y;
    spawnTime = SDL_GetTicks();
    spawnCount = 0;
    baseSpeed = 0.01f;
    std::cout << "RenderObstacle2 has been reset to position (" << x << ", " << y << ")." << std::endl;
}
