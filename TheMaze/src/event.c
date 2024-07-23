#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Event e;
    // initializing a rectangle box
    //  the first and second integer are the x and y co-ordinates of the rectangle
    //  the third and second integers are the width and height respectively
    SDL_Rect r = {10, 10, 200, 200};
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;

    SDL_CreateWindowAndRenderer(1280, 740, 0, &window, &render);

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_a:
                        r.x += 10;
                        break;
                    case SDLK_1:    printf("key 1 was pressed\n"); break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_a:
                        printf("the key a was released\n");
                        break;
                }
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&r.x, &r.y);
            }
        }
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &r);
        SDL_RenderPresent(render);

        SDL_Delay(10);
    }

    return 0;
}
