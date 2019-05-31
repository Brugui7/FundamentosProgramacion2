/**
 * @file
 * @brief Independent city functions
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "City.h"

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

        printf("%s y %s están separados por %d kn\n", from->name, to->name, distance);
        addRoad(from, to, distance);
    }

    fclose(file);
    free(buffer);
    return cities;
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

/**
 * Returns the number of cities in the list
 * @return int
 */
int countCities(city *cities) {
    int count = 0;
    city *tempCity = cities;
    while (tempCity != NULL) {
        count++;
        tempCity = tempCity->next;
    }
    return count;
}

/**
 * Checks that there is not isolated cities and that every city can be reached from other city
 * @param cities list of cities
 */
void validateOption(city *cities) {
    int citiesNumber = countCities(cities);
    bool paths[citiesNumber][citiesNumber];
    int i, j, k;

    city *tempCityI = cities;
    city *tempCityJ;
    for (i = 0; i < citiesNumber; i++) {
        tempCityJ = cities;
        for (j = 0; j < citiesNumber; j++) {
            if (tempCityI->road == NULL) {
                paths[i][j] = false;
            } else {
                road *tempCityRoad = tempCityI->road;
                while (tempCityRoad != NULL) {
                    //Saves in the array the distance if there is a direct connection between the two cities
                    if (tempCityRoad->to == tempCityJ) {
                        paths[i][j] = true;
                        break;
                    }
                    paths[i][j] = false;
                    tempCityRoad = tempCityRoad->next;
                }
            }
            tempCityJ = tempCityJ->next;
        }
        tempCityI = tempCityI->next;
    }

    for (k = 0; k < citiesNumber; ++k) {
        for (i = 0; i < citiesNumber; i++) {
            for (j = 0; j < citiesNumber; j++) {
                paths[i][j] = paths[i][j] || paths[i][k] && paths[k][j];
            }
        }
    }

    bool error = false;
    for (i = 0; i < citiesNumber; i++) {
        for (j = 0; j < citiesNumber; j++) {
            if (!paths[i][j]) {
                error = true;
                break;
            }
        }
    }

    if (error) {
        printf("Error en los datos hay al menos una ciudad aislada\n");
    } else {
        printf("El fichero ha sido validado correctamente\n");
    }


}


/**
 * Ask all the params to obtain the minimum distance between two cities and shows the result
 * @param cities list of cityes
 */
void getMinDistanceOption(city *cities) {
    char *buffer = (char *) malloc(sizeof(char) * 255);

    printf("Introduce el nombre de la ciudad origen\n> ");
    gets(buffer);
    fflush(stdin);
    city *from = getCityByName(cities, buffer);

    printf("Introduce el nombre de la ciudad destino\n> ");
    gets(buffer);
    fflush(stdin);
    city *to = getCityByName(cities, buffer);

    if (from == NULL || to == NULL) {
        printf("Error: Una de las ciudades no existe");
        free(buffer);
        return;
    }

    if (from == to) {
        printf("La distancia de una ciudad a ella misma... es 0");
        free(buffer);
        return;
    }


    int distance = getMinDistance(cities, from, to);
    if (distance != INT_MAX) {

        printf("La distancia mínima entre las dos ciudades es de %d\n", distance);
    } else {
        printf("Ocurrió un error al buscar el camino más corto");
    }


    free(buffer);

}

/**
 * Returns the min distance in km between two cities
 * @param cities
 * @param from
 * @param to
 * @return int distance
 */
int getMinDistance(city *cities, city *from, city *to) {
    int citiesNumber = countCities(cities);
    int paths[citiesNumber][citiesNumber];
    int midlePaths[citiesNumber][citiesNumber];
    int i, j, k;

    city *tempCityI = cities;
    city *tempCityJ;
    for (i = 0; i < citiesNumber; i++) {
        tempCityJ = cities;
        for (j = 0; j < citiesNumber; j++) {
            midlePaths[i][j] = -1;
            if (tempCityI->road == NULL) {
                paths[i][j] = INT_MAX;
            } else {
                road *tempCityRoad = tempCityI->road;
                while (tempCityRoad != NULL) {
                    //Saves in the array the distance if there is a direct connection between the two cities
                    if (tempCityRoad->to == tempCityJ) {
                        paths[i][j] = tempCityRoad->distance;
                        break;
                    }
                    paths[i][j] = INT_MAX;
                    tempCityRoad = tempCityRoad->next;
                }
            }

            tempCityJ = tempCityJ->next;
        }
        tempCityI = tempCityI->next;
    }

    for (k = 0; k < citiesNumber; ++k) {
        for (i = 0; i < citiesNumber; i++) {
            for (j = 0; j < citiesNumber; j++) {
                if (paths[i][k] != INT_MAX && paths[k][j] != INT_MAX && paths[i][k] + paths[k][j] < paths[i][j]) {
                    paths[i][j] = paths[i][k] + paths[k][j];
                    midlePaths[i][j] = k;
                }
            }
        }
    }

    tempCityI = cities;
    for (i = 0; i < citiesNumber; i++) {
        tempCityJ = cities;
        if (tempCityI == from) {
            for (j = 0; j < citiesNumber; j++) {
                if (tempCityJ == to) return paths[i][j];
                tempCityJ = tempCityJ->next;
            }
        }
        tempCityI = tempCityI->next;
    }

    return INT_MAX;
}

//TODO destroy everything