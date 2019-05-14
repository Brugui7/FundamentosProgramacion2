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
#include "Item.h"

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

/**
 * Asks for the file where te components are stored in and tries to read all of them
 * @param componentList
 * @return componentList updated
 */
struct component *createComponentOption(struct component *componentList) {
    char fileName[100] = "";
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length, bufferSize = 255;
    bool error;

    FILE *file = NULL;
    do {
        printf("Introduzca la ruta del fichero donde se encuentran los componentes\n> ");
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {

        struct component *component = (struct component *) malloc(sizeof(struct component));
        fscanf(file, "%s\n", buffer);
        length = strlen(buffer);
        component->id = (char *) malloc((length + 11) * sizeof(char));
        strncpy(component->id, buffer, length + 1);

        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n"); //Removes the \n
        length = strlen(buffer);
        component->name = (char *) malloc((length + 1) * sizeof(char));
        strncpy(component->name, buffer, length + 1);


        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n");
        length = strlen(buffer);
        component->description = (char *) malloc((length + 1) * sizeof(char));
        strncpy(component->description, buffer, length + 1);

        fscanf(file, "%d\n", &component->stock);
        printf("Componente detectado...\n");
        showComponent(*component);

        error = false;
        //Checks that all fields are valid
        if (strlen(component->id) == 0 || strlen(component->name) == 0 || strlen(component->description) == 0) {
            error = true;
            printf("Error: Uno o más campos son inválidos\n");
        }
        //Checks that there is not a component with the same id
        if (getComponentById(componentList, component->id) != NULL) {
            error = true;
            printf("Error: Ya existe un componente con el mismo identificador\n");
        }

        if (!error) {
            printf("Componente guardado correctamente\n");
            componentList = addComponent(componentList, component);
        }


    }
    fclose(file);
    free(buffer);
    return componentList;
}


/**
 * Asks for the file where the components id are stored in and tries to delete all of them
 * @param componentList
 */
void deleteComponentOption(struct component *componentList) {
    int confirm;
    char fileName[100] = "";
    char *componentId = malloc(sizeof(char) * 255);


    FILE *file = NULL;
    do {
        printf("Introduzca la ruta fichero donde se encuentran los identificadores\n> ");
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {
        fscanf(file, "%s\n", componentId);
        struct component *component = getComponentById(componentList, componentId);
        if (component != NULL) {
            if (component->items != NULL) {
                confirm = 2;
                do {
                    printf("Este componente contiene art%cculos que ser%cn eliminados.\n"
                           "%cDesea continuar?(1 = si | 2 = no)\n> ", 161, 160, 168);
                    scanf("%d", &confirm);
                    fflush(stdin);
                } while (confirm != 0 && confirm != 1);
                if (confirm == 0) continue;
            }
            printf("Eliminando el componente con identificador %s...\n", componentId);

            //Deletes all the component's items
            struct item *item = component->items;
            if (item != NULL) {
                item = item->next;
                while (item != NULL) {
                    deleteItem(component->items, item);
                    item = item->next;
                }
            }

            deleteComponent(componentList, component);

        } else {
            printf("No se ha encontrado el componente con identificador %s...\n", componentId);
        }
    }
    free(componentId);

}