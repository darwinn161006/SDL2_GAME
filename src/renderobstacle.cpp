#include "../include(headerfile)/RenderObstacle.hpp"
#include <iostream>

RenderObstacle::RenderObstacle(float p_x, float p_y, int p_size, SDL_Renderer* p_renderer)
    : x(p_x), y(p_y), size(p_size), speed(0.15f), renderer(p_renderer)  // Khởi tạo các giá trị ban đầu
{
    // Tải ảnh chướng ngại vật từ file PNG
    texture = IMG_LoadTexture(renderer, "../res/graphic/obstacle.png");  // Sử dụng renderer từ đối tượng
    if (texture == nullptr) {
        std::cerr << "Failed to load obstacle texture: " << SDL_GetError() << std::endl;
    }
}

void RenderObstacle::update()
{
    x -= speed;  // Di chuyển chướng ngại vật từ phải sang trái

    // Nếu chướng ngại vật ra ngoài màn hình thì quay lại bên phải
    if (x + size < 0) {
        x = 1280;  // Tạo lại chướng ngại vật ở bên phải màn hình
        y = rand() % (720 - size);  // Đặt vị trí y ngẫu nhiên trong màn hình
    }
}

void RenderObstacle::render()
{
    if (texture) {
        // Tạo hình chữ nhật cho chướng ngại vật
        SDL_Rect obstacleRect = { static_cast<int>(x), static_cast<int>(y), size, size };

        // Vẽ ảnh chướng ngại vật
        SDL_RenderCopy(renderer, texture, nullptr, &obstacleRect);
    }
}

bool RenderObstacle::checkCollision(float characterX, float characterY, int characterW, int characterH)
{
    // Kiểm tra va chạm giữa chướng ngại vật và nhân vật
    if (characterX + characterW > x && characterX < x + size &&
        characterY + characterH > y && characterY < y + size) {
        return true;  // Va chạm
    }
    return false;  // Không va chạm
}
