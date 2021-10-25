#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abk_fileops.h"
#include "abk_log.h"
#include "abk_menus.h"
#include "abk.h"

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

void fmtSiNo(int num)
{
	printf(": %i",num);
	int spcFill = 4;
	int temp = num;
	while(temp != 0)
	{	
		spcFill--;
		temp /= 10;
	}
	for(int i = 0; i < spcFill; i++)
		printf(" ");
	
}
void fmtString(char* str)
{
	printf(" : %s", str);

	int spcFill = 31 - strlen(str);
	for(int i = 0; i < spcFill; i++)
		printf(" ");
	

}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 
	char inp = '\0';
  	int ind = 1;
  	int check = -1;
  	switch(mode)
  	{
    	case e_list:
      		while(inp != 'q')
      		{
	        	check = 0;
    		    inp = '\0';
    		    menu_header(title);
    		    printf("\n==============================================================================================================");
    		    printf("\n: S.No : Name                            : Phone No                        : Email ID                        :");
    		    printf("\n==============================================================================================================\n");
    		    fmtSiNo(address_book->list[ind].si_no);
    		    fmtString(address_book->list[ind].name[0]);
    		    fmtString(address_book->list[ind].phone_numbers[0]);
    		    fmtString(address_book->list[ind].email_addresses[0]);
 
        		printf(" :\n");
		        for(int i = 1; i < 5; i++)
		        {
		     		printf(":      :                                ");
          			fmtString(address_book->list[ind].phone_numbers[i]);
          			fmtString(address_book->list[ind].email_addresses[i]);
          				if(i != 4)
            				printf(" :\n");
          				else
            				printf(" :");
        		}
    		    printf("\n==============================================================================================================\n");
    		    printf("%s", msg);
    		    printf("\nEnter Input: ");
 
 	 	        while(check != 1)
        		{
          			scanf("%c", &inp);
          			if(inp == 'n' && ind <= address_book->count)
          			{ 
            			ind++;
            			check = 1;
         		 	}
          			else if(inp == 'p' && ind > 0)
          			{ 
            			ind--;
            			check = 1;
          			}
          			else if(inp == 'q')
          			{
            			ind = 1;
						check = 1;
          			}
      
      	    		if((inp == 'n' && ind > address_book->count) || (inp == 'p' && ind <= 0))
          			{
            			printf("\nInvalid input. Out of bounds.\nEnter Input: ");
            			check = 0;

            			if(ind > address_book->count)
              			{
                			ind--;
              			}
            			else if(ind < 1)
              			{
                			ind++;
              			}
          			}
        		}
      		}
			break;
			 
  } 
  return e_success;
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
				list_contacts(address_book, "List Contacts: ", 1, "Press:\n[q] | Cancel\n[n] | Next Page\n[p] | Previous Page", e_list);
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

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
