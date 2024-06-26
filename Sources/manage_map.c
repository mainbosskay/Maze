#include "../headers/maze.h"

/**
 * map_data - Frees the memory allocated for the 2D map
 * @maze_map: pointer to the MazeMap_t data structure
 * Return: it is void
*/
void map_data(MazeMap_t *maze_map)
{
	int row_indx;

	for (row_indx = 0 ; row_indx < maze_map->num_rows ; row_indx++)
		free(maze_map->map_layout[row_indx]);
	free(maze_map->map_layout);
}
