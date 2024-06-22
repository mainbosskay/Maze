#ifndef MAZE_STRUCTURE_H
#define MAZE_STRUCTURE_H

/*
 * Overview: File contains defined structures for rendering, player,
 * map, lines and multi-threading.
 */

/**
 * struct SDL_Instance - Structure contains SDL global variables
 * @sdl_window: pointer to SDL window for displaying the game
 * @sdl_renderer: pointer to SDL renderer for rendering graphics
 * @sky_texture: pointer to sky texture
 * @wall_surface: pointer to wall surface
 * @wall_texture: pointer to wall texture
 * @weapon_texture: pointer to weapon texture
 */

typedef struct SDL_Instance
{
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
	SDL_Texture *sky_texture;
	SDL_Surface *wall_surface;
	SDL_Texture *wall_texture;
	SDL_Texture *weapon_texture;
} SDL_Instance;

/**
 * struct PlayerInfo - Structure contains player info
 * @position: represents the player's position on screen
 * @current_angle: represents current viewing angle of player
 */

typedef struct PlayerInfo
{
	SDL_Rect position;
	float current_angle;
} PlayerInfo;

/**
 * struct MazeMap - Structure contains game map layout
 * @map_layout: pointer to 2D array representing the map
 * @num_rows: represents number of rows in map
 * @num_columns: represents the number of columns in the map
 */

typedef struct MazeMap
{
	char **map_layout;
	int num_rows;
	int num_columns;
} MazeMap_t;

/**
 * struct LineSegment - Structure contains line segment
 * @start_point: starting point of line segment
 * @end_point: ending point of line segment
 */

typedef struct LineSegment
{
	SDL_Point start_point;
	SDL_Point end_point;
} LineSegment;

/**
 * struct ThreadData - Structure contains data for multithreading maze game
 * @sdl: pointer to the SDL_Instance
 * @player_info: pointer to the PlayerInfo
 * @maze_map: pointer to the MazeMap
 * @map_flag: pointer indicating the map status
 * @exit_flag: pointer indicating program exit status
 */

typedef struct ThreadData
{
	SDL_Instance *sdl;
	MazeMap_t *maze_map;
	struct PlayerInfo *player_info;
	SDL_bool *map_flag;
	int *exit_flag;
} ThreadData;

#endif