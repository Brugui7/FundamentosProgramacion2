/**
 * @file
 * @brief Application to manage the stock of a shop with dynamic memory allocation (With no global variables)
 * @author Alejandro Brugarolas
 * @since 2018-03
 * @version 2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "model/structs.h"
#include "function/Item.h"
#include "function/Component.h"

#define NOT_DEFINED 0
#define SOFTWARE 1
#define HARDWARE 2

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;
const char OPEN_QUESTION_MARK = 168;


struct component *createComponentOption(struct component *componentList);

void deleteComponentOption(struct component *componentList);

void showStockOption(struct component *componentList);

struct component *createItemOption(struct component *componentList);

void deleteItemOption(struct component *componentList);

/**
 * Search for a item in a component
 * @param itemId
 * @param component
 * @return
 */
struct item *getItemOnComponent(char *itemId, struct component *component);

/**
 * Search for a item in a component
 * @param itemId
 * @param component
 * @return the item if found, NULL if not
 */
struct item *getItemOnComponent(char *itemId, struct component *component);


/**
 * Shows all the options and calls the appropriate function depending of the choosen option
 */
void showMenu(struct component *componentList) {
    int option = 0;
    while (option != 6) {
        printf("\n############### MENU BOLET%cN 3 ###############\n"
               "Indique que acci%cn desea realizar\n"
               "\t1. Crear componentes\n"
               "\t2. Eliminar componentes\n"
               "\t3. Crear art%cculos\n"
               "\t4. Eliminar art%cculos\n"
               "\t5. Listar datos del stock de la tienda\n"
               "\t6. Salir\n", I_ACUTE, O_ACUTE, I_ACUTE, I_ACUTE);
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                componentList = createComponentOption(componentList);
                break;
            case 2:
                deleteComponentOption(componentList);
                break;
            case 3:
                componentList = createItemOption(componentList);
                break;
            case 4:
                deleteItemOption(componentList);
                break;
            case 5:
                showStockOption(componentList);
                break;
            case 6:
                printf("Saliendo...");
                break;
            default:
                printf("Por favor seleccione una opci%cn v%clida\n", O_ACUTE, A_ACUTE);
                break;
        }
    }
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
                           "%cDesea continuar?(1 = si | 2 = no)\n> ", I_ACUTE, A_ACUTE, OPEN_QUESTION_MARK);
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
        printf("Introduzca la ruta del fichero donde se encuentran los art%cculos\n> ", I_ACUTE);
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
        printf("Art%cculo detectado...\n", I_ACUTE);

        struct component *component = getComponentById(componentList, componentId);
        if (component == NULL) {
            printf("No se ha encontrado el componente para asociar este art%cculo", I_ACUTE);
            continue;
        }

        component->items = addItem(component->items, item, componentId, ++component->itemsNumber);
        printf("Art%cculo guardado correctamente\n", I_ACUTE);
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

        printf("Art%cculo escaneado: %s\n", I_ACUTE, itemId);
        struct item *item = getItemOnComponent(itemId, component);
        if (item == NULL) {
            printf("\nNo se ha encontrado el art%cculo...\n", I_ACUTE);
            continue;
        }
        printf("\nEliminando el art%cculo con identificador %s...\n", I_ACUTE, itemId);

        deleteItem(component->items, item);
    }
    free(componentId);
    free(itemId);
}

/**
 * Shows the stock or an error if there aren't components
 * @param componentList
 */
void showStockOption(struct component *componentList) {

    if (componentList == NULL) {
        printf("Error: La tienda no tiene componentes...");
        return;
    }
    printf("\n/****** STOCK TIENDA COMPONENTES INFORM%cTICOS ******/\n", A_ACUTE);
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



int main() {
    componentList componentList = createCompoentList();
    showMenu(componentList);
    //free(components);
}
