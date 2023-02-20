#include "struct.h"

#ifndef FILE_WORK_H

#define FILE_WORK_H

#define MAX_SIZE 1000

#define OK_READ 0
#define OK_ADDING 0
#define OK_DEL 0

#define ERR_ELEMENTS -3

#define ERR_CITY_INPUT -4
#define ERR_SQUARE_INPUT -5
#define ERR_ROOMS_INPUT -6
#define ERR_COST_INPUT -7
#define ERR_TYPE_INPUT -8
#define ERR_DECOR_INPUT -9
#define ERR_YEAR_INPUT -10
#define ERR_OWNER_INPUT -11
#define ERR_RESIDENT_INPUT -12
#define ERR_ANIMAL_INPUT -13
#define ERR_TOO_MUCH_FLATS -14
#define ERR_FILE_CLEAR -15

int read_file(FILE *flats_file, flat_t *flats_arr, int *size, keys_t *keys);
int add_flat(flat_t *flats_arr, int *size, keys_t *keys);
int delete_by_square(flat_t *flats_arr, int *size, keys_t *keys);
void swap_keys(keys_t *keys, int i, int j);
void swap_flats(flat_t *flats_arr, int i, int j);

#endif
