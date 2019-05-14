/**
 * @file
 * @brief Functions definition for component
 * @author: Alejandro Brugarolas
 * @since: 2019-03
*/

#ifndef FUNDAMENTOS2_COMPONENT_H
#define FUNDAMENTOS2_COMPONENT_H


#include <stdbool.h>


void showComponent(struct component component);

struct component *createCompoentList();

struct component *addComponent(struct component *componentList, struct component *component);

struct component *getComponentById(struct component *component, char *id);

void deleteComponent(struct component *componentList, struct component *component);

struct component *createComponentOption(struct component *componentList);

void deleteComponentOption(struct component *componentList);

#endif //FUNDAMENTOS2_COMPONENT_H
