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

#define MAX_COMPONENTS 10
#define MAX_ITEMS 100

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;

struct item {
    bool valid; //Used to check if the struct is empty or not
    char generalId[5];
    int id;
    char model[10];
    char brand[10];
    struct tm insertDate;
    int stock;
    enum type {
        notDefined = 1, software = 2, hardware = 3
    } type;
    float itemPrice;
    float shippingPrice;
};

struct component {
    bool valid; //Used to check if the struct is empty or not
    char id[10];
    char name[20];
    char description[150];
    int stock;
    struct item items[MAX_ITEMS];
};

void createComponentOption();
bool addComponent(struct component component);
char componentToString(struct component component);

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
    int componentNumber = 0;

    struct component component;
    do{
        printf("Introduzca la cantidad de componentes que desa crear\n> ");
        scanf("%d", &componentNumber);
        fflush(stdin);
    } while (componentNumber <= 0 || componentNumber > MAX_COMPONENTS);

    for (int i = 0; i < componentNumber; i++) {
        printf("\nId: \n");
        scanf("%c", component.id);
        fflush(stdin);
        printf("Nombre: \n");
        gets(component.name);
        fflush(stdin);
        printf("Descripcion: \n");
        gets(component.description);
        fflush(stdin);
        printf("Stock: \n");
        scanf("%d", &component.stock);
        fflush(stdin);
        if (addComponent(component)){
            printf("Componente guardado correctamente");
        } else {
            printf("La tienda est%c llena, no es posible crear m%cs componentes, elimine algunos primero\n", A_ACUTE, A_ACUTE);
            break;
        }
    }
}

/**
 * Saves a component in the first free position of the array
 * @param component struct to add
 * @return boolean if added correctly
 */
bool addComponent(struct component component) {
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (!components[i].valid){
            component.valid = true;
            components[i] = component;
            return true;
        }
    }
    return false;
}

int main() {

    showMenu();
}
