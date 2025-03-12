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
