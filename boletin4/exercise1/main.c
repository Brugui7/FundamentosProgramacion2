/**
 * @file
 * @brief Application to manage phone contacts
 * @author Alejandro Brugarolas
 * @since 2019-05
 */

#include <stdio.h>
#include "model/structs.h"
#include "functions/Contact.h"


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu(contact *contacts) {
    int option = 0;
    while (option != 3) {
        printf("\n############### MENU BOLETÍN 4 EJERCICIO 1 ###############\n"
               "Indique que acción desea realizar\n"
               "\t1. Crear contacto nuevo\n"
               "\t2. Buscar contacto\n"
               "\t3. Salir\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                contacts = addContactOption(contacts);
                break;
            case 2:
                findContactOption(contacts);
                break;
            case 3:
                printf("Saliendo...");
                break;
            default:
                printf("Por favor seleccione una opción válida\n");
                break;
        }
    }
}


int main() {
    contact *contacts = NULL;
    showMenu(contacts);
    destroyBook(contacts);
}