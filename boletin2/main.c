/**
 * @file
 * @brief Application to manage the stock of a shop with dynamic memory allocation
 * @author Alejandro Brugarolas
 * @since 2018-02
 * @verison 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "model/Item.h"
#include "model/Component.h"

#define NOT_DEFINED 0
#define SOFTWARE 1
#define HARDWARE 2

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;
const char OPEN_QUESTION_MARK = 168;

bool addComponent(struct component component);

void createComponentOption();

void deleteComponentOption();

void showStockOption();

bool addItem(struct item item, int componentPosition);

void createItemOption();

void deleteItemOption();

int getComponentPositionById(char *id);
/**
 * Search for a item in a component
 * @param itemId
 * @param componentPosition
 * @return the item position if found, -1 if not
 */
int getItemPositionOnComponent(char *itemId, int componentPosition);

struct component *components = NULL;
int componentsNumber = 0;

/**
 * Shows all the options and calls the appropriate function depending of the choosen option
 */
void showMenu() {
    int option = 0;
    while (option != 8) {
        printf("\n############### MENU ###############\n"
               "Indique que acci%cn desea realizar\n"
               "\t1. Crear componentes\n"
               "\t2. Eliminar componentes\n"
               "\t3. Crear art%cculos\n"
               "\t4. Eliminar art%cculos\n"
               "\t5. Listar datos del stock de la tienda\n"
               "\t6. Salir\n", O_ACUTE, I_ACUTE, I_ACUTE);
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                createComponentOption();
                break;
            case 2:
                deleteComponentOption();
                break;
            case 3:
                createItemOption();
                break;
            case 4:
                deleteItemOption();
                break;
            case 5:
                showStockOption();
                break;
            case 6:
                printf("Saliendo...");
                free(components);
                break;
            default:
                printf("Por favor seleccione una opci%cn v%clida\n", O_ACUTE, A_ACUTE);
                break;
        }
    }
}

/**
 * Asks for the file where te components are stored in and tries to read all of them
 */
void createComponentOption() {
    char fileName[100] = "";
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length, bufferSize = 255;

    FILE *file = NULL;
    do {
        printf("Introduzca la ruta del fichero donde se encuentran los componentes\n> ");
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {

        struct component component = {NULL};
        fscanf(file, "%s\n", buffer);
        length = strlen(buffer);
        component.id = (char *) malloc((length + 1) * sizeof(char));
        strncpy(component.id, buffer, length + 1);

        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n"); //Removes the \n
        length = strlen(buffer);
        component.name = (char *) malloc((length + 1) * sizeof(char));
        strncpy(component.name, buffer, length + 1);


        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n");
        length = strlen(buffer);
        component.description = (char *) malloc((length + 1) * sizeof(char));
        strncpy(component.description, buffer, length + 1);

        fscanf(file, "%d\n", &component.stock);
        printf("Componente detectado...\n");
        showComponent(component);
        printf(addComponent(component) ? "Componente guardado correctamente\n"
                                       : "Ya existe un componente con el mismo identificador\n");

    }
    fclose(file);
    free(buffer);
    sortComponentsByName(components, (size_t) (componentsNumber - 1));
}

/**
 * Asks for the file where the components id are stored in and tries to delete all of them
 */
void deleteComponentOption() {
    int confirm, componentPosition;
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
        componentPosition = getComponentPositionById(componentId);
        if (componentPosition != -1) {
            if (components[componentPosition].itemsNumber > 0) {
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
            for (int i = componentPosition; i < componentsNumber - 1; i++) {
                components[i] = components[i + 1];
            }
            components = (struct component *) realloc(components, --componentsNumber * sizeof(struct component));
        } else {
            printf("No se ha encontrado el componente con identificador %s...\n", componentId);
        }
    }
    free(componentId);
    sortComponentsByName(components, (size_t) (componentsNumber - 1));
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
 */
void createItemOption() {
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

        struct item item = {NULL};
        fscanf(file, "%s\n", buffer);
        length = strlen(buffer);
        componentId = (char *) malloc(++length * sizeof(char));
        strncpy(componentId, buffer, length);

        fscanf(file, "%d/%d/%d\n", &item.insertDate.tm_mday, &item.insertDate.tm_mon, &item.insertDate.tm_year);
        item.insertDate.tm_mon -= 1;

        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n");
        length = strlen(buffer);
        item.model = (char *) malloc(++length * sizeof(char));
        strncpy(item.model, buffer, length);


        fgets(buffer, bufferSize, file);
        strtok(buffer, "\n");
        length = strlen(buffer);
        item.brand = (char *) malloc(++length * sizeof(char));
        strncpy(item.brand, buffer, length);


        fscanf(file, "%s\n", buffer);
        if (strcmp(buffer, "Hardware") == 0) {
            item.type = HARDWARE;
        } else if (strcmp(buffer, "Software") == 0) {
            item.type = SOFTWARE;
        } else {
            item.type = NOT_DEFINED;
        }

        fscanf(file, "%f %f\n", &item.itemPrice, &item.shippingPrice);
        fscanf(file, "%d\n", &item.stock);
        printf("Art%cculo detectado...\n", I_ACUTE);
        showItem(item);
        int componentPosition = getComponentPositionById(componentId);
        if (componentPosition == -1) {
            printf("No se ha encontrado el componente para asociar este art%cculo", I_ACUTE);
            continue;
        }
        if (addItem(item, componentPosition)) {
            printf("Art%cculo guardado correctamente\n", I_ACUTE);
        } else {
            printf("Error al guardar el rt%cculo\n", I_ACUTE);
        }
        free(componentId);

    }
    fclose(file);
    free(buffer);

}


/**
 * Asks for the file where the components and items id are stored in and tries to delete all of them
 * Expected format: "componentId itemId"
 */
void deleteItemOption() {
    int componentPosition, itemPosition;
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
        componentPosition = getComponentPositionById(componentId);
        printf("Componente escaneado: %s\n", componentId);
        fscanf(file, "%s\n", itemId);
        if (componentPosition == -1) {
            printf("No se ha encontrado el componente...\n");
            continue;
        }

        printf("Art%cculo escaneado: %s\n", I_ACUTE, itemId);
        itemPosition = getItemPositionOnComponent(itemId, componentPosition);
        if (itemPosition == -1) {
            printf("\nNo se ha encontrado el art%cculo...\n", I_ACUTE);
            continue;
        }
        printf("\nEliminando el art%cculo con identificador %s...\n", I_ACUTE, itemId);
        struct component *component = &components[componentPosition];
        for (int i = itemPosition; i < component->itemsNumber - 1; i++) {
            component->items[i] = component->items[i + 1];
        }
        component->items = (struct item *) realloc(component->items, --component->itemsNumber * sizeof(struct item));
    }
    free(componentId);
    free(itemId);
}

