#include "../include(headerfile)/GameMenu.hpp"

GameMenu::GameMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      titleTexture(nullptr), backgroundTexture(nullptr),
      startButtonTexture(nullptr), quitButtonTexture(nullptr)
{
    // Load textures
    backgroundTexture = IMG_LoadTexture(renderer, "../res/graphic/background.png");
    if (!backgroundTexture) {
        std::cout << "Failed to load menu background: " << SDL_GetError() << std::endl;
    }


    titleTexture = IMG_LoadTexture(renderer, "../res/graphic/title.png");
    startButtonTexture = IMG_LoadTexture(renderer, "../res/graphic/start_button.png");
    quitButtonTexture = IMG_LoadTexture(renderer, "../res/graphic/quit_button.png");



      titleRect = {screenWidth / 2 - 300, 80, 600, 150};


      startButtonRect = {screenWidth / 2 - 150, 270, 300, 80};


      quitButtonRect = {screenWidth / 2 - 150, 380, 300, 80};
}

GameMenu::~GameMenu() {
    // Clean up textures
    if (titleTexture) SDL_DestroyTexture(titleTexture);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (startButtonTexture) SDL_DestroyTexture(startButtonTexture);
    if (quitButtonTexture) SDL_DestroyTexture(quitButtonTexture);
}

void GameMenu::handleEvents(SDL_Event& event, GameState& currentState) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // Check if start button was clicked
        if (mouseX >= startButtonRect.x && mouseX <= startButtonRect.x + startButtonRect.w &&
            mouseY >= startButtonRect.y && mouseY <= startButtonRect.y + startButtonRect.h) {
            currentState = PLAYING;
        }

        // Check if quit button was clicked
        if (mouseX >= quitButtonRect.x && mouseX <= quitButtonRect.x + quitButtonRect.w &&
            mouseY >= quitButtonRect.y && mouseY <= quitButtonRect.y + quitButtonRect.h) {
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
        }
    }
}

void GameMenu::render() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render background
    if (backgroundTexture) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    // Render title
    if (titleTexture) {
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    }

    // Render buttons
    if (startButtonTexture) {
        SDL_RenderCopy(renderer, startButtonTexture, NULL, &startButtonRect);
    }

    if (quitButtonTexture) {
        SDL_RenderCopy(renderer, quitButtonTexture, NULL, &quitButtonRect);
    }
}
