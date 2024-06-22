#ifndef SDL_HELPERS_HEADER
#define SDL_HELPERS_HEADER

/*
 * Overview: File includes functions for SDL initialization,
 * termination, and event handling.
 */

/* SDL Initialization and Closing functions */
void get_window(char *title, SDL_Instance *sdl);
void get_renderer(SDL_Instance *sdl);
void close_sdl(SDL_Instance *sdl);

/* SDL Event Handling */
void game_loop(SDL_Instance *sdl, MazeMap_t *maze_map);
void handle_events(int *exit_flag, SDL_Event *evnt, PlayerInfo *player_info,
	SDL_Point *cursor, SDL_bool *map_flag);
void sdl_error(void);
SDL_Point rotate_point(const SDL_Point *point, float xctr, float yctr,
	float rotang, float ray_sz);

#endif