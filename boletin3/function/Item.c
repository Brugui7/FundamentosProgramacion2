/**
 * @file
 * @brief Independent item functions
 * @author: Alejandro Brugarolas
 * @since: 2019-03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/structs.h"
#include "Item.h"

/**
 * Prints the item's data
 * @param item
 */
void showItem(struct item item) {
    char *type;
    switch (item.type) {
        case HARDWARE:
            type = "Hardware";
            break;
        case SOFTWARE:
            type = "Software";
            break;
        default:
            type = "Indefinido";
            break;
    }
    printf("\n- Art%cculo \t%s\n- Modelo:\t%s\n- Marca:\t%s\n- Stock:\t%d\n- Precio:\t%.2f\n- Transporte:\t%.2f\n- Tipo:\t%s\n",
           161, item.generalId, item.model, item.brand, item.stock, item.itemPrice,
           item.shippingPrice, type);
}

/**
 * Adds a new Item to the end of the list
 * @param itemList list of items
 * @param item item to create
 * @param componentId id of the component
 * @param componentId id of the component
 * @return itemList with the new one
 */
struct item *addItem(struct item *itemList, struct item *item, char *componentId, int itemListNumber) {
    item->next = NULL;

    if (itemList == NULL) {
        itemList = (struct item *) malloc(sizeof(struct item));
        item->previous = NULL;
        itemList->previous = itemList->next = item;
    } else {
        item->previous = itemList->previous; //The previous item of the new one, is the actual last one
        itemList->previous->next = item; //the next component of the actual last one, will be the new one
        itemList->previous = item; //Sets the new last component
    }
    char *aux = (char *) malloc(sizeof(char) * 9);
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length;
    //Creates and sets the item ID
    strftime(aux, 9, "%d_%m_%y", &item->insertDate); //This will be 9 always
    sprintf(buffer, "%s_%d_%s", componentId, itemListNumber, aux);
    length = strlen(buffer);
    item->generalId = (char *) malloc(++length * sizeof(char));
    strncpy(item->generalId, buffer, length);
    free(buffer);
    free(aux);
    return itemList;
}

/**
 * Deletes an item from the list
 * @param itemList The list
 * @param item The item
 */
void deleteItem(struct item *itemList, struct item *item) {

    if (item->next == NULL && item->previous == NULL) {
        itemList = NULL;
    } else if (item->next == NULL) {
        itemList->previous = item->previous;
        itemList->previous->next = NULL;
    } else if (item->previous == NULL) {
        itemList->next = item->next;
        item->next->previous = NULL;

    } else {
        item->next->previous = item->previous;
        item->previous->next = item->next;
    }
    free(item->generalId);
    free(item->model);
    free(item->brand);
    free(item);
}