/**
 * @file
 * @brief Application to manage phone contacts
 * @author Alejandro Brugarolas
 * @since 2019-05
 */

#include <stdio.h>
#include "model/structs.h"
#include "functions/City.h"


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu(city *cities) {
    int option = 0;
    while (option != 3) {
        printf("\n############### MENU BOLET%cN 4 EJERCICIO 2 ###############\n"
               "Indique que acci%cn desea realizar\n"
               "\t1. Comprobar validez del fichero\n"
               "\t2. Obtener ruta m%cs corta\n"
               "\t3. Salir\n", I_ACUTE, O_ACUTE, A_ACUTE);
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                validateOption(cities);
                break;
            case 2:
                //findShortestPath(cities);
                break;
            case 3:
                printf("Saliendo...");
                break;
            default:
                printf("Por favor seleccione una opci%cn v%clida\n", O_ACUTE, A_ACUTE);
                break;
        }
    }
}


int main() {

    city *cities = loadFile();
    showMenu(cities);
    //destroyEverything(contacts);
}