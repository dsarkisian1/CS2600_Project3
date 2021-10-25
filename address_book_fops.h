#ifndef ABK_FILEOPS_H
#define ABK_FILEOPS_H

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
    address_book->list = malloc(sizeof(ContactInfo)*100);
}

Status save_file(AddressBook *address_book);


#endif
