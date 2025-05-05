#include "../include(headerfile)/Timer.hpp"
#include <iostream>
#include <sstream>
#include <SDL2/SDL_image.h>

Timer::Timer(SDL_Renderer* renderer)
    : renderer(renderer), startTime(0), endTime(0), stopped(false), pausedTime(0), paused(false), totalPausedTime(0) {
    loadDigitTextures();
}

Timer::~Timer() {
    unloadDigitTextures();
}

void Timer::start() {
    startTime = SDL_GetTicks();
    stopped = false;
    paused = false;
    totalPausedTime = 0;
}

void Timer::stop() {
    if (!stopped) {
        endTime = SDL_GetTicks();
        stopped = true;
    }
}

void Timer::pause() {
    if (!stopped && !paused) {
        pausedTime = SDL_GetTicks();
        paused = true;
    }
}

void Timer::unpause() {
    if (paused) {
        totalPausedTime += (SDL_GetTicks() - pausedTime);
        paused = false;
    }
}

bool Timer::isPaused() {
    return paused;
}

void Timer::update() {

}

void Timer::render(int x, int y) {
    Uint32 timeToShow;

    if (stopped) {
        timeToShow = endTime - startTime;
    } else if (paused) {
        timeToShow = pausedTime - startTime - totalPausedTime;
    } else {
        timeToShow = SDL_GetTicks() - startTime - totalPausedTime;
    }

    std::string timeText = formatTime(timeToShow);
    int offsetX = 0;

    for (char c : timeText) {
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            renderDigit(digit, x + offsetX, y);
            offsetX += 75;
        } else if (c == ':') {

        }
    }
}

void Timer::loadDigitTextures() {
    std::string basePath = "../res/graphic/";
    for (int i = 0; i <= 9; ++i) {
        std::string filePath = basePath + std::to_string(i) + ".png";
        SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
        if (!texture) {
            std::cerr << "Failed to load digit texture (" << filePath << "): "
                      << IMG_GetError() << std::endl;
            digitTextures.push_back(nullptr);
        } else {
            digitTextures.push_back(texture);
        }
    }
}

void Timer::unloadDigitTextures() {
    for (SDL_Texture* texture : digitTextures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    digitTextures.clear();
}

void Timer::renderDigit(int digit, int x, int y) {
    if (digit < 0 || digit > 9 || !digitTextures[digit]) {
        return;
    }
    SDL_Rect destRect = {x, y, 60, 90};
    SDL_RenderCopy(renderer, digitTextures[digit], nullptr, &destRect);
}

std::string Timer::formatTime(Uint32 time) {
    Uint32 seconds = (time / 1000) % 60;
    Uint32 minutes = (time / 60000);
    std::ostringstream oss;
    oss << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    return oss.str();
}
