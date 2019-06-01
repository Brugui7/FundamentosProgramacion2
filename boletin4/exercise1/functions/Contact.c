/**
 * @file
 * @brief Independent contact functions
 * @author: Alejandro Brugarolas
 * @since: 2019-03
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Contact.h"
/**
 * Asks the user for the contacts details
 * @param contacts
 * @return contacts
 */
contact *addContactOption(contact *contacts) {
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t bufferLength;
    contact *newContact = (contact *) malloc(sizeof(contact));

    printf("Introduzca el nombre del nuevo contacto\n> ");
    gets(buffer);
    bufferLength = strlen(buffer);
    newContact->name = (char *) malloc(sizeof(char) * bufferLength);
    strncpy(newContact->name, buffer, bufferLength + 1);
    fflush(stdin);

    printf("Introduzca el número del nuevo contacto\n> ");
    gets(buffer);
    bufferLength = strlen(buffer);
    newContact->number = (char *) malloc(sizeof(char *) * bufferLength);
    strncpy(newContact->number, buffer, bufferLength + 1);
    fflush(stdin);

    if (strlen(newContact->number) == 0 || strlen(newContact->name) == 0) {
        printf("Error: Uno o más campos son inválidos\n");
    } else {
        contacts = addContact(contacts, newContact);
        printf("Contacto creado correctamente\n");
    }

    free(buffer);
    return contacts;

}

/**
 * Adds a new contact to the book, keeping them ordered by their names by doing recursion
 * @param contacts
 * @param contact
 */
contact *addContact(contact *contacts, contact *newContact) {
    if (contacts == NULL) {
        contacts = newContact;
        contacts->right = NULL;
        contacts->left = NULL;
        return contacts;
    }

    int comparison = strcmp(contacts->name, newContact->name);

    if (comparison > 0) {
        contacts->left = addContact(contacts->left, newContact);
    } else if (comparison < 0) {
        contacts->right = addContact(contacts->right, newContact);
    }

    return contacts;
}

/**
 * Ask the user for a number/name to find a contact
 * @param contacts
 */
void findContactOption(contact *contacts) {
    char *buffer = (char *) malloc(sizeof(char) * 255);
    int option = 0;

    while (option != 1 && option != 2) {
        printf("Seleccione el modo de búsqueda\n1. Por nombre\n2. Por número\n> ");
        scanf("%d", &option);
        fflush(stdin);
    }
    contact *contactFound = NULL;

    if (option == 1) {
        printf("Introduzca el nombre del contacto a buscar\n> ");
        gets(buffer);
        fflush(stdin);
        contactFound = getContactByName(contacts, buffer);
    } else {
        printf("Introduzca el número del contacto a buscar\n> ");
        gets(buffer);
        fflush(stdin);
        contactFound = getContactByNumber(contacts, buffer);
    }

    if (contactFound == NULL) {
        printf("No se encontró ningún contacto con los parámetros de búsqueda introducidos");
    } else if (option == 1) {
        printf("El número de %s es el %s", contactFound->name, contactFound->number);
    } else {
        printf("El nombre del contacto es %s", contactFound->name);
    }

    free(buffer);

}

/**
 * Returns a contact given a name
 * @param contacts the book
 * @param name of the contact
 * @return the contact or null if not found
 */
contact *getContactByName(contact *contacts, char *name) {
    if (contacts == NULL) return NULL;

    int comparison = strcmp(contacts->name, name);

    if (comparison == 0) {
        return contacts;
    } else if (comparison < 0) {
        return getContactByName(contacts->right, name); //name > contacts->name
    } else {
        return getContactByName(contacts->left, name); //name < contacts->name
    }

}

/**
 * Returns a contact given a number
 * @param contacts the book
 * @param number of the contact
 * @return the contact or null if not found
 */
contact *getContactByNumber(contact *contacts, char *number) {
    if (contacts == NULL) return NULL;

    if (strcmp(contacts->number, number) == 0) return contacts;


    contact *contact1 = getContactByNumber(contacts->right, number);
    contact *contact2 = getContactByNumber(contacts->left, number);


    if (contact1 != NULL) return contact1;
    if (contact2 != NULL) return contact2;
    return NULL;
}

/**
 * Deletes all the contacts
 * @param contacts
 */
void destroyBook(contact *contacts) {

    if (contacts == NULL) return;
    destroyBook(contacts->left);
    free(contacts->name);
    free(contacts->number);
    free(contacts);

}