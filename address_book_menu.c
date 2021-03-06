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
			scanf("%c", &option);
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
  	int ind = 0;
  	int check = -1;
	char* target = "\0";

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
        		for(int id = 1; id < 5; id++)
        		{
          			printf(":      :                                ");
					if(strcmp(address_book->list[ind].phone_numbers[id],target) != 0)
          				fmtString(address_book->list[ind].phone_numbers[id]);
					else
						printf(" :                                ");
					
					if(strcmp(address_book->list[ind].email_addresses[id],target) != 0)
        		 	 	fmtString(address_book->list[ind].email_addresses[id]);
					else
						printf(" :                                ");
          			if(id != 4)
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
          			if(inp == 'n')
          			{ 
            			ind++;
            			check = 1;
         		 	}
          			else if(inp == 'p')
          			{ 
            			ind--;
            			check = 1;
          			}
          			else if(inp == 'q')
          			{
            			ind = 1;
						check = 1;
          			}
      
      	    		if((inp == 'n' && ind > address_book->count - 1) || (inp == 'p' && ind <= -1))
          			{
            			printf("\nInvalid input. Out of bounds.\nEnter Input: ");
            			check = 0;

            			if(ind > address_book->count - 1)
              			{
                			ind--;
              			}
            			else if(ind <= -1)
              			{
                			ind++;
              			}
          			}
        		}
      		}
			  
  return e_success;
}

void search_menu(void)
{
	menu_header("Search Contact By:\n");
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
				add_contacts(address_book);
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
				list_contacts(address_book, "List Contacts: ", (int *)1, "Press:\n[q] | Cancel\n[n] | Next Page\n[p] | Previous Page", e_list);
				break;
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
        return e_fail;
    }

	ContactInfo contact;
	ContactInfo *p = &contact;

	int numberOfPhones = 0; 
	int numberOfEmails = 0;

	int userInput;

	int count = address_book->count;

	int SHOWNAME = 0;     //flags to let menu know if it should display
	int SHOWPHONE = 0;	  //the contact names and numbers
	int SHOWEMAIL = 0;


    //printf("Start inserting data:\n");                   //Insert new data
    //printf("Please enter your name: ");
    do{
		
		printf("####### Add Contact #######\n\n");
		printf("0. Back: \n");
		printf("1. Name: ");
		if(SHOWNAME == 1){
			printf("%s \n",  *contact.name);
		}
		else{
			printf("\n");
		}

		printf("2. Phone: ");
		if(SHOWPHONE == 1){
			printf("\n");
			for(int i = 0; i < numberOfPhones; i++){
				printf("     %d: ", i);
				printf("%s \n",  contact.phone_numbers[i]);
			}
		}
		else{
			printf("\n");
		}

		printf("3. Email: ");
		if(SHOWEMAIL == 1){
			printf("\n");
			for(int i = 0; i < numberOfEmails; i++){
				printf("     %d: ", i);
				printf("%s \n",  contact.email_addresses[i]);
			}
		}
		else{
			printf("\n");
		}

		scanf("%d", &userInput);

		switch(userInput){
		case 0:
			break;
		case 1:
			SHOWNAME = 1;
			printf("Please enter contact name: ");
			scanf("%s", *contact.name);
			break;
		case 2:
			SHOWPHONE = 1;
			printf("Please enter amount of phone numbers: ");
			scanf("%d", &numberOfPhones);
			for(int i = 0; i < 5; i++){
				if(i < numberOfPhones){
					printf("Please enter the phone number: ");
    				scanf("%s", contact.phone_numbers[i]);	
				}
				else{
				strcpy(contact.phone_numbers[i],"\0");
				}
			}
			break;
		case 3: 
			SHOWEMAIL = 1;
		    printf("Please enter amount of email addresses: ");
			scanf("%d", &numberOfEmails);
			for(int i = 0; i < 5; i++){
				if(i < numberOfEmails){
					printf("Please enter the address:");
    				scanf("%s", contact.email_addresses[i]);	
				}
			else{
				strcpy(contact.email_addresses[i],"\0");
				}
			}
		}
		
	}while(userInput != 0);

    printf("Insert successfully!\n");

	contact.si_no = count;	
	address_book -> list[count] = contact; 
	address_book->count++;
 
    return e_success;
}

