#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdlib> // for rand()
#include <stdbool.h>

const int SCREEN_W = 1000;
const int SCREEN_H = 1000;
const int TEXTURE_W = 2000;
const int TEXTURE_H = 2000;

int main()
{
	// setting the portion of the screen to copy from
	SDL_Rect srcRect = {0, 0, SCREEN_W / 32, SCREEN_H / 32};

	// setting the portion of the screen to copy
	SDL_Rect dstRect = {10, 10, SCREEN_W - 20, SCREEN_H - 20};
	SDL_Event e;

	// initializing everything
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return -1;
	}

	// creating a new window to render into
	SDL_Window *window = SDL_CreateWindow(
		"Scrolling",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000, 1000,
		SDL_WINDOW_RESIZABLE);

	// creating a render onject that will render into the window
	SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);

	// creating a texture template to draw
	SDL_Texture *texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
											 TEXTURE_W, TEXTURE_H);

	// using the vector space to dynamically store the array sizes of our points
	// just like calling malloc
	std::vector<SDL_Point> pv;
	for (int i = 0; i < 10000; i++) //setting max size to 10k points
	{
		SDL_Point point = {rand() % TEXTURE_W, rand() % TEXTURE_H}; // this initializes the x and co-ordinates of the points
		pv.emplace_back(point); // each generated generated co-ordinates is then placed at the end of the array
	}

	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running = false;
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					srcRect.y -= 3; //defining how the points will move about the screen upward
					break;
				case SDLK_DOWN: // defining how the points will move about downward
					srcRect.y += 3;
					break;
				case SDLK_LEFT: //defining how the points will move leftward
					srcRect.x -= 3;
					break;
				case SDLK_RIGHT: // defining how the points will move righward
					srcRect.x += 3;
					break;
				case SDLK_1:
					srcRect.w *= 2; //defining the zooom out pattern
					srcRect.h *= 2;
					break;
				case SDLK_2:
					srcRect.w /= 2; //defining the zoom in pattern
					srcRect.h /= 2;
					break;
				}
			}
		}

		SDL_SetRenderTarget(render, texture); // setting the target to texture
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255); //setting the color to white
		SDL_RenderClear(render); //clearing the render

		// the std:: is used to declare that the <for_each> is a function which is defined in C++ namespace
		// the for_each is used to apply a function to each elements of an array
		// the array in this case is pv which is already defined above
		// pv.begin() marks the beginning of the array and pv.end() marks the end
		//[](SDL_Point &item) is an anonymous function just like lambda in python
		// what these lines 98-101 is doing is that a function that changes the x and y co-ordinates of the
		//points is applied to each of the points which has been stored in pv
		// this enables random slight change in the movement of the points
		std::for_each(pv.begin(), pv.end(), [](SDL_Point &item)
					  {
            item.x += rand() % 3 - 1;
            item.y += rand() % 3 - 1; });

		// setting the color of the points to black
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		// creating all the points in one call
		//pv.data() is the pool of the points co-ordinates
		// pv.size() is the number of points to draw which should be 99K
		SDL_RenderDrawPoints(render, pv.data(), pv.size());

		SDL_SetRenderTarget(render, nullptr); //setting the target back to the window
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255); //setting the color of the window to white
		SDL_RenderClear(render);
		SDL_RenderCopy(render, texture, &srcRect, &dstRect); //copying the render from the texture to the window to be displayed
		SDL_RenderPresent(render); // displaying the render to the window
	}

	return 0;
}
