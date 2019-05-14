/**
 * @file
 * @brief Functions definition for item
 * @author: Alejandro Brugarolas
 * @since: 2019-03
*/

#ifndef FUNDAMENTOS2_ITEM_H
#define FUNDAMENTOS2_ITEM_H

#include <stdbool.h>
#include <time.h>

void showItem(struct item item);

struct component *createItemOption(struct component *componentList);

struct item *addItem(struct item *itemList, struct item *item, char *componentId, int itemListNumber);

struct item *getItemOnComponent(char *itemId, struct component *component);

void deleteItemOption(struct component *componentList);

void deleteItem(struct item *itemList, struct item *item);


#endif //FUNDAMENTOS2_ITEM_H
