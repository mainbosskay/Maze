#include "../headers/maze.h"

/**
 * count_lines - Counting the lines in the file
 * @filepntr - pointer to the file
 * Return: number of line
*/

int count_lines(FILE *filepntr)
{
	char filechar;
	int linecnt;

	linecnt = 0;
	while (!feof(filepntr))
	{
		filechar = fgetc(filepntr);
		if (filechar == '\n')
		{
			linecnt++;
		}
	}
	fseek(filepntr, 0, SEEK_SET);

	return (linecnt + 1);
}

/**
 * auth_line - Check line contents for errors and verify
 * @maxln_cnt: maximum allowable line length
 * @line: pointer to the line to be checked
 * @filepntr: pointer to the file to check
 * @curr_ln: current line number evaluated
 * Return: it is void
*/

void auth_line(int maxln_cnt, char *line, FILE *filepntr, int curr_ln)
{
	char allow_char[] = {'0', '1'};
	int indx;
	unsigned int linelnt = strlen(line);

	if (line == NULL)
		return;
	if (linelnt != (unsigned int)maxln_cnt)
	{
		free(line);
		close_file(filepntr);
		printf("Error line No. %d: The columns should be equal.\n", curr_ln);
		exit(EXIT_FAILURE);
	}
	for (indx = 0 ; indx < maxln_cnt ; indx++)
	{
		if ((check_array(line[indx], allow_char, maxln_cnt)) == 0)
		{
			printf("Error Line No. %d: Invalid map values found.\n", curr_ln);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * handle_file - Handling file operations
 * @filenm: pointer to the file
 * Return: MazeMap_t data structure that contains map info
*/

MazeMap_t handle_file(char *filenm)
{
	FILE *filepntr = NULL;
	MazeMap_t maze_map;

	filepntr = open_file(filenm);
	maze_map = read_file(filepntr);
	close_file(filepntr);

	return (maze_map);
}
