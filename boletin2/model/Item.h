/**
 * @file
 * @brief Data definition for item
 * @author: Alejandro Brugarolas
 * @since: 2019-03-15
*/

#ifndef FUNDAMENTOS2_ITEM_H
#define FUNDAMENTOS2_ITEM_H

#include <stdbool.h>
#include <time.h>

#define NOT_DEFINED 0
#define SOFTWARE 1
#define HARDWARE 2

struct item {
    bool valid; //Used to check if the struct is empty or not
    char *generalId;
    int id;
    char *model;
    char *brand;
    struct tm insertDate;
    int stock;
    enum type {
        notDefined = NOT_DEFINED, software = SOFTWARE, hardware = HARDWARE
    } type;
    float itemPrice;
    float shippingPrice;
};

void showItem(struct item item);


#endif //FUNDAMENTOS2_ITEM_H
