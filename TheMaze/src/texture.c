#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
	//initializing all SDL resources

	SDL_Init(SDL_INIT_EVERYTHING);

	/** declaring and creating Window
	 * @"Textures": this is the name that will appear at the top of the window
	 * SDL_WINDOWPOS_CENTERED: this flag specify the position of the x co-ordinate of the window
	 * that is, the window will appear at the middle of the monitor or screen where the application would be
	 * displayed
	 * the second SDL_WINDOWPOS_CENTERED defines the y co-ordinate of the window
	 * 1000, 1000: this integer sets the width and height of the window respectively
	 * SDL_WINDOW_RESIZABLE: this flag gives the user the ability to resize the window
	 */

	SDL_Window *window = SDL_CreateWindow(
		"Textures",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000, 1000,
		SDL_WINDOW_RESIZABLE);

	/**
	 * initializing and creating a pointer to a Render object
	 * this is object is used for rendering to the window. It allows for drawing various graphics, images
	 * colors on the window
	 * @window: this is the pointer to the window object render will be rendering into
	 * -1: this flag specifies which driver render should use in rendering. in the case of -1, i am setting the 
	 * render to use the first available driver
	 * 0: no special flag is set for the renderer
	 */

	SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);

	/**
	 * Creating a pointer to an SDL_Texture object.
	 * SDL_Texture is used to store and render images onto the screen. It can be used to store object from files which
	 * can be rendered onto the screen with the aid of SDL_Renderer
	 * @render: this specifies the pointer to a render object. this will be object that will be used in rendering the
	 * Texture to the screen
	 * @SDL_PIXELFORMAT_RGBA8888: this specifies the pixel format and order. in this case, the order
	 * of the pixel is RED-GREEN-BLUE-ALPHA. the ALPHA specifies the transparency of the pixel.
	 * the 8888 specifies the max bits for each of the pixel
	 * @SDL_TEXTUREACCESS_TARGET: this sets the Texture in draw mode, meaning you can draw on the Texture with the
	 * render object before rendering the Texture on the screen
	 * The two integers specifies the width and height of the pixel
	 */

	SDL_Texture *red_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);

	/*same as red_texture */
	SDL_Texture *blue_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000);

	/**
	 * This function sets the render target to the specified target, in this case, red_texture
	 * by default, render is set to target the window but after this line, it will
	 * target the SDL_Texture red_texture which had also been set to have target access to via the
	 * SDL_TEXTUREACCESS_TARGET
	 */
	SDL_SetRenderTarget(render, red_texture);

	/* setting the color on the red_texture object. in this case, the color was set to red */
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	// clearing the format
	SDL_RenderClear(render);
	
	// change target to blue texture
	SDL_SetRenderTarget(render, blue_texture);

	// setting color to blue
	SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
	SDL_RenderClear(render);

	// setting target back to the window
	SDL_SetRenderTarget(render, NULL);

	SDL_Rect srcRect = {0, 0, 500, 500}; // Portion of the texture
	SDL_Rect dstRect = {50, 50, 500, 500};
	/**
	 * SDL_RenderCopy is used to copy a render object from a source target to a destination target
	 * @render: this is the pointer to the render object. this will be used in copying
	 * @red_texture: the source target being copied from
	 * NULL: this sets the render to copy the entire area of the texture. The flag is used to copy a rect area of
	 * the texture
	 * NULL: this makes render to fill the entire destination target with the copied rendering
	 */
	SDL_RenderCopy(render, red_texture, &srcRect, &dstRect);

	// presenting/displaying the render to window
	SDL_RenderPresent(render);
	SDL_Delay(10000);

	SDL_RenderCopy(render, blue_texture, NULL, NULL);
	SDL_RenderPresent(render);
	SDL_Delay(10000);

	return 0;
}