/**
 * @file
 * @brief Independent city functions
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "City.h"

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;
const char OPEN_QUESTION_MARK = 168;

/**
 * Creates a new city
 * @param cities
 * @param newCity
 * @return
 */
city *addCity(city *cities, city *newCity) {
    newCity->road = NULL;
    newCity->next = cities == NULL ? NULL : cities;
    cities = newCity;
    return cities;
}

/**
 * Reads the file and returns the graph
 * @return graph of cities
 */
city *loadFile() {
    char fileName[100] = "";
    int distance;
    FILE *file = NULL;
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t bufferSize;
    city *cities = NULL;

    while (file == NULL) {
        printf("Introduzca la ruta al archivo de datos\n> ");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    }
    printf("Cargando datos...\n");

    //Cities insertion
    while (!feof(file)) {
        fscanf(file, "%s", buffer);
        buffer = strtok(buffer, ",");
        if (strcmp(buffer, "#") == 0) break;

        struct city *newCity = (city *) malloc(sizeof(struct city));
        bufferSize = strlen(buffer);
        newCity->name = (char *) malloc(sizeof(char) * (bufferSize + 1));
        strncpy(newCity->name, buffer, bufferSize + 1);
        cities = addCity(cities, newCity);
        printf("Ciuddad detectada:  %s\n", newCity->name);
    }

    //Roads insertion
    while (!feof(file)) {
        fscanf(file, "%s", buffer);
        struct city *from = getCityByName(cities, buffer);
        fscanf(file, "%s", buffer);
        struct city *to = getCityByName(cities, buffer);
        fscanf(file, "%d", &distance);

        if (from == NULL || to == NULL) {
            printf("Una de las dos ciudades conectadas no se pudo encontrar\n");
            continue;
        }

        printf("%s y %s est%cn separados por %d kn\n", from->name, to->name, A_ACUTE, distance);
        addRoad(from, to, distance);
    }


    fclose(file);
    free(buffer);
}

/**
 * Returns a city by it's name
 * @param cities list
 * @param name of the city
 * @return city or NULL if not found
 */
city *getCityByName(city *cities, char *name) {
    city *tempCity = cities;
    while (tempCity != NULL) {
        if (strcmp(tempCity->name, name) == 0) return tempCity;

        tempCity = tempCity->next;
    }
    return NULL;
}

/**
 * Adds a new road between two cities
 * @param from
 * @param to
 * @param distance
 */
void addRoad(city *from, city *to, int distance) {
    road *newRoad = (road *) malloc(sizeof(road));
    newRoad->to = to;
    newRoad->distance = distance;
    newRoad->next = from->road;
    from->road = newRoad;

}
