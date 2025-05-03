#include "../include(headerfile)/point.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

Point::Point(SDL_Renderer* renderer)
    : renderer(renderer), score(0) {
    loadDigitTextures();
}

Point::~Point() {
    unloadDigitTextures();
}

void Point::increment() {
    score++;
}

void Point::render(int x, int y) {
    std::string scoreText = std::to_string(score);

    int offsetX = -20; // Offset for positioning digits
    for (char c : scoreText) {
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            renderDigit(digit, x + offsetX, y);
            offsetX += 75; // Space between digits
        }
    }
}

void Point::loadDigitTextures() {
    std::string basePath = "../res/graphic/";

    // Load textures for digits 0-9
    for (int i = 0; i <= 9; ++i) {
        std::string filePath = basePath + std::to_string(i) + ".png";
        SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
        if (!texture) {
            std::cerr << "Failed to load digit texture (" << filePath << "): "
                      << IMG_GetError() << std::endl;
            digitTextures.push_back(nullptr);
            continue;
        }
        digitTextures.push_back(texture);
    }
}

void Point::unloadDigitTextures() {
    for (SDL_Texture* texture : digitTextures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    digitTextures.clear();
}

void Point::renderDigit(int digit, int x, int y) {
    if (digit < 0 || digit > 9 || !digitTextures[digit]) {
        return;
    }

    SDL_Rect destRect = {x, y, 60, 90};
    SDL_RenderCopy(renderer, digitTextures[digit], nullptr, &destRect);
}

// Reset the score to 0
void Point::reset() {
    score = 0;
}
