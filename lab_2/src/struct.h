#ifndef STRUCT_H
#define STRUCT_H

#define MAX_ADDRES_NAME 100
#define FLATS_MAX 1000

typedef struct
{
    int decorated;
} primary_t;


typedef struct
{
    int build_year;
    int previous_owners;
    int previous_rezidents;
    int animals;
} secondaray_t;


typedef union
{
    primary_t primary;
    secondaray_t secondary;
} type_flats;


typedef struct
{
    char address[MAX_ADDRES_NAME + 1];
    int square;
    int rooms;
    int one_m_cost;
    int is_primary;
    type_flats flat;
} flat_t;


typedef struct keys
{
    int square;
    int id;
} keys_t;


typedef struct table
{
    flat_t *flats_arr;
    keys_t *keys;
    int size;
    int maxsize; 
} table_t;

#endif