/**
 * @file
 * @brief Independent component functions
 * @author: Alejandro Brugarolas
 * @since: 2019-03-15
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/Component.h"

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
 * Compares two components name and returns which one goes before based in alphabetical order
 * @param paramComponent1 the first component
 * @param paramComponent2 the second component
 * @return int strcmp result
 */
int compareNames(const void *paramComponent1, const void *paramComponent2) {
    const struct component *component1 = paramComponent1;
    const struct component *component2 = paramComponent2;
    return strcmp(component1->name, component2->name);
}

/**
 * Sorts an array of components by their names in ascending order
 * @param components
 */
void sortComponentsByName(struct component *components, size_t componentsSize) {
    qsort(components, componentsSize, sizeof(struct component), compareNames);
}


/**
 * Saves a component in the first free position of the array
 * @param component struct to add
 * @return boolean if added correctly
 *//*
struct component* addComponent(struct component *component) {
    //Checks that all fields are valid
    if (strlen(component->id) == 0 || strlen(component->name) == 0 || strlen(component->description) == 0) return false;
    //Checks that there is not a component with the same id
    //if (getComponentPositionById(component->id) != -1) return false;

    if (componentsNumber == 0) {
        components = (struct component *) malloc(sizeof(struct component));
        component->next = NULL;
        component->previous = NULL;
        components->previous = components->next = component;
        componentsNumber++;
    } else {
        component->previous = components->previous; //The previous component of the new one, is the actual last one
        component->next = NULL;
        components->previous->next = component; //the next component of the actual last one, will be the new one
        components = (struct component *) realloc(components, (++componentsNumber) * sizeof(struct component));
    }
    return true;
}*/