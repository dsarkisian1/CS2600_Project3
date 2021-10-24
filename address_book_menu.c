#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"

#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	printf("%s", msg);
	int option;
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 
	switch(type)
	{
		case CHAR:
			scanf("%s", &option);
			break;
		case NUM:
			scanf("%d", &option);
			break;
		case NONE:
			break;
		default:
			break;	
	}
	return option;

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

	system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
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
	   if (address_book == NULL)            //Sentence blank
    {
        printf("address_book is null\n");
        return;
    }

    int count = address_book->count;
    ++address_book->count;
    printf("Start inserting data:\n");                   //Insert new data
    printf("Please enter your name:");
    scanf("%s", address_book->list[count].name);
    printf("Please enter the phone number:");
    scanf("%s", address_book->list[count].phone_numbers);
    printf("Please enter the address:");
    scanf("%s", address_book->list[count].email_addresses);
    printf("Insert successfully!\n");
    return;
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

Status exit_search()
{
	char input;
	do
	{
		printf("Press: [q] | Cancel: ");
		scanf("%c", &input);
		printf("\n");
	} while (input != "q");
	return e_back;
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
		if (i == 0)
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

Status search(const char *str, AddressBook *address_book, int field)
{
	int result = e_no_match;
	menu_header("Search Result:\n");

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
			// result = search();
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
	int option;
	const AddressBook *endPtr = address_book + address_book->count;
	char name[NAME_LEN];
	char phone_number[NUMBER_LEN];
	char email[EMAIL_ID_LEN];

	do 
	{
		menu_header("Search Contact to Delete By:");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone No\n");
		printf("3. Email ID\n");
		printf("4. Serial No\n");
		printf("\n");
		printf("Please select an option: ");
		option = get_option(NUM, "");
		switch (option)
		{
			case e_second_opt:
				printf("Enter the Name: ");
				scanf("%s", &name);
				search_and_delete(address_book, NAME, name, endPtr);
				break;
			case e_third_opt:
				printf("Enter the Phone No: ");
				scanf("%s", &phone_number);
				break;
			case e_fourth_opt:
				printf("Enter the email ID: ");
				scanf("%s", &email);
				break;
			case e_fifth_opt:
				get_option(NUM, "Enter the Serial No: ");
				break;
			case e_exit:
				break;
		}
	} while(option != e_exit);
	

	/* Add the functionality for delete contacts here */
}

Status search_and_delete(AddressBook *address_book, DeleteType type, char *target, AddressBook *endPtr)
{
	int contacts[address_book->count];
	int contacts_count = 0;
	switch(type)
	{
		case NAME:
			for(AddressBook *startPoint = address_book; startPoint < endPtr; startPoint++)
			{
				if(strcmp(*address_book->list->name, target) == 0)
				{
					contacts[contacts_count] = address_book->list->si_no;
					contacts_count += 1;
				}
			}
			break;
		case PHONE:
			for(AddressBook *startPoint = address_book; startPoint < endPtr; startPoint++)
			{
				if(strcmp(*address_book->list->name, target) == 0)
				{
					contacts[contacts_count] = address_book->list->si_no;
					contacts_count += 1;
				}
			}
			break;
		case EMAIL:
			break;
		default:
			break;
	}

	if(contacts_count > 0)
	{
		for(int count = 0; count < contacts_count; count++)
		{
			for(AddressBook *startPoint = address_book; startPoint < endPtr; startPoint++)
			{
				if(startPoint->list->si_no == contacts[count])
				{
					menu_header("Search Result: ");
					printf("============================================================================================================/n");
					printf(": S. No : Name                            : Phone No                        : Email ID                     :/n");
					printf("============================================================================================================/n");
				}
			}
		}
	}
}