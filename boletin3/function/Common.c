/**
 * @file
 * @brief Common function implementation
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#include <stdio.h>
#include <stdlib.h>
#include "../model/structs.h"
#include "Component.h"
#include "Item.h"

/**
 * Shows the stock or an error if there aren't components
 * @param componentList
 */
void showStockOption(struct component *componentList) {

    if (componentList == NULL) {
        printf("Error: La tienda no tiene componentes...");
        return;
    }
    printf("\n/****** STOCK TIENDA COMPONENTES INFORM%cTICOS ******/\n", 160);
    struct component *component = componentList->next;
    while (component != NULL) {
        showComponent(*component);
        struct item *item = component->items;
        if (item != NULL) {
            item = item->next;
            while (item != NULL) {
                showItem(*item);
                item = item->next;
            }
        }
        component = component->next;
    }
    printf("\n/****** FIN ******/\n");
}

/**
 * Destroy all components and items
 * @param componentList
 */
void destroyEverything(struct component *componentList) {
    if (componentList != NULL) {
        struct component *component = componentList->next;
        while (component != NULL) {
            struct item *item = component->items;
            if (item != NULL) {
                item = item->next;
                while (item != NULL) {
                    deleteItem(component->items, item);
                    item = item->next;
                }
            }
            deleteComponent(componentList, component);
            component = component->next;
        }
    }
    free(componentList);
}

