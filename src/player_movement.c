#include "../headers/maze.h"

/**
 * cursor_movement - Monitors mouse position and modifies player rotation
 * @player_info: pointer to PlayerInfo data structure
 * @cursor: pointer to SDL_Point stores mouse cordinates
 * Return: it is void
*/

void cursor_movement(PlayerInfo *player_info, SDL_Point *cursor)
{
	int mouse_pos_x = cursor->x;
	int movement_x = 0;

	SDL_GetMouseState(&cursor->x, &cursor->y);
	movement_x = cursor->x - mouse_pos_x;
	if (movement_x < 0)
		player_info->current_angle -= ROTATION_MAGNITUDE;
	else
		player_info->current_angle += ROTATION_MAGNITUDE;
}

/**
 * move_player - Moves player position based on direction
 * @player_info: pointer to PlayerInfo data structure
 * Return: SDL_Point with offset distance
*/

SDL_Point move_player(PlayerInfo *player_info)
{
	SDL_Point vector = {0, 0};
	double degree_rad = player_info->current_angle;

	vector.x = cos(RADIAN((90 - (degree_rad - (FOV / 2))))) * MOVE_SPEED;
	vector.y = sin(RADIAN((90 - (degree_rad - (FOV / 2))))) * MOVE_SPEED;

	return (vector);
}
