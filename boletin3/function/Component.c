/**
 * @file
 * @brief Independent component functions
 * @author: Alejandro Brugarolas
 * @since: 2019-03
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../model/structs.h"
#include "Component.h"

/**
 * Prints the component data
 * @param component
 */
void showComponent(struct component component) {
    printf("---------------------------------------\n"
           "Componente %s\n"
           "---------------------------------------\n"
           "Nombre: %s\nDescripci%cn: %s\nStock General: %d\n\n", component.id, component.name,
           162, component.description, component.stock);
}

/**
 * Creates an empty list of components
 * @return NULL
 */
struct component *createCompoentList() {
    return NULL;
}

/**
 * Search for a component in the list
 * @param the list to search into
 * @param id identifier of a component
 * @return a pointer to the component if found, null if not
 */
struct component *getComponentById(struct component *componentList, char *id) {
    if (componentList == NULL) return NULL;
    struct component *component = componentList->next;
    while (component != NULL) {
        if (strcmp(component->id, id) == 0) return component;
        component = component->next;
    }
    return NULL;
}

/**
 * Adds a component to the list and keeps the list ordered by the components names
 * @param componentList
 * @param component
 * @return componentList updated with the new component
 */
struct component *addComponent(struct component *componentList, struct component *component) {

    component->items = NULL;
    component->itemsNumber = 0;

    if (componentList == NULL) {
        componentList = (struct component *) malloc(sizeof(struct component));
        component->next = NULL;
        component->previous = NULL;
        componentList->previous = componentList->next = component;
    } else {
        bool added = false;
        struct component *tempComponent = componentList->next;
        do {
            if (strcmp(tempComponent->name, component->name) > 0) {


                if (tempComponent->previous == NULL) {
                    //In this case, tempComponent is the first component
                    componentList->next = component;
                } else {
                    tempComponent->previous->next = component;
                }
                component->previous = tempComponent->previous;
                tempComponent->previous = component;
                component->next = tempComponent;
                added = true;
                break;
            }
            tempComponent = tempComponent->next;
        } while (tempComponent->next != NULL);
        if (!added) {
            component->previous = componentList->previous; //The previous component of the new one, is the actual last one
            component->next = NULL;
            componentList->previous->next = component; //the next component of the actual last one, will be the new one
            componentList->previous = component; //Sets the new last component
        }

    }
    return componentList;
}

/**
 * Deletes a component from the list
 * @param componentList The list
 * @param component The component
 */
void deleteComponent(struct component *componentList, struct component *component) {
    if (component->next == NULL && component->previous == NULL) {
        //There is only one component
        componentList = NULL;
    } else if (component->next == NULL) {
        //This is the last component
        componentList->previous = component->previous;
        component->previous->next = NULL;
    } else if (component->previous == NULL) {
        //This is the first component
        componentList->next = component->next;
        component->next->previous = NULL;
    } else {
        component->next->previous = component->previous;
        component->previous->next = component->next;
    }
    free(component->id);
    free(component->name);
    free(component->description);
    free(component->items);
    free(component);
}