#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include(headerfile)/RenderWindow.hpp"
using namespace std;

RenderWindow :: RenderWindow(const char* p_title, int p_w, int p_h)
      :window(NULL), renderer(NULL)
{
      window= SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, SDL_WINDOW_SHOWN);
      if(window== NULL)
         {
               cout<<"Can not initialize. Error: "<<SDL_GetError()<<endl;
         }

      renderer= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


}

void RenderWindow::cleanUp()
{
      SDL_DestroyWindow(window);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
      SDL_Texture* texture= NULL;
      texture = IMG_LoadTexture(renderer, p_filePath);
      if(texture== NULL)
      {
            cout<<"Can not load texture. Error: "<<SDL_GetError()<<endl;
      }
      return texture;
}

void RenderWindow::clear()
{
      SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_text)
{
      SDL_RenderCopy(renderer, p_text, NULL, NULL);
}

void RenderWindow::display()
{
      SDL_RenderPresent(renderer);
}
