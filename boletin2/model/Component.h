//
// Created by Brugui on 15/03/2019.
//

#ifndef FUNDAMENTOS2_COMPONENT_H
#define FUNDAMENTOS2_COMPONENT_H
#ifndef FUNDAMENTOS2_ITEM_H

#include "Item.h"

#endif

#include <stdbool.h>

struct component {
    char *id;
    char *name;
    char *description;
    int stock;
    struct item *items;
    int itemsNumber;
};

void showComponent(struct component component);


#endif //FUNDAMENTOS2_COMPONENT_H
