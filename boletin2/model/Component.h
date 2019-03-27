/**
 * @file
 * @brief Data definition for component
 * @author: Alejandro Brugarolas
 * @since: 2019-03-15
*/

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

int compareNames(const void *paramComponent1, const void *paramComponent2);

void sortComponentsByName(struct component *components, size_t componentsSize);

#endif //FUNDAMENTOS2_COMPONENT_H
