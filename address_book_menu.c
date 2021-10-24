#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void search_menu(void)
{
	menuheader("Search Contact By:\n");
	printf("\n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

void print_search_header()
{
	printf("==============================================================================================================\n");
	printf(": S.No : Name                             : Phone No                         : Email ID                      :\n");
	printf("==============================================================================================================\n");
}

void print_search_separator()
{
	printf("==============================================================================================================\n");
}

void print_contact(ContactInfo *contact)
{
	bool_t si_no_printed = 0;
	
	for (int i = 0; i < 5; i++)
	{
		//Print serial no
		if (i == 0)
		{
			printf(": %d    : ", contact->si_no);
		}
		else
		{
			printf(":      : ");
		}

		//Print name
		if (i > 0)
		{
			printf("%s",contact->name[i]);
			for (int k = 0; k < 32-strlen(contact->name[i]); k++)
			{
				printf(" ");
			}
		}
		else
		{
			printf("                                ");
		}
		printf(" : ");

		//Print Phone
		printf("%s",contact->phone_numbers[i]);
		for (int k = 0; k < 32-strlen(contact->phone_numbers[i]); k++)
		{
			printf(" ");
		}
		printf(" : ");

		//Print Email
		printf("%s", contact->email_addresses[i]);
		for (int k = 0; k < 32-strlen(contact->email_addresses[i]); k++)
		{
			printf(" ");
		}
		printf(" :\n");
	}

}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	int result = e_no_match;
	char input;
	do
	{

	} while (input != "q");

	return result;
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	int option;
	int result = e_no_match;

	if (address_book->count == 0)
	{
		printf("There are no contacts in the address book.");
		return e_back;
	}

	do
	{
		search_menu();
		option = get_option(NUM,"Please select an option: ");
		printf("\n");
	} while (option < 0 && option > 4);

	switch(option)
	{
		//Back
		case e_first_opt:
			result = e_back;
			break;
		//Name
		case e_second_opt:
			char target[NAME_LEN];
			printf("Enter the Name: ");
			scanf("%s", &target);
			printf("\n");
			
			break;
		//Phone
		case e_third_opt:
			char target[NAME_LEN];
			printf("Enter the Phone Number: ");
			scanf("%s", &target);
			printf("\n");
			break;
		//Email
		case e_fourth_opt:
			char target[NAME_LEN];
			printf("Enter the Email: ");
			scanf("%s", &target);
			printf("\n");
			break;
		//Serial No
		case e_fifth_opt:
			int targetNum;
			printf("Enter the Serial Number: ");
			scanf("%d", &targetNum);
			printf("\n");
			break;
	}

	return result;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
