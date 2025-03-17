#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct RenderWindow
{

      RenderWindow(const char* p_title, int p_w, int p_h);
      SDL_Texture* loadTexture(const char* p_filePath);
      void cleanUp();
      void clear();
      void render(SDL_Texture* p_text);
      void display();

      SDL_Window* window;
      SDL_Renderer* renderer;

};
