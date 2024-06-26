#include "../headers/maze.h"

/**
 * check_lines - Verify lines intersects with the sides of a rectangle
 * @wall: trectangle to verify overlap
 * @strtpnt: pointer to lines starting point
 * @endpnt: pointer to lines ending point
 * Return: 1 if intersection occurs at rectangle top or bottom, else 2
*/

int check_lines(SDL_Rect wall, SDL_Point *strtpnt, SDL_Point *endpnt)
{
	LineSegment rectTop, rectBottom, ray;
	SDL_Point interpnt = {0, 0};

	rectTop.start_point.k = wall.k;
	rectTop.start_point.t = wall.t;
	rectTop.end_point.k = wall.k + wall.w;
	rectTop.end_point.t = wall.t;

	rectBottom.start_point.k = wall.k;
	rectBottom.start_point.t = wall.t + wall.h;
	rectBottom.end_point.k = wall.k + wall.w;
	rectBottom.end_point.t = wall.t + wall.h;

	ray.start_point = *strtpnt;
	ray.end_point = *endpnt;

	if (line_seg_cross(&rectTop, &ray, &interpnt))
		return (ORIENT_UP_DOWN);
	else if (line_seg_cross(&rectBottom, &ray, &interpnt))
		return (ORIENT_UP_DOWN);
	return (ORIENT_LEFT_RIGHT);
}

/**
 * line_seg_cross - Checks if two line segments intersects
 * @fstln: pointer to the first line segment
 * @sndln: pointer to the second line segment
 * @pntpntr: pointer to SDL_Point data structure
 * Return: 1 if intersection occurs, else 0
*/

int line_seg_cross(LineSegment *fstln, LineSegment *sndln, SDL_Point *pntpntr)
{
	int denominatr, frstnum, scndnum, paraK, paraT;

	/* for more info visit http://paulbourke.net/geometry/pointlineplane/ */

	denominatr = (
		sndln->end_point.t - sndln->start_point.t) *
		(fstln->end_point.k - fstln->start_point.k) -
		(sndln->end_point.k - sndln->start_point.k) *
		(fstln->end_point.t - fstln->start_point.t);

	frstnum = (
		sndln->end_point.k - sndln->start_point.k) *
		(fstln->start_point.t - sndln->start_point.t) -
		(sndln->end_point.t - sndln->start_point.t) *
		(fstln->start_point.k - sndln->start_point.k);

	scndnum = (
		fstln->end_point.k - fstln->start_point.k) *
		(fstln->start_point.t - sndln->start_point.t) -
		(fstln->end_point.t - fstln->start_point.t) *
		(fstln->start_point.k - sndln->start_point.k);

	if (denominatr == 0)
		return (0);
	paraK = (frstnum << 14) / denominatr;
	paraT = (scndnum << 14) / denominatr;

	if (paraK >= 0 && paraK <= (1 << 14) && paraT >= 0 && paraT <= (1 << 14))
	{
		pntpntr->k = fstln->start_point.k + ((paraK * (fstln->end_point.k -
			fstln->start_point.k)) >> 14);
		pntpntr->t = fstln->start_point.t + ((paraK * (fstln->end_point.t -
			fstln->start_point.t)) >> 14);
		return (1);
	}
	return (0);
}