void print_search_header()
{
	printf("================================================================================================================\n");
	printf(": S.No : Name                             : Phone No                         : Email ID                        :\n");
	printf("================================================================================================================\n");
}

void print_search_separator()
{
	printf("================================================================================================================\n");
}

void exit_search()
{
	char input;
	while(1)
	{
		printf("Press: [q] | Cancel: ");
		scanf(" %c", &input);
		printf("\n");
		if (input == 'q' || input == 'Q')
		{
			break;
		}
	} 
}

void print_contact(ContactInfo *contact)
{
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

		//Print phone
		printf("%s", contact->phone_numbers[i]);
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
		printf(":\n");
	}
}

Status search(AddressBook *address_book, const char *targetName, int targetNo, int data_type)
{
	int result = e_no_match;
	menu_header("Search Result:\n");
	print_search_header();

	//Search for Name
	if (data_type == NAME){
		for (int i = 0; i < address_book->count; i++)
		{
			if (strcmp(address_book->list[i].name[0],targetName) == 0)
			{
				print_contact(&(address_book->list[i]));
				print_search_separator();
				result = e_success;
			}
		}
	}

	//Search for phone
	if (data_type == PHONE){
		for (int i = 0; i < address_book->count; i++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (strcmp(address_book->list[i].phone_numbers[k],targetName) == 0)
				{
					print_contact(&(address_book->list[i]));
					print_search_separator();
					k = 5;
					result = e_success;
				}
			}
		}
	}

	//Search for email
	if (data_type == EMAIL){
		for (int i = 0; i < address_book->count; i++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (strcmp(address_book->list[i].email_addresses[k],targetName) == 0)
				{
					print_contact(&(address_book->list[i]));
					print_search_separator();
					k = 5;
					result = e_success;
				}
			}
		}
	}


	//Search for serial
	if (data_type == SERIAL_NO)
	{
		for (int i = 0; i < address_book->count; i++)
		{
			if (address_book->list[i].si_no == targetNo)
			{
				print_contact(&(address_book->list[i]));
				print_search_separator();
				result = e_success;
			}
		}
	}

	//No matches found
	if (result == e_no_match)
	{
		printf("No results found.\n");
	}
	
	return result;
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	int option;
	int result = e_no_match;
	char target[NAME_LEN];
	int targetNum;

	if (address_book == NULL)            
    {
        printf("Address_book is null\n");
        return e_fail;
    }

	if (address_book->count == 0)
	{
		printf("There are no contacts in the address book.");
		return e_back;
	}

	do
	{
		search_menu();
		printf("Please select an option: ");
		scanf("%d",&option);
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
			printf("Enter the Name: ");
			scanf("%s", target);
			printf("\n");
			result = search(address_book, target, 0, NAME);
			exit_search();
			break;
		//Phone
		case e_third_opt:
			printf("Enter the Phone Number: ");
			scanf("%s", target);
			printf("\n");
			result = search(address_book, target, 0, PHONE);
			exit_search();
			break;
		//Email
		case e_fourth_opt:
			printf("Enter the Email: ");
			scanf("%s", target);
			printf("\n");
			result = search(address_book, target, 0, EMAIL);
			exit_search();
			break;
		//Serial No
		case e_fifth_opt:
			printf("Enter the Serial Number: ");
			scanf("%d", &targetNum);
			printf("\n");
			result = search(address_book, "\0", targetNum, SERIAL_NO);
			exit_search();
			break;
	}

	return result;
}

