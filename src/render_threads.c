#include "../headers/maze.h"

/**
 * transmit_viewport - Generates and displays the renderer's contents
 * @sdl: pointer to SDL_Instance data structure
 * Return: it is void
*/

void transmit_viewport(SDL_Instance *sdl)
{
	REND_COLOR_BLACK(sdl->sdl_renderer);
	SDL_SetRenderDrawBlendMode(sdl->sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderPresent(sdl->sdl_renderer);
	SDL_RenderClear(sdl->sdl_renderer);
}

/**
 * handle_thread - Handles rendering in a different thread
 * @thrd_pntr: void pointer to ThreadData data structure
 * Return: integer indicating thread status
*/

int handle_thread(void *thrd_pntr)
{
	ThreadData *thrd_dt = thrd_pntr;
	Uint64 sttcnt, endcnt;
	double rendTimeMs;

	while (*(thrd_dt->exit_flag) == 0)
	{
		sttcnt = SDL_GetPerformanceCounter();
		plot_textured_sky(thrd_dt->sdl, thrd_dt->maze_map);
		plot_untextured_floor(thrd_dt->sdl);
		raycast(thrd_dt->sdl, thrd_dt->player_info, thrd_dt->maze_map,
			thrd_dt->map_flag);
		plot_weapon(thrd_dt->sdl, thrd_dt->maze_map);
		if (*(thrd_dt->map_flag) != 0)
		{
			plot_mazemap(thrd_dt->sdl, thrd_dt->maze_map);
			render_player(thrd_dt->sdl, thrd_dt->player_info);
		}
		transmit_viewport(thrd_dt->sdl);
		endcnt = SDL_GetPerformanceCounter();
		rendTimeMs = (endcnt - sttcnt) / SDL_GetPerformanceCounter() * 1000;
		SDL_Delay(floor(16.666 - rendTimeMs));
	}
	return (0);
}
