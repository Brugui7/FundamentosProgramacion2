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
#include "Common.h"
#include "Component.h"

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


/**
 * Asks for the file where te components are stored in and tries to read all of them
 * FORMAT
 * Component ID
 * Numeric ID
 * date in DD/MM/YYYY
 * model
 * brand
 * type
 * price shippingPrice (both with a point as decimal separator)
 * stock
 * @param componentList
 * @return componentList updated
 */
struct component *createItemOption(struct component *componentList) {
    char fileName[100] = "";
    FILE *file = NULL;
    char *componentId, *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length, bufferSize = 255;
    do {
        printf("Introduzca la ruta del fichero donde se encuentran los art%cculos\n> ", 161);
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {

        struct item *item = (struct item *) malloc(sizeof(struct item));
        fscanf(file, "%s\n", buffer);
        length = strlen(buffer);
        componentId = (char *) malloc(++length * sizeof(char));
        strncpy(componentId, buffer, length);

        fscanf(file, "%d/%d/%d\n", &item->insertDate.tm_mday, &item->insertDate.tm_mon, &item->insertDate.tm_year);
        item->insertDate.tm_mon -= 1;

        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n");
        length = strlen(buffer);
        item->model = (char *) malloc(++length * sizeof(char));
        strncpy(item->model, buffer, length);


        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n");
        length = strlen(buffer);
        item->brand = (char *) malloc(++length * sizeof(char));
        strncpy(item->brand, buffer, length);


        fscanf(file, "%s\n", buffer);
        if (strcmp(buffer, "Hardware") == 0) {
            item->type = HARDWARE;
        } else if (strcmp(buffer, "Software") == 0) {
            item->type = SOFTWARE;
        } else {
            item->type = NOT_DEFINED;
        }

        fscanf(file, "%f %f\n", &item->itemPrice, &item->shippingPrice);
        fscanf(file, "%d\n", &item->stock);
        printf("Art%cculo detectado...\n", 161);

        struct component *component = getComponentById(componentList, componentId);
        if (component == NULL) {
            printf("No se ha encontrado el componente para asociar este art%cculo", 161);
            continue;
        }

        component->items = addItem(component->items, item, componentId, ++component->itemsNumber);
        printf("Art%cculo guardado correctamente\n", 161);
        showItem(*item);
        free(componentId);

    }
    fclose(file);
    free(buffer);
    return componentList;

}


/**
 * Asks for the file where the components and items id are stored in and tries to delete all of them
 * Expected format: "componentId itemId"
 * @param componentList
 */
void deleteItemOption(struct component *componentList) {
    char fileName[100] = "";
    char *componentId = malloc(sizeof(char) * 255);
    char *itemId = malloc(sizeof(char) * 255);


    FILE *file = NULL;
    do {
        printf("Introduzca la ruta fichero donde se encuentran los identificadores\n> ");
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {

        fscanf(file, "%s ", componentId);
        struct component *component = getComponentById(componentList, componentId);
        printf("Componente escaneado: %s\n", componentId);
        fscanf(file, "%s\n", itemId);
        if (component == NULL) {
            printf("No se ha encontrado el componente...\n");
            continue;
        }

        printf("Art%cculo escaneado: %s\n", 161, itemId);
        struct item *item = getItemOnComponent(itemId, component);
        if (item == NULL) {
            printf("\nNo se ha encontrado el art%cculo...\n", 161);
            continue;
        }
        printf("\nEliminando el art%cculo con identificador %s...\n", 161, itemId);

        deleteItem(component->items, item);
    }
    free(componentId);
    free(itemId);
}

/**
 * Search for an item in a component
 * @param itemId
 * @param component
 * @return the item if found, NULL if not
 */
struct item *getItemOnComponent(char *itemId, struct component *component) {
    if (component->items == NULL) return NULL;
    struct item *item = component->items->next;
    while (item != NULL) {
        if (strcmp(item->generalId, itemId) == 0) return item;
        item = item->next;
    }

    return NULL;
}
