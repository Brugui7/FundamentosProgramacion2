/**
 * @file
 * @brief Independent item functions
 * @author: Alejandro Brugarolas
 * @since: 2019-03-15
*/

#include <stdio.h>
#include "../model/Item.h"

/**
 * Prints the item's data
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
           161, item.generalId, item.model, item.brand, item.stock, item.itemPrice, item.shippingPrice, type);
}
