#include "../include(headerfile)/endtime.hpp"
#include <iostream>
#include <string>

EndTime::EndTime(SDL_Renderer* renderer) : renderer(renderer), elapsedTime(0) {
    // Load textures for digits (0.png, 1.png, ..., 9.png) located in the res folder
    for (int i = 0; i < 10; ++i) {
        std::string path = "../res/" + std::to_string(i) + ".png";
        digitTextures[i] = IMG_LoadTexture(renderer, path.c_str());
        if (!digitTextures[i]) {
            std::cerr << "Failed to load texture for digit " << i << ": " << SDL_GetError() << std::endl;
        }
    }
}

EndTime::~EndTime() {
    // Free digit textures
    for (int i = 0; i < 10; ++i) {
        if (digitTextures[i]) {
            SDL_DestroyTexture(digitTextures[i]);
        }
    }
}

void EndTime::setElapsedTime(int milliseconds) {
    elapsedTime = milliseconds / 1000; // Convert milliseconds to seconds
}

void EndTime::renderTime(int x, int y) {
    std::string timeStr = std::to_string(elapsedTime); // Convert time to string
    int digitWidth = 50;  // Width of each digit
    int digitHeight = 100; // Height of each digit
    int spacing = 10;      // Spacing between digits

    for (char c : timeStr) {
        int digit = c - '0'; // Convert character '0'-'9' to integer
        SDL_Rect dstRect = {x, y, digitWidth, digitHeight};
        SDL_RenderCopy(renderer, digitTextures[digit], nullptr, &dstRect);
        x += digitWidth + spacing; // Move to the next digit position
    }
}
