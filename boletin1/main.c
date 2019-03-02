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
#include <conio.h>

#define MAX_COMPONENTS 11
#define MAX_ITEMS 100
#define ID_LENGTH 11
#define GENERAL_ID_LENGTH 21
#define NAME_LENGTH 21
#define DESCRIPTION_LENGTH 151
#define NOT_DEFINED 0
#define SOFTWARE 1
#define HARDWARE 2

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;


struct item {
    bool valid; //Used to check if the struct is empty or not
    char generalId[GENERAL_ID_LENGTH];
    int id;
    char model[16];
    char brand[16];
    struct tm insertDate;
    int stock;
    enum type {
        notDefined = NOT_DEFINED, software = SOFTWARE, hardware = HARDWARE
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
    int numberOfItems;
    struct item items[MAX_ITEMS];
};

void createComponentOption();

void deleteComponentOption(); //TODO, indicar que los artículos asociados se borrarán

void createItemOption();

void showStockOption();

void saveDataOption();

bool addComponent(struct component component);

bool addItem(struct item item, int componentPosition);

int getComponentPositionById(char* id);

void showComponent(struct component component);

void showItem(struct item item);

char* createItemId(struct item item, char componentId);

struct component components[MAX_COMPONENTS];

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
            case 2:
                deleteComponentOption();
                break;
            case 3:
                createItemOption();
                break;
            case 4:
                //TODO
            break;
            case 5:
                saveDataOption();
                break;
            case 7:
                showStockOption();
                break;
            case 8:
                printf("Saliendo...");
                break;
            default:
                printf("tu opción %d", option);
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
        fscanf(file, "%s\n", component.id);
        fgets(component.name, sizeof(component.name), file);
        strtok(component.name, "\n"); //Removes the \n
        fgets(component.description, sizeof(component.description), file);
        strtok(component.description, "\n");
        fscanf(file, "%d\n", &component.stock);
        printf("Componente detectado...\n");
        showComponent(component);
        printf(addComponent(component) ? "Componente guardado correctamente\n" : "Error al guardar el componente\n");

    }
    fclose(file);
}

/**
 * Asks for the file where the components id are stored in and tries to delete all of them
 */
void deleteComponentOption() {
    char fileName[100] = "";
    char code[ID_LENGTH] = "";

    FILE *file = NULL;
    do {
        printf("Introduzca la ruta fichero donde se encuentran los identificadores\n> ");
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {
        fscanf(file, "%s\n", code);
        if (getComponentPositionById(code) != -1) {
            printf("Eliminando el componente con identificador %s...\n", code);
        } else {
            printf("No se ha encontrado el componente con identificador %s...\n", code);
        }
    }

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
    do {
        printf("Introduzca la ruta del fichero donde se encuentran los art%cculos\n> ", I_ACUTE);
        gets(fileName);
        printf("%s", fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    } while (file == NULL);

    while (!feof(file)) {
        char* type;
        char componentId[ID_LENGTH] = "";
        struct item item = {NULL};
        fscanf(file, "%s\n", componentId);
        fscanf(file, "%d/%d/%d\n", &item.insertDate.tm_mday, &item.insertDate.tm_mon, &item.insertDate.tm_year);
        fgets(item.model, sizeof(item.model), file);
        strtok(item.model, "\n");
        fgets(item.brand, sizeof(item.brand), file);
        strtok(item.brand, "\n");
        fscanf(file, "%s\n", type);
        if (strcmp(type, "Hardware") == 0) {
            item.type = HARDWARE;
        } else if (strcmp(type, "Software") == 0) {
            item.type = SOFTWARE;
        } else {
            item.type = NOT_DEFINED;
        }

        fscanf(file, "%f %f\n", &item.itemPrice, &item.shippingPrice);
        fscanf(file, "%d\n", &item.stock);
        printf("Art%cculo detectado...\n", I_ACUTE);
        showItem(item);
        int componentPosition = getComponentPositionById(componentId);
        if (componentPosition == -1){
            printf("No se ha encontrado el componente para asociar este art%cculo", I_ACUTE);
            continue;
        }
        if (addItem(item, componentPosition)){
            printf("Art%cculo guardado correctamente\n", I_ACUTE);
        } else {
             printf("Error al guardar el rt%cculo\n", I_ACUTE);
        }

    }
    fclose(file);

}

void showStockOption(){
    printf("\n/****** STOCK TIENDA COMPONENTES INFORM%cTICOS ******/\n", A_ACUTE);
    for(int i = 0; i < MAX_COMPONENTS; i++){
        if (!components[i].valid) break;
        showComponent(components[i]);
        for (int j = 0; j < MAX_ITEMS; ++j) {
            if (!components[i].items[j].valid) break;
            showItem(components[i].items[j]);
        }

    }
    printf("\n/****** FIN ******/\nPulse una tecla para continuar...\n");
}

/**
 * Saves the components array to a file
 */
void saveDataOption(){
    char fileName[100] = "";
    int success = 0;
    FILE *file = NULL;
    do {
        printf("Introduzca la ruta del fichero donde desea guardar los datos\n> ");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "wb");
    } while (file == NULL);

    success = fwrite(&components, sizeof(struct component), MAX_COMPONENTS, file);
    printf(success == 0 ? "Error al guardar los datos\n" : "Datos guardados correctamente\n");
    fclose(file);
}

/**
 * Search for a component in the array
 * @param id identifier of a component
 * @return the component position if found or -1 if not
 */
int getComponentPositionById(char* id) {
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (strcmp(components[i].id, id) == 0) {
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
int getItemPositionOnComponent(char itemId, char componentId) {
    int componentPosition = getComponentPositionById(&componentId);
    if (componentPosition == -1) return -2;
    struct item *items = components[componentPosition].items;
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (strcmp(items[i].generalId, &itemId) == 0) {
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
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (!components[i].valid) {
            component.valid = true;
            components[i] = component;
            return true;
        }
    }
    return false;
}

/**
 * Saves a component in the first free position of the array
 * @param item struct to add
 * @param componentPosition place where the component is
 * @return boolean if added correctly
 */
bool addItem(struct item item, int componentPosition) {
    struct component component = components[componentPosition];
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (!component.items[i].valid) {
            item.valid = true;
            char generalId[GENERAL_ID_LENGTH];
            strftime(generalId, sizeof(generalId), "%d_%m_%y", &item.insertDate);
            sprintf(item.generalId, "%s_%d_%s", component.id, i, generalId);
            components[componentPosition].items[i] = item;
            return true;
        }
    }
    return false;
}

/**
 *
 * @param component
 */
void showComponent(struct component component) {
    printf("---------------------------------------\n"
           "Componente %s\n"
           "---------------------------------------\n"
           "Nombre: %s\nDescripci%cn: %s\nStock General: %d\n\n", component.id, component.name, O_ACUTE,
           component.description, component.stock);

}

/**
 *
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
           I_ACUTE, item.generalId, item.model, item.brand, item.stock, item.itemPrice, item.shippingPrice, type);
}

int main() {

    showMenu();
}
