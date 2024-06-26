#include "../headers/maze.h"

/**
 * open_file - Opening of a file
 * @filenm: pointer to the name of the file
 * Return: file pointer to opened file
*/

FILE *open_file(char *filenm)
{
	FILE *filepntr = NULL;

	filepntr = fopen(filenm, "r");
	if (filepntr == NULL)
	{
		fprintf(stderr, "File Error: Can't open file %s\n", filenm);
		exit(EXIT_FAILURE);
	}
	return (filepntr);
}

/**
 * read_file - Reading file content and constructs MazeMap_t data structure
 * @filepntr: pointer to the input file
 * Return: MazeMap_t contains mazemap data read from file
*/

MazeMap_t read_file(FILE *filepntr)
{
	size_t linecnt = 0;
	char *content = NULL;
	char *linecpy = NULL;
	MazeMap_t maze_map = {NULL, 0, 0};
	unsigned int lnindx = 0, linelnt = 0;

	maze_map.num_rows = count_lines(filepntr);
	maze_map.map_layout = malloc(sizeof(char *) * maze_map.num_rows);
	while ((getline(&content, &linecnt, filepntr)) != -1)
	{
		linecpy = strtok(strdup(content), "\n");
		if (linelnt == 0)
		{
			maze_map.num_columns = strlen(linecpy);
			linelnt++;
		}
		auth_line(maze_map.num_columns, linecpy, filepntr, (lnindx + 1));
		maze_map.map_layout[lnindx] = linecpy;
		lnindx++;
	}
	free(content);
	fseek(filepntr, 0, SEEK_SET);

	return (maze_map);
}

/**
 * close_file - Closing previously opened file
 * @filepntr: pointer to the file
 * Return: it is void
*/

void close_file(FILE *filepntr)
{
	if (filepntr != NULL)
		fclose(filepntr);
}
