#include "../headers/maze.h"

/**
 * raycast - Shoots rays to display 3D scene on 2D map
 * @sdl: pointer to SDL_Instance data structure
 * @player_info: pointer to PlayerInfo data structure
 * @maze_map: pointer to MazeMap_t data structure
 * @map_flag: pointer to the Boolean indicating mazemap display status
 * Return: it is void
*/

void raycast(SDL_Instance *sdl, PlayerInfo *player_info,
	MazeMap_t *maze_map, SDL_bool *map_flag)
{
	SDL_Point point, plyctr;
	double indx, deg = (player_info->current_angle - (FOV / 2.0));
	double ray_ang;
	double raylent = 0.0;
	double expdist = 0.0;
	SDL_Color sd_color = {0, 0, 0, 0};
	int side;
	double curr_ang = (deg - FOV);

	plyctr.k = player_info->position.k + (player_info->position.w / 2);
	plyctr.t = player_info->position.t + (player_info->position.h / 2);
	ray_ang = ((FOV) / (SCREEN_WIDTH * 1.0));
	for (indx = 0 ; indx < SCREEN_WIDTH ; indx++)
	{
		point = check_intersection(&plyctr, curr_ang, *maze_map, &raylent,
			&side);
		set_wall_tones(&sd_color, side);
		if (*map_flag)
		{
			REND_COLOR_GREEN(sdl->sdl_renderer);
			SDL_RenderDrawLine(sdl->sdl_renderer, plyctr.k, plyctr.t, point.k, point.t);
		}
		expdist = remove_distortion(player_info, raylent, curr_ang);
		plot_walls(sdl, expdist, indx, sd_color);
		curr_ang += ray_ang;
	}
}

/**
 * check_intersection - Verifies if ray hit any walls
 * @ctr: pointer to position from the player's center
 * @angle_rot: rotation angle for the ray
 * @maze_map: pointer to MazeMap_t data structure
 * @raylent: pointer to save the ray's calculated length
 * @side: show the side of where ray's intersect
 * Return: SDL_Point with cordinates of the ray
*/

SDL_Point check_intersection(SDL_Point *ctr, double angle_rot,
	MazeMap_t maze_map, double *raylent, int *side)
{
	SDL_Point point;
	SDL_bool walls_intersect = SDL_FALSE;
	int row_indx, col_indx;
	SDL_Rect wallRect;
	LineSegment LineSegment = {{0, 0}, {0, 0}};
	double oppt, adjct, hypt;

	point.k = ctr->k;
	point.t = ctr->t;
	wallRect.k = 0;
	wallRect.t = 0;
	wallRect.w = GRID_SIZE;
	wallRect.h = GRID_SIZE;
	point = rotate_point(&point, ctr->k, ctr->t, RADIAN(angle_rot),
		MAX_DRAW_DISTANCE);
	for (row_indx = 0 ; row_indx < maze_map.num_rows ; row_indx++)
		for (col_indx = 0 ; col_indx < maze_map.num_columns ; col_indx++)
		{
			if (maze_map.map_layout[row_indx][col_indx] == '0')
				continue;
			wallRect.k = (col_indx << 4) + MAP_MARGIN;
			wallRect.t = (row_indx << 4) + MAP_MARGIN;
			LineSegment.start_point = *ctr;
			LineSegment.end_point = point;
			walls_intersect = SDL_IntersectRectAndLine(
				&wallRect, &LineSegment.start_point.k, &LineSegment.start_point.t,
				&LineSegment.end_point.k, &LineSegment.end_point.t);
			if (walls_intersect == SDL_TRUE)
			{
				*side = check_lines(wallRect, ctr, &LineSegment.start_point);
				adjct = LineSegment.start_point.k - ctr->k;
				oppt = LineSegment.start_point.t - ctr->t;
				hypt = sqrt((pow(oppt, 2.0) + pow(adjct, 2.0)));
				point = *ctr;
				point = rotate_point(&point, ctr->k, ctr->t, RADIAN(angle_rot), hypt);
				*raylent = hypt;
			}
		}
	return (point);
}

/**
 * remove_distortion - Adjust ray length distortion
 * @player_info: pointer to the PlayerInfo data structure
 * @raylent: length of ray from player to wall
 * @ray_angle: angle of ray to player's view
 * Return: ray length distortion
*/

double remove_distortion(PlayerInfo *player_info, double raylent,
	double ray_angle)
{
	double distortedRaylent = raylent;
	double correctedRaylent = 0.0;
	double anglediff = (player_info->current_angle - (FOV / 2.0));

	correctedRaylent = distortedRaylent *
		cos(RADIAN((ray_angle - (anglediff - FOV / 2.0))));
	return (correctedRaylent);
}

/**
 * plot_walls - Displays and draws walls on the SDL renderer
 * @sdl: pointer to the SDL_Instance data structure
 * @raylent: length of ray from player to wall
 * @ray_indx: current screen column for wall drawing
 * @wall_color: pointer to SDL_Color data structure
 * Return: it is void
*/

void plot_walls(SDL_Instance *sdl, double raylent, int ray_indx,
	SDL_Color wall_color)
{
	int projectionDistance = (SCREEN_WIDTH / 2) / (tan(RADIAN((FOV / 2))));
	double wallheight = ceil((SCREEN_HEIGHT / (raylent * 1.0)) *
		(projectionDistance >> 6));
	double walldrawstart = (SCREEN_HEIGHT / 2.0) - (wallheight / 2.0);

	plot_textured_walls(sdl, wallheight, ray_indx, walldrawstart,
		wall_color.a);
}
