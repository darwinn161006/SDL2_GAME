#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include(headerfile)/RenderDuck.hpp"
using namespace std;

RenderDuck::RenderDuck(float p_x, float p_y, int p_w, int p_h, SDL_Texture* p_spritesheet)
    : x(p_x), y(p_y), w(p_w), h(p_h), spritesheet(p_spritesheet), frameIndex(0), frameCount(11),
      frameTime(100),
      timeSinceLastFrame(0) {
    currentFrame = {0, 0, w, h};
}


void RenderDuck::handleInput(SDL_Event& event)
{
      const int screenHeight = 720; // Kích thước màn hình
      int y_min = screenHeight * (1.0 / 8.0);
      int y_max = screenHeight - h; // Đáy màn hình trừ chiều cao vịt

      if(event.type== SDL_KEYDOWN)
      {
            switch(event.key.keysym.sym)
            {
                  case SDLK_UP:
                        if(y- 10>= y_min)
                        {
                           y-= 10;
                        }
                  break;

                  case SDLK_DOWN:
                        if(y+10<=y_max)
                        {
                              y+= 10;
                        }
                  break;
            }
      }
}

void RenderDuck::update()
{
      Uint32 currentTime = SDL_GetTicks();
      Uint32 deltaTime = currentTime - timeSinceLastFrame; // Tính thời gian trôi qua

      if (deltaTime >= frameTime) {
      frameIndex = (frameIndex + 1) % frameCount; // Đảm bảo chạy hết spritesheet rồi lặp lại
      currentFrame.x = frameIndex * w;  // Lấy vị trí frame tiếp theo trong spritesheet
      timeSinceLastFrame = currentTime; // Cập nhật thời gian frame cuối cùng được cập nhật
}
}

void RenderDuck::render(SDL_Renderer* renderer)
{
      if(!spritesheet)
      {
            cerr<<"error"<<endl;
            return;
      }
      SDL_Rect destRect= {static_cast<int>(x),static_cast<int>(y), w, h};
      SDL_RenderCopy(renderer, spritesheet, &currentFrame, &destRect);
}
















