/**
 * Application to manage the stock of a shop, it can save the state by saving th data to and recovering it from files
 * @author Alejandro Brugarolas
 * @since 2018-02
 * @verison 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_COMPONENTS 11
#define MAX_ITEMS 100
#define ID_LENGTH 11
#define NAME_LENGTH 21
#define DESCRIPTION_LENGTH 151

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;


struct item {
    bool valid; //Used to check if the struct is empty or not
    char generalId[21];
    int id;
    char model[10];
    char brand[10];
    struct tm insertDate;
    int stock;
    enum type {
        notDefined = 0, software = 1, hardware = 2
    } type;
    float itemPrice;
    float shippingPrice;
};

struct component {
    bool valid; //Used to check if the struct is empty or not
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    char description[DESCRIPTION_LENGTH];
    int stock;
    struct item items[MAX_ITEMS];
};

void createComponentOption();
bool addComponent(struct component component);
bool addItemToComponent(struct item item, struct component component);
char componentToString(struct component component);
int getComponentPositionById(char id);
void showComponent(struct component component);

struct component components[MAX_COMPONENTS];

/**
 * Shows all the options and calls the appropriate function depending of the choosen option
 */
void showMenu() {
    int option = 0;
    while (option != 8) {
        printf("############### MENU ###############\n"
               "Indique que acci%cn desea realizar\n"
               "\t1. Crear componentes\n"
               "\t2. Eliminar componentes\n"
               "\t3. Crear art%cculos\n"
               "\t4. Eliminar art%cculos\n"
               "\t5. Guardar estado del programa\n"
               "\t6. Cargar estado de fichero\n"
               "\t7. Listar datos del stock de la tienda\n"
               "\t8. Salir\n", O_ACUTE, I_ACUTE, I_ACUTE);
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                createComponentOption();
                break;
            case 8:
                printf("Saliendo...");
                break;
            default:
                printf("Por favor seleccione una opci%cn v%clida\n", O_ACUTE, A_ACUTE);
                break;
        }
    }
}

void createComponentOption() {
    char fileName[100] = "";
    FILE *file = NULL;
    do  {
        printf("Introduzca el nombre del fichero donde se encuentran los componentes\n> ");
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)){
        struct component component = {NULL};
        fscanf(file, "%s\n", component.id);
        fgets(component.name, NAME_LENGTH, file);
        fgets(component.description, DESCRIPTION_LENGTH, file);
        fscanf(file, "%d\n", &component.stock);
        printf("Componente detectado...\n");
        showComponent(component);
        printf(addComponent(component) ? "Componente guardado correctamente\n" : "Error al guardar el componente\n");

    }
    fclose(file);
}

void createItemOption() {
    int itemNumber = 0;

    do{
        printf("Introduzca la cantidad de art%culos que desa crear\n> ", I_ACUTE);
        scanf("%d", &itemNumber);
        fflush(stdin);
    } while (itemNumber <= 0);

    for (int i = 0; i < itemNumber; i++) {
        struct item item;
        int type = -1;
        int inputDate = 0;
        char componentId = "";
        int componentPosition = -1;

        printf("\nId: \n");
        scanf("%d", item.id);
        fflush(stdin);

        printf("Marca: \n");
        gets(item.brand);
        fflush(stdin);

        printf("Modelo: \n");
        gets(item.model);
        fflush(stdin);

        printf("Stock: \n");
        scanf("%d", &item.stock);
        fflush(stdin);

        do{
            printf("Tipo (0 = indefinido, 1 = software, 2 = hardware): \n");
            scanf("%d", &type);
            fflush(stdin);
        } while (type < 0 || type > 2);
        item.type = type;

        printf("Precio: \n");
        scanf("%f", &item.itemPrice);
        fflush(stdin);
        printf("Precio del transporte: \n");
        scanf("%f", &item.shippingPrice);
        fflush(stdin);

        do{
            printf("Seleccione si desea itroducir la fecha de alta (1) o usar la fecha actual (0):\n> ");
            scanf("%d", &inputDate);
            fflush(stdin);
        } while (inputDate != 0 && inputDate != 1);
        if (inputDate == 0){
            time_t sysTime;
            time(&sysTime);
            item.insertDate = *localtime(&sysTime);
        } else {
            printf("Introduzca la fecha de alta (DD/MM/YYYY):");
            scanf("%d/%d/%d", &item.insertDate.tm_mday, &item.insertDate.tm_mon, &item.insertDate.tm_year);
            fflush(stdin);
        }

        //It will be asking for a component until the user introduces a valid one or cancels the item creation
        while (componentPosition == -1){
            printf("Introduzca el identificador del componente al que quiere asociar este art%cculo "
                   "o \"cancelar\" para cancelar el alta:\n> ", I_ACUTE);
            gets(&componentId);
            fflush(stdin);
            if (strcmp("cancelar", &componentId) == 0){
                printf("Cancelando...\n");
                return;
            }

            componentPosition = getComponentPositionById(componentId);
            if (componentPosition == -1){
                printf("No se han encontrado componentes con el identificador introducido\n");
            }
        }
    }

}

/**
 * Search for a component in the array
 * @param id identifier of a component
 * @return the component position if found or -1 if not
 */
int getComponentPositionById(char id){
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (strcmp(components[i].id, &id) == 0){
            return i;
        }
    }
    return -1;
}

/**
 * Search for a item in a component
 * @param itemId
 * @param componentId the general one
 * @return the item position if found, -1 if not, -2 if the component couldn't be found
 */
int getItemPositionOnComponent(char itemId, char componentId){
    int componentPosition = getComponentPositionById(componentId);
    if (componentPosition == -1) return -2;
    struct item *items = components[componentPosition].items;
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (strcmp(items[i].generalId, &itemId) == 0){
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
    if (strlen(component.id) == 0 || strlen(component.name) == 0 || strlen(component.description) == 0) return false;
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (!components[i].valid){
            component.valid = true;
            components[i] = component;
            return true;
        }
    }
    return false;
}

void showComponent(struct component component){
    printf("|%s| |%s| |%s| |%d|\n", component.id, component.name, component.description, component.stock);
}

int main() {

    showMenu();
}
