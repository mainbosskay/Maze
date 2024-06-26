#include "../headers/maze.h"

/**
 * get_window - Set up the SDL window
 * @title: pointer to string that contains the window title
 * @sdl: pointer to SDL_Instance data structure
 * Return: 1 if window is created else 0
*/

void get_window(char *title, SDL_Instance *sdl)
{
	sdl->sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!sdl->sdl_window)
	{
		sdl_error();
		close_sdl(sdl);
		exit(EXIT_FAILURE);
	}
}

/**
 * get_renderer - Set up the SDL renderer
 * @sdl: pointer to SDL_Instance data structure
 * Return: it is void
*/

void get_renderer(SDL_Instance *sdl)
{
	sdl->sdl_renderer = SDL_CreateRenderer(sdl->sdl_window, -1,
	SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!sdl->sdl_renderer)
	{
		sdl_error();
		close_sdl(sdl);
		exit(EXIT_FAILURE);
	}
}

/**
 * close_sdl - Releases SDL resources and closes SDL window
 * @sdl: pointer to SDL_Instance data structure
 * Return: it is void
*/

void close_sdl(SDL_Instance *sdl)
{
	if (sdl->sdl_window)
		SDL_DestroyWindow(sdl->sdl_window);
	if (sdl->sdl_renderer)
		SDL_DestroyRenderer(sdl->sdl_renderer);
	if (sdl->sky_texture)
		SDL_DestroyTexture(sdl->sky_texture);
	if (sdl->wall_surface)
		SDL_FreeSurface(sdl->wall_surface);
	if (sdl->wall_texture)
		SDL_DestroyTexture(sdl->wall_texture);
	if (sdl->weapon_texture)
		SDL_DestroyTexture(sdl->weapon_texture);
	sdl->sdl_window = NULL;
	sdl->sdl_renderer = NULL;
	sdl->sky_texture = NULL;
	sdl->wall_surface = NULL;
	sdl->wall_texture = NULL;
	SDL_Quit();
}
