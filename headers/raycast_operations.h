#ifndef RAYCAST_OPS_H
#define RAYCAST_OPS_H

/*
 * Overview: This header file contains map visualization,
 * map management and raycasting algorithm functions
 */

/* Functions for Map Visualization */
void plot_mazemap(SDL_Instance *sdl, MazeMap_t *maze_map);
void plot_textured_sky(SDL_Instance *sdl, MazeMap_t *maze_map);
void plot_untextured_sky(SDL_Instance *sdl);
void plot_untextured_floor(SDL_Instance *sdl);
void set_wall_tones(SDL_Color *color_pntr, int side);

/* Functions for Managing Map */
void map_data(MazeMap_t *maze_map);

/* Functions implementing the Raycasting Algorithm */
void raycast(SDL_Instance *sdl, PlayerInfo *player_info,
	MazeMap_t *maze_map, SDL_bool *map_flag);
SDL_Point check_intersection(SDL_Point *ctr, double angle_rot,
	MazeMap_t maze_map, double *raylent, int *side);
double remove_distortion(PlayerInfo *player_info, double raylent,
	double ray_angle);
void plot_walls(SDL_Instance *sdl, double raylent, int ray_indx,
	SDL_Color wall_color);

/* Detecting raycast collision functions */
int check_lines(SDL_Rect wall, SDL_Point *strtpnt, SDL_Point *endpnt);
int line_seg_cross(LineSegment *frstln, LineSegment *scndln, SDL_Point *pntpntr);

/* Functions for rendering textures using raycasting */
void plot_textured_walls(SDL_Instance *sdl, double wallhgt, int currcol,
	int strt_axis, uint8_t alpha);

#endif