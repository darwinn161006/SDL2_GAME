#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include(headerfile)/RenderWindow.hpp"
#include "../include(headerfile)/RenderDuck.hpp"
#include "../include(headerfile)/RenderObstacle.hpp"
#include "../include(headerfile)/RenderObstacle2.hpp"
#include "../include(headerfile)/RenderObstacle3.hpp"
#include "../include(headerfile)/RenderObstacle4.hpp"
#include "../include(headerfile)/RenderObstacle5.hpp"
#include "../include(headerfile)/RenderObstacle6.hpp"
#include "../include(headerfile)/GameMenu.hpp"
#include "../include(headerfile)/Timer.hpp"
#include "../include(headerfile)/Point.hpp"

using namespace std;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        cout << "SDL_Init has failed. Error: " << SDL_GetError() << endl;
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        cout << "IMG_Init has failed. Error: " << IMG_GetError() << endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    RenderWindow window("DuckRace v1.2", 1280, 720);

    SDL_Texture* grassTexture = window.loadTexture("../res/graphic/background.png");
    SDL_Texture* character1Spritesheet = window.loadTexture("../res/graphic/character1_spritesheet.png");
    SDL_Texture* character2Spritesheet = window.loadTexture("../res/graphic/character2_spritesheet.png");
    SDL_Texture* againButtonTexture = window.loadTexture("../res/graphic/again_button.png");
    SDL_Texture* quitButtonTexture = window.loadTexture("../res/graphic/quit_button.png");
    SDL_Texture* player1WinTexture = window.loadTexture("../res/graphic/player1_win.png");
    SDL_Texture* player2WinTexture = window.loadTexture("../res/graphic/player2_win.png");
    SDL_Texture* pauseTexture = window.loadTexture("../res/pause.png");

    if (!grassTexture || !character1Spritesheet || !character2Spritesheet || !againButtonTexture ||
        !quitButtonTexture || !player1WinTexture || !player2WinTexture || !pauseTexture) {
        cout << "Failed to load one or more textures. Exiting..." << endl;
        return -1;
    }

    Mix_Music* bgMusic = Mix_LoadMUS("../res/background_music.mp3");
    if (bgMusic == nullptr) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    Mix_Chunk* crashedSound = Mix_LoadWAV("../res/crashed_sound.mp3");
    if (crashedSound == nullptr) {
        cout << "Failed to load crashed sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    Mix_Music* gameOverMusic = Mix_LoadMUS("../res/game_over.mp3");
    if (gameOverMusic == nullptr) {
        cout << "Failed to load game over music! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    Mix_PlayMusic(bgMusic, -1);

    RenderDuck character1 = {50, 200, 127, 125, character1Spritesheet, 30};
    RenderDuck character2 = {50, 335, 127, 125, character2Spritesheet, 30};

    RenderObstacle obstacle1 = {1280, rand() % (720 - 150), 100, window.renderer};
    RenderObstacle2 obstacle2 = {rand() % (1280 - 100), -100.0f, 100, window.renderer};
    RenderObstacle3 obstacle3 = {rand() % (1280 - 100), -100.0f, 100, window.renderer};
    RenderObstacle4 obstacle4 = {-100, rand() % (720 - 150), 100, window.renderer};
    RenderObstacle5 obstacle5 = {rand() % (1280 - 100), -100.0f, 100, window.renderer};
    RenderObstacle6 obstacle6 = {rand() % (1280 - 100), -100.0f, 100, window.renderer};

    GameState currentState = MENU;
    GameMenu menu(window.renderer, 1280, 720);

    Timer gameTimer(window.renderer);
    Point pointSystem(window.renderer);
    bool gameRunning = true;
    SDL_Event event;

    Uint32 playStartTime = 0;
    Uint32 lastPointTime = SDL_GetTicks();

    SDL_Rect againButtonRect = {540, 270, 200, 80};
    SDL_Rect quitButtonRect = {540, 380, 200, 80};
    SDL_Rect winMessageRect = {540, 150, 200, 80};
    SDL_Rect pauseRect = {(1280 - 400) / 2, (720 - 200) / 2, 400, 200};

    bool character1Crashed = false;
    bool character2Crashed = false;
    bool isGameOverMusicPlaying = false;
    bool player1CrashedFirst = false;

    while (gameRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }

            if (currentState == MENU) {
                menu.handleEvents(event, currentState);
                if (currentState == PLAYING) {
                    playStartTime = SDL_GetTicks();
                    gameTimer.start();
                }
            } else if (currentState == PLAYING) {
                if (!character1Crashed) character1.handleInput(event, false);
                if (!character2Crashed) character2.handleInput(event, true);

                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    currentState = PAUSED;
                    gameTimer.pause();
                    Mix_PauseMusic();
                    cout << "Game paused!" << endl;
                }
            } else if (currentState == PAUSED) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    currentState = PLAYING;
                    gameTimer.unpause();
                    Mix_ResumeMusic();
                    cout << "Game resumed!" << endl;
                }
            } else if (currentState == GAME_OVER) {
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    if (mouseX >= againButtonRect.x && mouseX <= againButtonRect.x + againButtonRect.w &&
                        mouseY >= againButtonRect.y && mouseY <= againButtonRect.y + againButtonRect.h) {
                        currentState = PLAYING;

                        character1.reset(50, 200);
                        character2.reset(50, 335);
                        obstacle1.reset(1280, rand() % (720 - 150));
                        obstacle2.reset(rand() % (1280 - 100), -100.0f);
                        obstacle3.reset(rand() % (1280 - 100), -100.0f);
                        obstacle4.reset(-100, rand() % (720 - 150));
                        obstacle5.reset(rand() % (1280 - 100), -100.0f);
                        obstacle6.reset(rand() % (1280 - 100), -100.0f);

                        playStartTime = SDL_GetTicks();
                        gameTimer.start();
                        pointSystem.reset();
                        lastPointTime = SDL_GetTicks();

                        character1Crashed = false;
                        character2Crashed = false;
                        player1CrashedFirst = false;

                        Mix_HaltMusic();
                        isGameOverMusicPlaying = false;
                        Mix_PlayMusic(bgMusic, -1);
                        cout << "Game restarted. Obstacles and characters reset." << endl;
                    }

                    if (mouseX >= quitButtonRect.x && mouseX <= quitButtonRect.x + quitButtonRect.w &&
                        mouseY >= quitButtonRect.y && mouseY <= quitButtonRect.y + quitButtonRect.h) {
                        gameRunning = false;
                    }
                }
            }
        }

        window.clear();

        if (currentState == MENU) {
            menu.render();
        } else if (currentState == PLAYING) {
            Uint32 currentTime = SDL_GetTicks();
            Uint32 elapsed = currentTime - playStartTime;

            bool showObstacle1 = elapsed >= 2000;
            bool showObstacle2 = elapsed >= 3000;
            bool showObstacle3 = elapsed >= 4000;
            bool showObstacle4 = elapsed >= 5000;
            bool showObstacle5 = elapsed >= 6000;
            bool showObstacle6 = elapsed >= 7000;

            if (!character1Crashed) character1.update();
            if (!character2Crashed) character2.update();

            if (currentTime - lastPointTime >= 3000) {
                pointSystem.increment();
                lastPointTime = currentTime;
            }

            if (showObstacle1) obstacle1.update();
            if (showObstacle2) obstacle2.update();
            if (showObstacle3) obstacle3.update();
            if (showObstacle4) obstacle4.update();
            if (showObstacle5) obstacle5.update();
            if (showObstacle6) obstacle6.update();

            window.render(grassTexture);

            if (showObstacle1) obstacle1.render();
            if (showObstacle2) obstacle2.render();
            if (showObstacle3) obstacle3.render();
            if (showObstacle4) obstacle4.render();
            if (showObstacle5) obstacle5.render();
            if (showObstacle6) obstacle6.render();

            if (!character1Crashed) character1.render(window.renderer);
            if (!character2Crashed) character2.render(window.renderer);

            gameTimer.render(10, 10);
            pointSystem.render(1100, 10);

            if (!character1Crashed) {
                character1Crashed = obstacle1.checkCollision(character1.getHitbox().x, character1.getHitbox().y,
                                                             character1.getHitbox().w, character1.getHitbox().h) ||
                                    obstacle2.checkCollision(character1.getHitbox().x, character1.getHitbox().y,
                                                             character1.getHitbox().w, character1.getHitbox().h) ||
                                    obstacle3.checkCollision(character1.getHitbox().x, character1.getHitbox().y,
                                                             character1.getHitbox().w, character1.getHitbox().h) ||
                                    obstacle4.checkCollision(character1.getHitbox().x, character1.getHitbox().y,
                                                             character1.getHitbox().w, character1.getHitbox().h) ||
                                    obstacle5.checkCollision(character1.getHitbox().x, character1.getHitbox().y,
                                                             character1.getHitbox().w, character1.getHitbox().h) ||
                                    obstacle6.checkCollision(character1.getHitbox().x, character1.getHitbox().y,
                                                             character1.getHitbox().w, character1.getHitbox().h);
                if (character1Crashed) {
                    Mix_PlayChannel(-1, crashedSound, 0);
                    if (!character2Crashed) player1CrashedFirst = true;
                }
            }

            if (!character2Crashed) {
                character2Crashed = obstacle1.checkCollision(character2.getHitbox().x, character2.getHitbox().y,
                                                             character2.getHitbox().w, character2.getHitbox().h) ||
                                    obstacle2.checkCollision(character2.getHitbox().x, character2.getHitbox().y,
                                                             character2.getHitbox().w, character2.getHitbox().h) ||
                                    obstacle3.checkCollision(character2.getHitbox().x, character2.getHitbox().y,
                                                             character2.getHitbox().w, character2.getHitbox().h) ||
                                    obstacle4.checkCollision(character2.getHitbox().x, character2.getHitbox().y,
                                                             character2.getHitbox().w, character2.getHitbox().h) ||
                                    obstacle5.checkCollision(character2.getHitbox().x, character2.getHitbox().y,
                                                             character2.getHitbox().w, character2.getHitbox().h) ||
                                    obstacle6.checkCollision(character2.getHitbox().x, character2.getHitbox().y,
                                                             character2.getHitbox().w, character2.getHitbox().h);
                if (character2Crashed) {
                    Mix_PlayChannel(-1, crashedSound, 0);
                }
            }

            if (character1Crashed && character2Crashed) {
                if (!isGameOverMusicPlaying) {
                    Mix_HaltMusic();
                    Mix_PlayMusic(gameOverMusic, -1);
                    isGameOverMusicPlaying = true;

                    gameTimer.stop();
                    cout << "Both players crashed! Timer stopped." << endl;
                }
                cout << "Game Over!" << endl;
                currentState = GAME_OVER;
            }
        } else if (currentState == PAUSED) {

            window.render(grassTexture);

            obstacle1.render();
            obstacle2.render();
            obstacle3.render();
            obstacle4.render();
            obstacle5.render();
            obstacle6.render();

            if (!character1Crashed) character1.render(window.renderer);
            if (!character2Crashed) character2.render(window.renderer);

            gameTimer.render(10, 10);
            pointSystem.render(1100, 10);

            SDL_RenderCopy(window.renderer, pauseTexture, nullptr, &pauseRect);
        } else if (currentState == GAME_OVER) {
            window.render(grassTexture);
            obstacle1.render();
            obstacle2.render();
            obstacle3.render();
            obstacle4.render();
            obstacle5.render();
            obstacle6.render();

            if (!character1Crashed) character1.render(window.renderer);
            if (!character2Crashed) character2.render(window.renderer);

            if (player1CrashedFirst) {
                SDL_RenderCopy(window.renderer, player2WinTexture, nullptr, &winMessageRect);
            } else {
                SDL_RenderCopy(window.renderer, player1WinTexture, nullptr, &winMessageRect);
            }

            SDL_RenderCopy(window.renderer, againButtonTexture, nullptr, &againButtonRect);
            SDL_RenderCopy(window.renderer, quitButtonTexture, nullptr, &quitButtonRect);

            gameTimer.render(10, 10);
            pointSystem.render(1100, 10);
        }

        window.display();
    }

    Mix_FreeMusic(bgMusic);
    Mix_FreeChunk(crashedSound);
    Mix_FreeMusic(gameOverMusic);
    Mix_CloseAudio();

    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(character1Spritesheet);
    SDL_DestroyTexture(character2Spritesheet);
    SDL_DestroyTexture(againButtonTexture);
    SDL_DestroyTexture(quitButtonTexture);
    SDL_DestroyTexture(player1WinTexture);
    SDL_DestroyTexture(player2WinTexture);
    SDL_DestroyTexture(pauseTexture);

    window.cleanUp();
    SDL_Quit();

    return 0;
}
