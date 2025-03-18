#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include(headerfile)/RenderWindow.hpp"
#include "../include(headerfile)/RenderDuck.hpp"
#include "../include(headerfile)/RenderObstacle.hpp"
using namespace std;

int main(int argc, char* args[])
{
    // Kiểm tra SDL và IMG
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL_Init has failed. Error: " << SDL_GetError() << endl;
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        cout << "IMG_Init has failed. Error: " << IMG_GetError() << endl;
        return -1;
    }

    // Khởi tạo cửa sổ render
    RenderWindow window("DuckRace v1.0", 1280, 720);

    // Tải ảnh nền
    SDL_Texture* grassTexture = window.loadTexture("../res/graphic/background.png");
    SDL_Texture* characterSpritesheet = window.loadTexture("../res/graphic/ducksheet.png");

    // Tạo nhân vật với kích thước nhỏ hơn (ví dụ 117x100)
    RenderDuck character = {50, 200, 234, 199, characterSpritesheet};

    // Tạo chướng ngại vật với kích thước lớn hơn (ví dụ 100x100)
    RenderObstacle obstacle = {1280, rand() % (720 - 150), 150, window.renderer};
    bool gameRunning = true;
    SDL_Event event;

    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            character.handleInput(event);
        }
        character.update();

        // Cập nhật màn hình
        window.clear();
        window.render(grassTexture);

        // Vẽ chướng ngại vật và nhân vật
        obstacle.update();
        obstacle.render();
        character.render(window.renderer);

        // Kiểm tra va chạm
        if (obstacle.checkCollision(character.x, character.y, character.w, character.h))
        {
            cout << "Game Over!" << endl;
            gameRunning = false;
        }

        window.display();
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}
