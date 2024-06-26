#include "../headers.maze.h"

/**
 * check_array - Checking if certain value is in an array
 * @arr_val: value that find the array
 * @arr: pointer to the array
 * @arr_lent: length of the array
 * Return: 1 if value is in array or 0
*/

int check_array(char arr_val, char *arr, unsigned int arr_lent)
{
	unsigned int indx;

	for (indx = 0 ; indx < arr_lent ; indx++)
	{
		if (arr[indx] == arr_val)
			return (1);
	}
	return (0);
}

/**
 * string_concat - Merging two strings together
 * @dest_str: pointer to the destination string
 * @surc_str: pointer to the source string
 * Return: new string that being merged
*/

char *string_concat(const char *dest_str, const char *surc_str)
{
	char *nwstr = NULL;

	nwstr = malloc(strlen(dest_str) + strlen(surc_str) + 1);
	if (nwstr == NULL)
		return (NULL);
	strcpy(nwstr, dest_str);
	strcat(nwstr, surc_str);
	return (nwstr);
}

/**
 * slope_region - Calculating quadrant of an angle
 * @angle: angle to calculate the quadrant
 * @exp_angle: pointer to angle that rangle between (0-360)
 * Return: quadrant which the angle belongs between (0-3)
*/

int slope_region(int angle, int *exp_angle)
{
	int region;

	angle %= 360;
	if (angle < 0)
		angle += 360;
	region = (angle / 90) % (4 + 1);
	*exp_angle = angle;

	return (region);
}
