#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include(headerfile)/RenderWindow.hpp"
#include "../include(headerfile)/RenderDuck.hpp"
using namespace std;

int main(int argc, char* args[])
{
      //Kiểm tra xem có hoạt động bình thường ko
      if(SDL_Init(SDL_INIT_VIDEO)>0)
      {
            cout<<"SDL_Init has failed. Error: "<<SDL_GetError()<<endl;
      }

      if(!(IMG_Init(IMG_INIT_PNG)))
      {
            cout<<"IMG_Init has failed. Error: "<<IMG_GetError()<<endl;
      }

      //Bắt đầu render cửa sổ
      RenderWindow window("DuckRace v1.0", 1280, 720);


      //Render background
      SDL_Texture* grassTexture = window.loadTexture("../res/graphic/background.png");
      SDL_Texture* characterSpritesheet = window.loadTexture("../res/graphic/ducksheet.png");

      RenderDuck character(640, 380, 234, 199, characterSpritesheet);

      //Kiểm soát việc xóa cửa sổ
      bool gameRunning= true;

      SDL_Event event;

      while(gameRunning)
      {
            while(SDL_PollEvent(&event))
            {
                  if(event.type== SDL_QUIT)
                  {
                        gameRunning= false;
                  }
                  character.handleInput(event);
            }
            character.update();
            window.clear();
            window.render(grassTexture);
            character.render(window.renderer);

            window.display();
      }


      window.cleanUp();
      SDL_Quit();
      return 0;
}
