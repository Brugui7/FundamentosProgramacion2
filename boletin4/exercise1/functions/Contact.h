/**
 * @file
 * @brief Functions definition for contact
 * @author: Alejandro Brugarolas
 * @since: 2019-05
*/

#include "../model/structs.h"

#ifndef FUNDAMENTOS2_CONTACT_H
#define FUNDAMENTOS2_CONTACT_H

const char A_ACUTE;
const char E_ACUTE;
const char I_ACUTE;
const char O_ACUTE;
const char U_ACUTE;
const char OPEN_QUESTION_MARK;


contact *addContactOption(contact *contacts);

contact *addContact(contact *contacts, contact *contact);

contact *getContactByName(contact *contacts, char *name);

contact *getContactByNumber(contact *contacts, char *number);

#endif //FUNDAMENTOS2_CONTACT_H
