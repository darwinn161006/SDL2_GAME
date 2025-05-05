#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Timer {
public:
    Timer(SDL_Renderer* renderer);
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();
    bool isPaused();
    void update();
    void render(int x, int y);

private:
    SDL_Renderer* renderer;
    Uint32 startTime;
    Uint32 endTime;
    Uint32 pausedTime;
    Uint32 totalPausedTime;
    bool stopped;
    bool paused;
    std::vector<SDL_Texture*> digitTextures;

    void loadDigitTextures();
    void unloadDigitTextures();
    void renderDigit(int digit, int x, int y);
    std::string formatTime(Uint32 time);
};
