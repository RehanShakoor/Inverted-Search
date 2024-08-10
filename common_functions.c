/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//This file contains definition of common functions
//which is used in both read/store and searching part of project

//include in-built header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//global variables to check validity of word
char *preposition[10] = {"of", "in", "to", "for", "with", "on", "at", "by", "about", "from"};
char *conjunction[10] = {"and", "but", "or", "so", "yet", "for", "nor", "because", "although", "if"};
char *article[3]      = {"a", "an", "the"};
char *pronoun[12]     = {"i", "you", "he", "she", "it", "we", "they", "me", "him", "her", "this", "that"};
char *others[3]       = {"is", "am", "are"};

//include user-defined header files
#include "global_variables.h"
#include "common_functions.h"
#include "read_store_update.h"
#include "search.h"

//function definition to print main menu
char print_main_menu(void)
{
	//print main menu options
	printf("\nSelect your choice among following options : \n");
	printf("1. Create  DATABASE\n");
	printf("2. Update  DATABASE\n");
    printf("3. Delete  DATABASE\n");
	printf("4. Display DATABASE\n");
	printf("5. Save    DATABASE\n");
	printf("6. Search  DATABASE\n");
	printf("7. Help Menu\n");
	printf("8. Exit\n");

	//read user choice and return it
	printf("Enter your choice : ");
	char user_choice = 0;
	scanf("%c",&user_choice);
	printf("\n");
	return user_choice;
}

//function definition to print help menu
void print_help_menu(void)
{
	//a file named as help, contains the help instruction
	char* help_filename = "help";

	//open help file
	FILE* fp = fopen(help_filename, "r");

	//if fp is NULL
	if(fp == NULL)
	{
		//then print below error msg and return
		printf("Error   : Can't open help file \"%s\"\n",help_filename);
		printf("Info    : Please create a \"help\" file and write help instructions in it\n");
		return;
	}
	else
	{
		//read character from help file and print it
		char ch = 0;
		while((ch = fgetc(fp)) != EOF)
		{
			putchar(ch);
		}
	}
	printf("\n");
}

//function definition to display content of DatabaseFile
void display_database(void)
{
	//database filename
	char* database_filename = "DatabaseFile";

	//print below info
	printf("Info    : Opening database file \"%s\" to display its content\n",database_filename);

	//open database file in read mode
	FILE* fp = fopen(database_filename, "r");

	//if file pointer is NULL
	if(fp == NULL)
	{
		//then print below error msg and return NULL
		printf("Error   : Database file \"%s\" doesn't exists\n",database_filename);
		printf("Usage   : First create a database then display it\n\n");
		return;	
	}
	else
	{
		//read first char of database file
		char ch = fgetc(fp);
		//if EOF or LF is first char
		if(ch == EOF || ch == '\n')
		{
			//print below info and usgae
			printf("Info    : Database file \"%s\" is empty\n",database_filename);
			printf("Usage   : First create a database then display it\n");
		}
		else
		{
			//read each char of database file and print it
			printf("\n");
			//print first read char
			putchar(ch);
			while((ch = fgetc(fp)) != EOF)
			{
				putchar(ch);
			}
			printf("\n");
		}
		
		//print below info msg and return
		printf("Info    : Closing database file \"%s\"\n\n",database_filename);
		return;
	}
}

//function definition to print word_list
void print_word_list(struct word* word_list)
{
	//if given list is empty
	if(word_list == NULL)
	{
		//then print below info
		printf("Info    : word_list is empty\n");
	}
	else
	{
		//iterate over word_list
		while(word_list)
		{
			//print word and
			printf("word = %s\n",word_list->word);

			//store head node of filename_list in temp pointer
			struct filename* temp_ptr = word_list->filename_list;

			//iterate over filename_list
			while(temp_ptr)
			{
				//print filename and word count
				printf("Filename = %s\n",temp_ptr->filename);
				printf("word count = %d\n",temp_ptr->word_count);

				//move to next node
				temp_ptr = temp_ptr->next;
			}
			
			word_list = word_list->next;
			printf("\n");
		}
	}
}

//function definition to check validity of word
int check_valid_word(char* word)
{
	//check for preposition
	for(int i = 0; i <= (sizeof(preposition) / sizeof(*preposition) - 1); i++)
		//if word matches then return 0
		if(strcmp(word, preposition[i]) == 0)
			return 0;

	//check for conjunction
	for(int i = 0; i <= (sizeof(conjunction) / sizeof(*conjunction) - 1); i++)
		//if word matches then return 0
		if(strcmp(word, conjunction[i]) == 0)
			return 0;

	//check for articles
	for(int i = 0; i <= (sizeof(article) / sizeof(*article) - 1); i++)
		//if word matches then return 0
		if(strcmp(word, article[i]) == 0)
			return 0;

	//check for pronouns
	for(int i = 0; i <= (sizeof(pronoun) / sizeof(*pronoun) - 1); i++)
		//if word matches then return 0
		if(strcmp(word, pronoun[i]) == 0)
			return 0;

    //check for others
	for(int i = 0; i <= (sizeof(others) / sizeof(*others) - 1); i++)
		//if word matches then return 0
		if(strcmp(word, others[i]) == 0)
			return 0;

	//if execution reaches this point, that means no word matches
	return 1;
}

//function definition to create a backup file of database file
void create_backup(void)
{
	//database filename
	char* database_filename = "DatabaseFile";

	//print below info
	printf("Info    : Creating backup file of database file\n");
	printf("Info    : Opening database file \"%s\" to create its backup\n",database_filename);

	//open database file in read mode
	FILE* fp1 = fopen(database_filename, "r");

	//if file pointer is NULL
	if(fp1 == NULL)
	{
		//then print below error msg and return
		printf("Error   : Database file \"%s\" doesn't exists\n",database_filename);
		printf("Usage   : First create a database then create its backup\n\n");
		return;	
	}
	else
	{
		//read backup filename from user
		char backup_filename[20];
		printf("Enter the name of backup file : ");
		scanf("%s",backup_filename);

		//open backup file in write mode
		FILE *fp2 = fopen(backup_filename, "w");

		//if file pointer is NULL
		if(fp2 == NULL)
		{
			//then print below error msg
			printf("Error   : Can't open/create \"%s\" file\n", backup_filename);
		}
		else
		{
			//read first char of database file
			char ch = fgetc(fp1);
			//if EOF or LF is first char
			if(ch == EOF || ch == '\n')
			{
				//print below info and usgae
				printf("Info    : Database file \"%s\" is empty\n",database_filename);
				printf("Usage   : First create a database then display it\n");
			}
			else
			{
				//read each char of database file and write it to backup file
				//write first read char
				fputc(ch, fp2);
				while((ch = fgetc(fp1)) != EOF)
				{
					fputc(ch, fp2);
				}

				//print below info and usgae
				printf("Success : Backup file \"%s\" is created\n",backup_filename);
			}
		}
		
		//print below info msg and return
		printf("Info    : Closing database file \"%s\"\n\n",database_filename);
		return;
	}
}