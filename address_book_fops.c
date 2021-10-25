#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;
	printf("Works First");
	char firstCharacter;
	address_book->count = 0;
    address_book->list = malloc(sizeof(ContactInfo)*100);

	/* 
	 * Check for file existance
	 */
	address_book->fp = fopen(DEFAULT_FILE, "r");

	if (address_book->fp == NULL)
	{
		printf("Doesnt Works");
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
		address_book->count = 0;
	} else
	{
		fscanf(address_book->fp, "%d", &address_book->count);
		for(int counter = 0; counter < address_book->count; counter++)
		{
			fscanf(address_book->fp, "%d,%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,]",
			&address_book->list[counter].si_no,
			address_book->list[counter].phone_numbers[0],
			address_book->list[counter].phone_numbers[1], 
			address_book->list[counter].phone_numbers[2], 
			address_book->list[counter].phone_numbers[3],
			address_book->list[counter].phone_numbers[4],
			address_book->list[counter].email_addresses[0], 
			address_book->list[counter].email_addresses[1],
			address_book->list[counter].email_addresses[2],
			address_book->list[counter].email_addresses[3], 
			address_book->list[counter].email_addresses[4]);
		}
		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
