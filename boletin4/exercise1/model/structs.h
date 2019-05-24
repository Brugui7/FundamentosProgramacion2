//
// Created by Brugui on 22/05/2019.
//

#ifndef FUNDAMENTOS2_STRUCTS_H
#define FUNDAMENTOS2_STRUCTS_H

typedef struct contact {
    char *name;
    char *number;
    struct contact *left;
    struct contact *right;
} contact;

#endif //FUNDAMENTOS2_STRUCTS_H
