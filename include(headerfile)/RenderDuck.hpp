#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderDuck
{
public:
      RenderDuck(float p_x, float p_y, int p_w, int p_h, SDL_Texture* p_spritesheet);
      void handleInput(SDL_Event& event);
      void update();
      void render(SDL_Renderer* renderer);

private:
      float x, y; //Day la vi tri cua DUCK
      int w, h; //Day la kich thuoc cua DUCK
      SDL_Texture* spritesheet; //Day la spritesheet cua DUCK
      SDL_Rect currentFrame; //Frame hien tai cua nhan vat
      int frameIndex; //Chi so frame hien tai
      int frameCount; //Tong so frame hien co
};

