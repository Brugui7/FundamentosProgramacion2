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

const char A_ACUTE = 160;
const char E_ACUTE = 130;
const char I_ACUTE = 161;
const char O_ACUTE = 162;
const char U_ACUTE = 163;
const char OPEN_QUESTION_MARK = 168;

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

    printf("Introduzca el n%cmero del nuevo contacto\n> ", U_ACUTE);
    gets(buffer);
    bufferLength = strlen(buffer);
    newContact->number = (char *) malloc(sizeof(char *) * bufferLength);
    strncpy(newContact->number, buffer, bufferLength + 1);

    if (strlen(newContact->number) == 0 || strlen(newContact->name) == 0) {
        printf("Error: Uno o m%cs campos son inv%clidos\n", A_ACUTE, A_ACUTE);
    } else {
        contacts = addContact(contacts, newContact);
        printf("Contacto creado correctamente\n");
    }

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

    int comparation = strcmp(contacts->name, newContact->name);

    if (comparation > 0) {
        contacts->left = addContact(contacts->left, newContact);
    } else if (comparation < 0) {
        contacts->right = addContact(contacts->right, newContact);
    }

    return contacts;
}

/**
 * Returns a contact given a name
 * @param contacts the book
 * @param name of the contact
 * @return the contact or null if not found
 */
contact *getContactByName(contact *contacts, char *name) {
//TODO
    return NULL;
}

/**
 * Returns a contact given a number
 * @param contacts the book
 * @param number of the contact
 * @return the contact or null if not found
 */
contact *getContactByNumber(contact *contacts, char *number) {
//TODO
    return NULL;
}