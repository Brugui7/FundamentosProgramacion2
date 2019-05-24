/**
 * @file
 * @brief Application to manage phone contacts
 * @author Alejandro Brugarolas
 * @since 2018-05
 */

#include <stdio.h>
#include "model/structs.h"
#include "functions/Contact.h"


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu(contact *contacts) {
    int option = 0;
    while (option != 4) {
        printf("\n############### MENU BOLET%cN 4 EJERCICIO 1 ###############\n"
               "Indique que acci%cn desea realizar\n"
               "\t1. Crear contacto nuevo\n"
               "\t2. Buscar contacto por nombre\n"
               "\t3. Buscar contacto por %cmero\n"
               "\t4. Salir\n", I_ACUTE, O_ACUTE, U_ACUTE);
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                contacts = addContactOption(contacts);
                break;
            case 2:
                //contacts = addContactOption(contacts);
                break;
            case 3:
                //contacts = addContactOption(contacts);
                break;
            default:
                printf("Por favor seleccione una opci%cn v%clida\n", O_ACUTE, A_ACUTE);
                break;
        }
    }
}


int main() {
    contact *contacts = NULL;
    showMenu(contacts);
    //destroyEverything(componentList);


}