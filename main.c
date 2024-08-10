/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//include in-built header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//create a pointer to a node of struct word
//this will store all words, its filename and its word_count
struct word* word_list = NULL;

//include user-defined header files
#include "global_variables.h"
#include "common_functions.h"
#include "read_store_update.h"
#include "search.h"

//main function, executuion starts from this function
int main(int argc, char **argv)
{
	//if two command line arguments are passed
	if(argc == 2)
	{
		//read user choice for main menu
		char user_choice = 0;
		while((user_choice = print_main_menu()))
		{
			//call functions according to user choice
			switch(user_choice)
			{
				case '1':
					//below function read all words of all files and store it in a file
					create_database(argv[1]);
					break;

				case '2':
					//call function to update database
					update_database(argv[1]);
					break;

				case '3':
					//call function to delete database
					delete_database();
					break;
					
				case '4':
					//call function to print content of databasefile
					display_database();
					break;

				case '5':
					//call function to create a backup file of database file
					create_backup();
					break;

				case '6':
					//call function to search user input string in database
					search_database(argv[1]);
					break;

				case '7':
					//print help menu
					print_help_menu();
				break;

				case '8':
					//print below info and exit from program
					printf("Info    : Exiting from program\n");
					//exit(0) is used to terminate the whole program and free and dynamic memory
					exit(0);

				default:
					//print below error msg and continue
					printf("Error   : Please enter a valid choice\n");
					break;
			}

			//clear input buffer
			getchar();
			//ask user to continue or not
			while(1)
			{
				printf("Do you want to continue (y/n) : ");
				scanf("%c", &user_choice);
				getchar();
				if(user_choice == 'n')
				{
					//print below info and exit from program
					printf("Info    : Exiting from program\n");
					//exit(0) is used to terminate the whole program and free and dynamic memory
					exit(0);
				}
				else if(user_choice == 'y')
				{
					break;
				}
				else
				{
					//print below error msg and continue
					printf("Error   : Please enter a valid choice\n");
				}
			}
		}
	}
	else
	{
		//then print below error msg and exit
		printf("Error   : No command line argument is passed\n");
		printf("Usage   : <executable file> Filelist\n");
		printf("\"Filelist\" contains names of all files, whose words to be read\n");
	}

	//exit(0) is used to terminate the whole program and free and dynamic memory
	exit(0);
}