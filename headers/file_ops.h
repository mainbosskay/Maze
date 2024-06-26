#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

/*
 * Overview: Files for file parsing functions and utilities
 */

/* Functions for File Operations */
FILE *open_file(char *filenm);
MazeMap_t read_file(FILE *filepntr);
void close_file(FILE *filepntr);

/* Functions for Validating File Information */
int count_lines(FILE *filepntr);
void auth_line(int maxln_cnt, char *line, FILE *filepntr, int curr_ln);
MazeMap_t handle_file(char *filenm);

/* Functions utilities */
int check_array(char arr_val, char *arr, unsigned int arr_lent);
char *string_concat(const char *dest_str, const char *surc_str);
int slope_region(int angle, int *exp_angle);

#endif