Status edit_contact(AddressBook *address_book)
{
	int option;
	AddressBook *endPtr = address_book + address_book->count;
	char name[NAME_LEN];
	char phone_number[NUMBER_LEN];
	char email[EMAIL_ID_LEN];
	do 
	{
		menu_header("Search Contact to Edit By:");
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
				scanf("%s", name);
				search_and_change(address_book, e_edit, NAME, name, -1);
				break;
			case e_third_opt:
				printf("Enter the Phone No: ");
				scanf("%s", phone_number);
				search_and_change(address_book, e_edit, PHONE, phone_number, -1);
				break;
			case e_fourth_opt:
				printf("Enter the email ID: ");
				scanf("%s", email);
				search_and_change(address_book, e_edit, EMAIL, email, -1);
				break;
			case e_fifth_opt:
				get_option(NUM, "Enter the Serial No: ");
				search_and_change(address_book, e_edit, SERIAL_NO, email, option);
				break;
			case e_exit:
				break;
		}
	} while(option != e_exit);
	
	return e_success;
	/* Add the functionality for delete contacts here */
}

Status delete_contact(AddressBook *address_book){
	int option;
	AddressBook *endPtr = address_book + address_book->count;
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
				scanf("%s", name);
				search_and_change(address_book, e_delete, NAME, name, -1);
				break;
			case e_third_opt:
				printf("Enter the Phone No: ");
				scanf("%s", phone_number);
				search_and_change(address_book, e_delete, PHONE, phone_number, -1);
				break;
			case e_fourth_opt:
				printf("Enter the email ID: ");
				scanf("%s", email);
				search_and_change(address_book, e_delete, EMAIL, email, -1);
				break;
			case e_fifth_opt:
				get_option(NUM, "Enter the Serial No: ");
				search_and_change(address_book, e_delete, SERIAL_NO, email, option);
				break;
			case e_exit:
				break;
		}
	} while(option != e_exit);
	
	return e_success;
	/* Add the functionality for delete contacts here */
}

Status edit_contact_display(AddressBook *address_book, int index)
{
    char* target = "\0";
    
    menu_header("Edit Contact");
    printf("\n\n");
    printf("0. Back\n");
    printf("1. Name       : %s\n", address_book->list[index].name[0]);
    for(int i = 0; i < 5; i++)
    {
        if(i == 0 && strcmp(address_book->list[index].phone_numbers[i],target) != 0)
            printf("2. Phone No 1 : %s\n",address_book->list[index].phone_numbers[i]);
        else if(i != 0 && (strcmp(address_book->list[index].phone_numbers[i],target) != 0))
            printf("            %i : %s\n", i + 1, address_book->list[index].phone_numbers[i]);
    }

    for(int j = 0; j < 5; j++)
    {
        if(j == 0 && strcmp(address_book->list[index].email_addresses[j],target) != 0)
            printf("3. Email ID 1 : %s\n",address_book->list[index].email_addresses[j]);
        else if(j != 0 && (strcmp(address_book->list[index].email_addresses[j],target) != 0))
            printf("            %i : %s\n", j + 1, address_book->list[index].email_addresses[j]);
        
    }
}