void showStockOption() {
    printf("\n/****** STOCK TIENDA COMPONENTES INFORM%cTICOS ******/\n", A_ACUTE);
    for (int i = 0; i < componentsNumber; i++) {
        struct component component = components[i];
        showComponent(component);
        for (int j = 0; j < component.itemsNumber; ++j) {
            showItem(component.items[j]);
        }

    }
    printf("\n/****** FIN ******/\n");
}

/**
 * Search for a component in the array
 * @param id identifier of a component
 * @return the component position if found or -1 if not
 */
int getComponentPositionById(char *id) {
    for (int i = 0; i < componentsNumber; i++) {
        if (strcmp(components[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Search for a item in a component
 * @param itemId
 * @param componentPosition
 * @return the item position if found, -1 if not
 */
int getItemPositionOnComponent(char *itemId, int componentPosition) {
    struct item *items = components[componentPosition].items;
    for (int i = 0; i < components[componentPosition].itemsNumber; i++) {
        if (strcmp(items[i].generalId, itemId) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Saves a component in the first free position of the array
 * @param component struct to add
 * @return boolean if added correctly
 */
bool addComponent(struct component component) {
    //Checks that all fields are valid
    if (strlen(component.id) == 0 || strlen(component.name) == 0 || strlen(component.description) == 0) return false;
    //Checks that there is not a component with the same id
    if (getComponentPositionById(component.id) != -1) return false;

    if (componentsNumber == 0) {
        components = (struct component *) malloc(sizeof(struct component));
        componentsNumber++;
    } else {
        components = (struct component *) realloc(components, (++componentsNumber) * sizeof(struct component));
    }
    components[componentsNumber - 1] = component;
    return true;
}

/**
 * Saves a component in the first free position of the array
 * @param item struct to add
 * @param componentPosition place where the component is
 * @return boolean if added correctly
 */
bool addItem(struct item item, int componentPosition) {
    struct component *component = &components[componentPosition];
    if (component->itemsNumber == 0) {
        component->items = (struct item *) malloc(sizeof(struct item));
        component->itemsNumber++;
    } else {
        component->items = (struct item *) realloc(component->items, (++component->itemsNumber) * sizeof(struct item));
    }
    char *aux = (char *) malloc(sizeof(char) * 9);
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length;
    //Creates and sets the item ID
    strftime(aux, 9, "%d_%m_%y", &item.insertDate); //This will be 9 always
    sprintf(buffer, "%s_%d_%s", component->id, component->itemsNumber, aux);
    length = strlen(buffer);
    item.generalId = (char *) malloc(++length * sizeof(char));
    strncpy(item.generalId, buffer, length);

    component->items[component->itemsNumber - 1] = item;
    free(buffer);
    free(aux);
    return true;

}





int main() {

    showMenu();
    free(components);
}
