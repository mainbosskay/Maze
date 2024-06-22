#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

/*
 * Overview: Files for file parsing functions and utilities
 */

/* Functions for File Operations */
FILE *open_file(char *filenm);
MazeMap_t read_file(FILE *fileptr);
void close_file(FILE *fileptr);

/* Functions for Validating File Information */
int count_lines(FILE *fileptr);
void authz_line(int maxln_cnt, char *line, FILE *fileptr, int curr_ln);
MazeMap_t handle_file(char *filenm);

/* Functions utilities */
int check_array(char arr_val, char *arr, unsigned int arr_lent);
char *string_concat(const char *dest_str, const char *src_str);
int slope_region(int angle, int *exp_angle);

#endif