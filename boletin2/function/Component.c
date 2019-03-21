/**
 * @file
 * @brief Independent component functions
 * @author: Alejandro Brugarolas
 * @since: 2019-03-15
*/
#include <stdio.h>
#include "../model/Component.h"

/**
 * Prints the component data
 * @param component
 */
void showComponent(struct component component) {
    printf("---------------------------------------\n"
           "Componente %s\n"
           "---------------------------------------\n"
           "Nombre: %s\nDescripci%cn: %s\nStock General: %d\n\n", component.id, component.name,
           162, component.description, component.stock);

}