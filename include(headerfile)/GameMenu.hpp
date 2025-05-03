
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>

// Define game states
enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class GameMenu {
public:
    GameMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~GameMenu();

    void handleEvents(SDL_Event& event, GameState& currentState);
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* titleTexture;
    SDL_Texture* backgroundTexture;
    SDL_Texture* startButtonTexture;
    SDL_Texture* quitButtonTexture;

    SDL_Rect titleRect;
    SDL_Rect startButtonRect;
    SDL_Rect quitButtonRect;

    int screenWidth;
    int screenHeight;
};