Status search_and_change(AddressBook *address_book, Modes mode, DeleteType type, char *target, int sno)
{
	printf("%d", mode);
	int total_contacts = address_book->count;
	int contacts[total_contacts];
	int option;
	int contacts_count = 0;
	switch(type)
	{
		case NAME:
			for(int counter = 0; counter < address_book->count; counter++)
			{
				if(strcmp(address_book->list[counter].name[0], target) == 0)
				{
					contacts[contacts_count] = address_book->list[counter].si_no;
					contacts_count += 1;
				}
			}
			search(address_book, target, 0, NAME);
			break;
		case PHONE:
			for(int counter = 0; counter < address_book->count; counter++)
			{
				for(int counter2 = 0; counter2 < PHONE_NUMBER_COUNT; counter2++)
				{
					if(strcmp(address_book->list[counter].name[counter2], target) == 0)
					{
						contacts[contacts_count] = address_book->list[counter].si_no;
						contacts_count += 1;
					}	
				}
			}
			search(address_book, target, 0, PHONE);
			break;
		case EMAIL:
			for(int counter = 0; counter < address_book->count; counter++)
			{
				for(int counter2 = 0; counter2 < EMAIL_ID_LEN; counter2++)
				{
					if(strcmp(address_book->list[counter].email_addresses[counter2], target) == 0)
					{
						contacts[contacts_count] = address_book->list[counter].si_no;
						contacts_count += 1;
					}	
				}
				
			}
			search(address_book, target, 0, EMAIL);
			break;
		case SERIAL_NO:
			for(int counter = 0; counter < address_book->count; counter++)
			{
				if(address_book->list[counter].si_no == sno)
				{
					contacts[0] = sno;
					contacts_count++;
				}
			}
			search(address_book, "\0", sno, SERIAL_NO);
			break;
		default:
			break;
	}

	if(contacts_count > 0 && mode == e_delete)
	{
		int isValid = 0;
		option = get_option(NUM, "\nEnter a Serial Number (S No.) to Delete: ");
		while(isValid == 0)
		{
			for(int count = 0; count < contacts_count; count++)
			{
				if(contacts[count] == option)
				{
					isValid = 1;
					printf("%d", isValid);
					break;
				} 
			}
			if(isValid == 0)
			{
				option = get_option(NUM, "S No. out of range of search. Enter a Serial Number (S No.) to Delete: ");
			} else
			{
				break;
			}
		}

		for(int count = 0; count < contacts_count; count++)
		{
			for(int counter = 0; counter < address_book->count; counter++)
			{

				if(option == address_book->list[counter].si_no && option == contacts[count])
				{
					ContactInfo temp = address_book->list[address_book->count - 1];
					address_book->list[address_book->count - 1] = address_book->list[counter];
					address_book->list[counter] = temp;
					address_book->count--;
					printf("Deletion successful");
					break;
				}
			}
		}
	}else if(contacts_count > 0 && mode == e_edit)
	{
		int isValid = 0;
		option = get_option(NUM, "\nEnter a Serial Number (S No.) to Edit: ");
		int chosenSINO = option;
		while(isValid == 0)
		{
			for(int count = 0; count < contacts_count; count++)
			{
				if(contacts[count] == option)
				{
					isValid = 1;
					break;
				} 
			}
			if(isValid == 0)
			{
				option = get_option(NUM, "S No. out of range of search. Enter a Serial Number (S No.) to Delete: ");
			} else
			{
				break;
			}
		}

		for(int count = 0; count < contacts_count; count++)
		{
			for(int counter = 0; counter < address_book->count; counter++)
			{

				if(chosenSINO == address_book->list[counter].si_no && option == contacts[count])
				{
					int elementIndex;
					int emailInt;
					int valid = 0;
					do
					{
						edit_contact_display(address_book, counter);
						option = get_option(NUM, "\nPlease select an option: ");

						switch(option)
						{
							case NAME:
								printf("Enter Name: ");
								scanf("%s", address_book->list[counter].name[0]);
								break;
							case PHONE:
								do
								{
									/* code */
									printf("Enter Phone Number index to be changed [Max 5]: ");
									elementIndex = get_option(NUM, "");
									if(elementIndex < 5 && elementIndex > 0)
									{
										printf("Enter Phone Number %d: ", elementIndex);
										scanf("%s", address_book->list[counter].phone_numbers[elementIndex - 1]);
										break;
									}
								} while (valid == 0);
								break;
							case EMAIL:
									printf("Enter Email index to be changed [Max 5]: ");
									elementIndex = get_option(NUM, "");
									if(elementIndex < 5 && elementIndex > 0)
									{
										printf("Enter Email %d: ", elementIndex);
										scanf("%s", address_book->list[counter].email_addresses[elementIndex - 1]);
										break;
									}
								break;
							default:
								break;
						}
					} while (option != e_exit);
					
					//Print the contact
					break;
				}
			}
		}
	}

	return e_success;

}