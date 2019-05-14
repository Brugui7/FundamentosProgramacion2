/**
 * @file
 * @brief Application to manage the stock of a shop with dynamic memory allocation (With no global variables)
 * @author Alejandro Brugarolas
 * @since 2018-03
 * @version 2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "model/structs.h"
#include "function/Item.h"
#include "function/Component.h"
#include "function/Common.h"

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;
const char OPEN_QUESTION_MARK = 168;

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


int main() {
    componentList componentList = createCompoentList();
    showMenu(componentList);
    destroyEverything(componentList);


}
