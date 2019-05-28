/**
 * @file
 * @brief structs definition
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/
#ifndef FUNDAMENTOS2_STRUCTS_H
#define FUNDAMENTOS2_STRUCTS_H

typedef struct road {
    struct road *next;
    struct city *to;
    int distance;
} road;

typedef struct city {
    char *name;
    struct city *next;
    struct road *road;
} city;
#endif //FUNDAMENTOS2_STRUCTS_H
