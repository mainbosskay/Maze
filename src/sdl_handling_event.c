#include "../headers/maze.h"

/**
 * game_loop - Controls the game's event loop and monitors SDL events
 * @sdl: pointer to SDL_Instance data structure
 * @maze_map: pointer to MazeMap_t data structure
 * Return: it is void
*/

void game_loop(SDL_Instance *sdl, MazeMap_t *maze_map)
{
	int exit_flag = 0;
	SDL_Event evt;
	PlayerInfo player_info = {{80, 70, PLAYER_WIDTH, PLAYER_WIDTH}, (FOV * 2.5)};
	SDL_Point cursor = {0, 0};
	SDL_bool map_flag = SDL_TRUE;
	SDL_Thread *threadID;
	ThreadData thrd_dt;

	thrd_dt.sdl = sdl;
	thrd_dt.maze_map = maze_map;
	thrd_dt.player_info = &player_info;
	thrd_dt.map_flag = &map_flag;
	thrd_dt.exit_flag = &exit_flag;
	threadID = NULL;
	threadID = SDL_CreateThread(handle_thread, "RenderingThread", &thrd_dt);

	while (!exit_flag)
	{
		handle_events(&exit_flag, &evt, &player_info, &cursor, &map_flag);
		collision_sensor(&player_info, maze_map);
	}
	SDL_WaitThread(threadID, NULL);
}

/**
 * handle_events - Handles and monitors SDL events within the game
 * @exit_flag: pointer to an integer representing the SDL loop status
 * @evt: pointer to SDL_Event data structure
 * @player_info: pointer to PlayerInfo data structure
 * @cursor: pointer to an SDL_Point representing mouse positions
 * @map_flag: pointer to the boolean representing map display
 * Return: it is void
*/

void handle_events(int *exit_flag, SDL_Event *evt, PlayerInfo *player_info,
	SDL_Point *cursor, SDL_bool *map_flag)
{
	SDL_Point vector = {0, 0};

	vector = move_player(player_info);
	while (SDL_PollEvent(evt) != 0)
	{
		if (evt->type == SDL_QUIT)
			*exit_flag = 1;
		if (evt->type == SDL_MOUSEMOTION)
			cursor_movement(player_info, cursor);
		switch (evt->key.keysym.sym)
		{
			case SDLK_ESCAPE:
				*exit_flag = 1;
				break;
			case SDLK_w:
				player_info->position.x += vector.x;
				player_info->position.y -= vector.y;
				break;
			case SDLK_s:
				player_info->position.x -= vector.x;
				player_info->position.y += vector.y;
				break;
			case SDLK_a:
				player_info->current_angle -= ROTATION_MAGNITUDE;
				break;
			case SDLK_d:
				player_info->current_angle += ROTATION_MAGNITUDE;
				break;
			case SDLK_m:
				*map_flag = SDL_FALSE;
				break;
			case SDLK_n:
				*map_flag = SDL_TRUE;
				break;
			default:
				break;
		}
	}
}

/**
 * sdl_error - Printing the sdl errors
 * Return: it is void
*/

void sdl_error(void)
{
	printf("An SDL error has occured:%s\n", SDL_GetError());
}

/**
 * rotate_point - Rotates an SDL_Point around a specified center
 * @point: pointer to SDL_Point data structure
 * @xctr: x-cordinate of  center of rotation
 * @yctr: y-cordinate of center of rotation
 * @ang_rot: angle of rotation in degrees that is converted to radians
 * @ray_sz: length of the cast ray that extends upon collision
 * Return: new SDL_Point after rotation
*/

SDL_Point rotate_point(const SDL_Point *point, float xctr, float yctr,
	float ang_rot, float ray_sz)
{
	SDL_Point nwpnt = {0, 0};

	nwpnt.x = ((point->x - xctr) * cos(ang_rot) - (((point->y - ray_sz) - yctr) *
						sin(ang_rot))) + xctr;
	nwpnt.y = ((point->x - xctr) * sin(ang_rot) + (((point->y - ray_sz) - yctr) *
						cos(ang_rot))) + yctr;
	/*
	 * for more understanding visit
	 * https://danceswithcode.net/engineeringnotes/rotations_in
	 * _2d/rotations_in_2d.html
	 */
	return (nwpnt);
}
