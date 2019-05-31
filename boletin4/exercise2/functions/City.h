/**
 * @file
 * @brief Functions definition for City
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/
#ifndef FUNDAMENTOS2_CITY_H
#define FUNDAMENTOS2_CITY_H

#include "../model/structs.h"

city *addCity(city *cities, city *newCity);

void addRoad(city *from, city *to, int distance);

city *loadFile();

city *getCityByName(city *cities, char *name);

void validateOption(city *cities);

int countCities(city *cities);

void getMinDistanceOption(city *cities);

int getMinDistance(city *cities, city *from, city *to);

void destroyEverything(city *cities);

#endif //FUNDAMENTOS2_CITY_H
