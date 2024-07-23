#include <SDL2/SDL.h>
#include <stdbool.h>
#include <vector>
class Screen {
    SDL_Window *window;
    SDL_Renderer *render;

    std::vector<SDL_FPoint> points;
    SDL_Event e;

    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(640*2, 480*2, SDL_WINDOW_RESIZABLE, &window, &render);
        SDL_RenderSetScale(render, 2, 2);
    }

    
}