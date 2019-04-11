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

bool addComponent(struct component *component);

void createComponentOption();

void deleteComponentOption();


void showStockOption();

bool addItem(struct item *item, struct component *component);

void createItemOption();

void deleteItemOption();

int getComponentPositionById(char *id);

struct component *getComponentById(char *id);

/**
 * Deletes an Item
 * @param component
 * @param item
 * @return bool if deleted
 */
bool deleteItem(struct component *component, struct item *item);

/**
 * Search for a item in a component
 * @param itemId
 * @param component
 * @return the item if found, NULL if not
 */
struct item *getItemOnComponent(char *itemId, struct component *component);

struct component *components = NULL;
int componentsNumber = 0;

/**
 * Shows all the options and calls the appropriate function depending of the choosen option
 */
void showMenu() {
    int option = 0;
    while (option != 6) {
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
        printf(addComponent(component) ? "Componente guardado correctamente\n"
                                       : "Ya existe un componente con el mismo identificador\n");

    }
    fclose(file);
    free(buffer);
//    sortComponentsByName(components, (size_t) (componentsNumber - 1));
}

/**
 * Asks for the file where the components id are stored in and tries to delete all of them
 */
void deleteComponentOption() {
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
        struct component *component = getComponentById(componentId);
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
                    deleteItem(component, item);
                    item = item->next;
                }
            }


            if (component->next == NULL && component->previous == NULL) {
                //There is only one component
                components = NULL;
            } else if (component->next == NULL) {
                //This is the last component
                components->previous = component->previous;
                component->previous->next = NULL;
            } else if (component->previous == NULL) {
                //This is the first component
                components->next = component->next;
                component->next->previous = NULL;
            } else {
                component->next->previous = component->previous;
                component->previous->next = component->next;
            }
            free(component);
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
        struct component *component = getComponentById(componentId);
        if (component == NULL) {
            printf("No se ha encontrado el componente para asociar este art%cculo", I_ACUTE);
            continue;
        }
        if (addItem(item, component)) {
            printf("Art%cculo guardado correctamente\n", I_ACUTE);
            showItem(*item);
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
        struct component *component = getComponentById(componentId);
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

        deleteItem(component, item);
    }
    free(componentId);
    free(itemId);
}

/**
 * Shows the stock or an error if there aren't components
 */
void showStockOption() {

    if (components == NULL) {
        printf("Error: La tienda no tiene componentes...");
        return;
    }
    printf("\n/****** STOCK TIENDA COMPONENTES INFORM%cTICOS ******/\n", A_ACUTE);
    struct component *component = components->next;
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
 * Deletes an Item
 * @param component
 * @param item
 * @return bool if deleted
 */
bool deleteItem(struct component *component, struct item *item) {

    if (item->next == NULL && item->previous == NULL) {
        component->items = NULL;
    } else if (item->next == NULL) {
        component->items->previous = item->previous;
        component->items->previous->next = NULL;
    } else if (item->previous == NULL) {
        component->items->next = item->next;
        item->next->previous = NULL;

    } else {
        item->next->previous = item->previous;
        item->previous->next = item->next;
    }
    free(item);
}

/**
 * Search for a component in the list
 * @param id identifier of a component
 * @return a pointer to the component if found, null if not
 */
struct component *getComponentById(char *id) {
    if (components == NULL) return NULL;
    struct component *component = components->next;
    while (component != NULL) {
        if (strcmp(component->id, id) == 0) return component;
        component = component->next;
    }
    return NULL;
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

/**
 * Adds a component to the list and keeps the list ordered by the components names
 * @param component struct to add
 * @return boolean if added correctly
 */
bool addComponent(struct component *component) {
    //Checks that all fields are valid¿
    if (strlen(component->id) == 0 || strlen(component->name) == 0 || strlen(component->description) == 0) return false;
    //Checks that there is not a component with the same id
    if (getComponentById(component->id) != NULL) return false;
    component->items = NULL;
    component->itemsNumber = 0;

    if (components == NULL) {
        components = (struct component *) malloc(sizeof(struct component));
        component->next = NULL;
        component->previous = NULL;
        components->previous = components->next = component;
    } else {
        bool added = false;
        struct component *tempComponent = components->next;
        do {
            if (strcmp(tempComponent->name, component->name) > 0) {


                if (tempComponent->previous == NULL) {
                    //In this case, tempComponent is the first component
                    components->next = component;
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
            component->previous = components->previous; //The previous component of the new one, is the actual last one
            component->next = NULL;
            components->previous->next = component; //the next component of the actual last one, will be the new one
            components->previous = component; //Sets the new last component
        }

    }
    return true;
}

/**
 * Saves an item at the end of the list
 * @param item to add
 * @param pointer to component to add the item to
 * @return boolean if added correctly
 */
bool addItem(struct item *item, struct component *component) {
    item->next = NULL;

    if (component->items == NULL) {
        component->items = (struct item *) malloc(sizeof(struct item));
        item->previous = NULL;
        component->items->previous = component->items->next = item;
    } else {
        item->previous = component->items->previous; //The previous item of the new one, is the actual last one
        component->items->previous->next = item; //the next component of the actual last one, will be the new one
        component->items->previous = item; //Sets the new last component
    }
    char *aux = (char *) malloc(sizeof(char) * 9);
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length;
    //Creates and sets the item ID
    strftime(aux, 9, "%d_%m_%y", &item->insertDate); //This will be 9 always
    sprintf(buffer, "%s_%d_%s", component->id, ++component->itemsNumber, aux);
    length = strlen(buffer);
    item->generalId = (char *) malloc(++length * sizeof(char));
    strncpy(item->generalId, buffer, length);
    free(buffer);
    free(aux);
    return true;

}


int main() {
    showMenu();
    free(components);
}
