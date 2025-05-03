#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Timer {
public:
    Timer(SDL_Renderer* renderer);
    ~Timer();

    void start();
    void update();
    void render(int x, int y);
    void stop();
    void reset();
    bool isStopped() const;

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> digitTextures;
    SDL_Texture* colonTexture;

    Uint32 startTime;
    Uint32 endTime;
    bool stopped;

    void loadDigitTextures();
    void unloadDigitTextures();
    void loadColonTexture();
    void unloadColonTexture();
    void renderDigit(int digit, int x, int y);
    std::string formatTime(Uint32 time);
};
