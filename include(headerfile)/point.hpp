
#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Point {
public:
    Point(SDL_Renderer* renderer);
    ~Point();

    void increment(); // Increments the score by 1
    void render(int x, int y);
    void reset();

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> digitTextures;
    int score;

    void loadDigitTextures();
    void unloadDigitTextures();
    void renderDigit(int digit, int x, int y);
};
