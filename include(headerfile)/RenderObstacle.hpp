#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct RenderObstacle
{
    float x, y;        // Vị trí của chướng ngại vật
    int size;          // Kích thước của chướng ngại vật
    float speed;       // Tốc độ di chuyển
    SDL_Texture* texture;  // Ảnh của chướng ngại vật
    SDL_Renderer* renderer; // Thêm renderer vào đối tượng

    // Constructor
    RenderObstacle(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer);

    void update();
    void render();
    bool checkCollision(float characterX, float characterY, int characterW, int characterH);
};
