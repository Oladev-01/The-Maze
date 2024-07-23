#include <SDL2/SDL.h>
/**
 * main - printing a pixel on the window
 */

int main()
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1000, 700, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, 1000 / 2, 700 / 2);
	SDL_RenderPresent(renderer);
	SDL_Delay(20000);

	return 0;
}




