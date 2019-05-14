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

struct item *addItem(struct item *itemList, struct item *item, char *componentId, int itemListNumber);

void deleteItem(struct item *itemList, struct item *item);


#endif //FUNDAMENTOS2_ITEM_H
