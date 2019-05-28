/**
 * @file
 * @brief structs definition
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#ifndef FUNDAMENTOS2_STRUCTS_H
#define FUNDAMENTOS2_STRUCTS_H

typedef struct contact {
    char *name;
    char *number;
    struct contact *left;
    struct contact *right;
} contact;

#endif //FUNDAMENTOS2_STRUCTS_H
