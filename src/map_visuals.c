#include "../headers/maze.h"

/**
 * plot_mazemap - Displays a 2D map on the SDL window
 * @sdl: pointer to SDL_Instance data structure
 * @maze_map: pointer to MazeMap_t data structure
 * Return: it is void
*/

void plot_mazemap(SDL_Instance *sdl, MazeMap_t *maze_map)
{
	int row_indx, col_indx;
	SDL_Rect cell = {0, 0, GRID_SIZE, GRID_SIZE};

	for (row_indx = 0 ; row_indx < maze_map->num_rows ; row_indx++)
	{
		for (col_indx = 0 ; col_indx < maze_map->num_cols ; col_indx++)
		{
			cell.x = (col_indx << 4) + MAP_MARGIN;
			cell.y = (row_indx << 4) + MAP_MARGIN;
			if (maze_map->map_layout[row_indx][col_indx] == '0')
			{
				REND_COLOR(sdl->sdl_renderer, 255, 255, 255, 100);
				SDL_RenderFillRect(sdl->sdl_renderer, &cell);
			}
			else
			{
				REND_COLOR(sdl->sdl_renderer, 0, 0, 0, 150);
				SDL_RenderFillRect(sdl->sdl_renderer, &cell);
			}
		}
	}
}

/**
 * plot_textured_sky - Displays a detailed sky in the SDL window
 * @sdl: pointer to SDL_Instance data structure
 * @maze_map: pointer to MazeMap_t data structure
 * Return: it is void
*/

void plot_textured_sky(SDL_Instance *sdl, MazeMap_t *maze_map)
{
	SDL_Rect sky_dome = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};
	SDL_Surface *sky_surface;

	if (sdl->sky_texture == NULL)
	{
		sky_surface = SDL_LoadBMP("images/sky.bmp");
		if (sky_surface == NULL)
		{
			printf("Sky Surface Error: %s", SDL_GetError());
			map_data(maze_map);
			close_sdl(sdl);
			exit(EXIT_FAILURE);
		}
		sdl->sky_texture = SDL_CreateTextureFromSurface(sdl->sdl_renderer,
			sky_surface);
		SDL_FreeSurface(sky_surface);
	}
	SDL_RenderCopy(sdl->sdl_renderer, sdl->sky_texture, NULL, &sky_dome);
}

/**
 * plot_untextured_sky - Displays a plain ceiling in the SDL window
 * @sdl: pointer to SDL_Instance data structure
 * Return: it is void
*/

void plot_untextured_sky(SDL_Instance *sdl)
{
	SDL_Rect sky_dome = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};

	REND_COLOR(sdl->sdl_renderer, 25, 181, 254, 255);
	SDL_RenderFillRect(sdl->sdl_renderer, &sky_dome);
}

/**
 * plot_untextured_floor - Displays a plain floor in the SDL window
 * @sdl: pointer to SDL_Instance data structure
 * Return: it is void
*/

void plot_untextured_floor(SDL_Instance *sdl)
{
	double floor_offset = (SCREEN_HEIGHT >> 1);
	SDL_Rect floor_area;

	floor_area.x = 0;
	floor_area.y = floor_offset;
	floor_area.w = SCREEN_WIDTH;
	floor_area.h = (SCREEN_HEIGHT >> 1);

	REND_COLOR(sdl->sdl_renderer, 52, 140, 49, 255);
	SDL_RenderFillRect(sdl->sdl_renderer, &floor_area);
}

/**
 * set_wall_tones - Assigns wall color based on side
 * @color_pntr: pointer to the color
 * @side: side in which it is hitting
 * Return: it is void
*/

void set_wall_tones(SDL_Color *color_pntr, int side)
{
	SDL_Color vertl_color = {112, 112, 112, 255};
	SDL_Color horztl_color = {96, 96, 96, 150};

	if (side == ORIENT_UP_DOWN)
		*color_pntr = vertl_color;
	else
		*color_pntr = horztl_color;
}
