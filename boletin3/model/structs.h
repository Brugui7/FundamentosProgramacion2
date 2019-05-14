/**
 * @file
 * @brief Structs and constants definition
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#ifndef FUNDAMENTOS2_STRUCTS_H
#define FUNDAMENTOS2_STRUCTS_H

#include <wchar.h>

#define NOT_DEFINED 0
#define SOFTWARE 1
#define HARDWARE 2


struct item {
    char *generalId;
    int id;
    char *model;
    char *brand;
    struct tm insertDate;
    int stock;
    enum type {
        notDefined = NOT_DEFINED, software = SOFTWARE, hardware = HARDWARE
    } type;
    float itemPrice;
    float shippingPrice;
    struct item *next;
    struct item *previous;
};

typedef struct item *itemList;

struct component {
    char *id;
    char *name;
    char *description;
    int stock;
    itemList items;
    int itemsNumber;
    struct component *next;
    struct component *previous;
};

typedef struct component *componentList;


#endif //FUNDAMENTOS2_STRUCTS_H
