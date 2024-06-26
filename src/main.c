#include "../headers/maze.h"

/**
 * main - Starting point of the Maze program
 * @argc: number of command line arguments
 * @argv: double pointer to array of strings passed to command-line args
 * Return: 0 on success, or exit otherwise
*/

int main(int argc, char **argv)
{
	SDL_Instance sdl = {NULL, NULL, NULL, NULL, NULL, NULL};
	MazeMap_t maze_map;
	char *map_dirct;

	if (argc < 2)
	{
		printf("Usage: %s 'map_dir'", argv[0]);
		exit(EXIT_FAILURE);
	}
	map_dirct = string_concat("maps/", argv[1]);
	maze_map = handle_file(map_dirct);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Initialization Error! SDL_Error:%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	get_window(WINDOW_TITLE, &sdl);
	get_renderer(&sdl);
	game_loop(&sdl, &maze_map);
	map_data(&maze_map);
	close_sdl(&sdl);

	return (0);
}
