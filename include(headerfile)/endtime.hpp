#ifndef ENDTIME_HPP
#define ENDTIME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class EndTime {
private:
    SDL_Texture* digitTextures[10]; // Textures for digits 0-9
    SDL_Renderer* renderer;         // Renderer for displaying textures
    int elapsedTime;                // Time played in seconds

public:
    EndTime(SDL_Renderer* renderer);
    ~EndTime();

    void setElapsedTime(int milliseconds); // Set elapsed time in milliseconds
    void renderTime(int x, int y);         // Render the time on the screen at position (x, y)
};

#endif
