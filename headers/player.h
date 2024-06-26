#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*
 * Overview: File includes functions for player handling
 * and movement in the Maze game
 */

/* Player Management function */
void player_render(SDL_Instance *sdl, PlayerInfo *player_info);
void player_skid(PlayerInfo *player_info);
void weapon_plot(SDL_Instance *sdl, MazeMap_t *maze_map);
void collision_sensor(PlayerInfo *player_info, MazeMap_t *maze_map);

/* Player movement functions */
void cursor_movement(PlayerInfo *player_info, SDL_Point *cursor);
SDL_Point move_player(PlayerInfo *player_info);

#endif
