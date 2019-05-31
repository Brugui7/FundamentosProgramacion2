/**
 * @file
 * @brief Functions definition for contact
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#include "../model/structs.h"

#ifndef FUNDAMENTOS2_CONTACT_H
#define FUNDAMENTOS2_CONTACT_H


contact *addContactOption(contact *contacts);

contact *addContact(contact *contacts, contact *contact);

void findContactOption(contact *contacts);

contact *getContactByName(contact *contacts, char *name);

contact *getContactByNumber(contact *contacts, char *number);

void destroyBook(contact *contacts);

#endif //FUNDAMENTOS2_CONTACT_H
