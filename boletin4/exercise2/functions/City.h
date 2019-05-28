/**
 * @file
 * @brief Functions definition for City
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/
#ifndef FUNDAMENTOS2_CITY_H
#define FUNDAMENTOS2_CITY_H

const char A_ACUTE;
const char E_ACUTE;
const char I_ACUTE;
const char O_ACUTE;
const char U_ACUTE;
const char OPEN_QUESTION_MARK;

#include "../model/structs.h"

city *addCity(city *cities, city *newCity);

void addRoad(city *from, city *to, int distance);

city *loadFile();

city *getCityByName(city *cities, char *name);

#endif //FUNDAMENTOS2_CITY_H
