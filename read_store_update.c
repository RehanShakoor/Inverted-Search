/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//this file contains function definitions related to
//read/store/update of database file

//include in-built header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//include user-defined header files
#include "global_variables.h"
#include "common_functions.h"
#include "read_store_update.h"
#include "search.h"

//function definition to read one filename at a time and return it
char* get_filename(FILE* fp, char* filename)
{
	//if fp is NULL
	if(fp == NULL)
	{
		//then print below error msg and return NULL
		printf("Error   : Can't open file \"%s\"\n",filename);
		return NULL;
	}
	//if file opens successfully
	else
	{
		//below variable will be used to temporarily store filename
		char temp_filename[MAX_FILENAME_SIZE];

		//below variables will be used to store length and file char
		//static is used to retain value between function calls
		//this is used mainly to check empty file case
		static int filename_length = 0;
		char file_char = 0;

		//read single filename at a time
		//if first char is EOF or LF
		file_char = fgetc(fp);
		if(file_char == EOF || file_char == '\n')
		{
			//if length of filename is zero
			if(filename_length == 0)
			{
				//then print below info
				printf("Info    : \"%s\" file is empty\n", filename);
				printf("Info    : Clossing file \"%s\"\n", filename);

				//close the file and return NULL from function
				fclose(fp);
				return NULL;
			}
			//if length of filename is not zero
			else
			{
				//this means EOF is reached and all filenames are read
				//print success msg and then return
				printf("\nSuccess : Reading of filenames from \"%s\" completed\n", filename);
				printf("Info    : Clossing file \"%s\"\n", filename);

				//close the file and return NULL from function
				fclose(fp);
				return NULL;
			}
		}
		//if file is not empty
		else
		{
			//reset length to zero
			filename_length = 0;

			//store first char in temp array
			temp_filename[filename_length] = file_char;
			filename_length++;

			//read file untill newline is not encountered
			//each filename is stored in a newline
			while((file_char = fgetc(fp)) != '\n')
			{
				//store filename in temp array
				temp_filename[filename_length] = file_char;
				filename_length++;
			}

			//terminate char array with NULL character
			temp_filename[filename_length] = '\0';
			filename_length++;

			//allocate dynamic memory to store filename
			char* return_filename = malloc(filename_length);

			//copy temp array to dynamic memory
			return strcpy(return_filename, temp_filename);
		}
	}
}

//function definition to read one valid words from given file pointer
char* get_word(FILE *fp, char *filename)
{
	//if fp is NULL
	if(fp == NULL)
	{
		//then print below error msg and return NULL
		printf("Error   : Can't open file \"%s\"\n",filename);
		return NULL;
	}
	//if file opens successfully
	else
	{
		//below variable will be used to temporarily store a word
		char word[MAX_WORD_SIZE];

		//below variables will be used to store length and file char
		//static is used to retain value between function calls
		//this is used mainly to check empty file case
		static int word_length = 0;
		char file_char = 0;

		//read single word from given file
		//if first char is EOF or LF and word length is zero 
		file_char = fgetc(fp);
		if((file_char == EOF || file_char == '\n') && word_length == 0)
		{
			//then print below info
			printf("Info    : \"%s\" file is empty\n",filename);
			printf("Info    : Clossing file \"%s\"\n", filename);

			//close the file and return from function
			fclose(fp);
			return NULL;
		}
		//if file is not empty
		else
		{
			//reset word length to zero
			word_length = 0;

			//if first read character is a alphabet
			if(isalpha(file_char))
			{
				//then store that alphabet in word
				//all characters are stored in lowercase
				word[word_length] = tolower(file_char);
				word_length++;
			}

			//read file untill an alphabet is not encountered
			while(1)
			{
				//read char from file
				file_char = fgetc(fp);

				//if read char is a alphabet
				if(isalpha(file_char))
				{
					//then get out of loop
					break;
				}
                //if read char is not a alphabet and some word is read
                else if(word_length != 0)
                {
                    //terminate word with NULL character and break
			        word[word_length] = '\0';
			        word_length++;

                    //if word is a valid one
			        if(check_valid_word(word))
			        {
				        //allocate dynamic memory for word
				        char* word_return = malloc(word_length);
				
				        //copy the word in dynamic memory and return it
				        return strcpy(word_return, word);
			        }
			        //else return INVALID from function
			        else
			        {
				        return "INVALID";
			        }
                }
				//if EOF is reached
				else if(file_char == EOF)
				{
					//this mean all words are read now
					//print success msg and then return
					printf("Success : Reading all words of file \"%s\" completed\n",filename);
					printf("Success : Storing all words of file \"%s\" in linked list completed\n",filename);
					printf("Info    : Clossing file \"%s\"\n", filename);

					//close the file and return from function
					fclose(fp);
					return NULL;
				}    
			}

			//read file untill non-alphabet character is encountered
			do
			{
				//then store that alphabet in word
				//all characters are stored in lowercase
				word[word_length] = tolower(file_char);
				word_length++;
			}
			while(isalpha(file_char = fgetc(fp)));

			//terminate word with NULL character
			word[word_length] = '\0';
			word_length++;
			
			//if word is a valid one
			if(check_valid_word(word))
			{
				//allocate dynamic memory for word
				char* word_return = malloc(word_length);
				
				//copy the word in dynamic memory and return it
				return strcpy(word_return, word);
			}
			//else return INVALID from function
			else
			{
				return "INVALID";
			}
		}
	}
}

//function definition to store word in list of struct word
void store_word(char* word, char* filename, struct word** head)
{
	//if word list is empty
	if(*head == NULL)
	{
		//create a new node in heap memory
		*head = malloc(sizeof(struct word));
		//store word in new node
		(*head)->word = word;

		//allocate dynamic memory for struct filename
		(*head)->filename_list =  malloc(sizeof(struct filename));
		//store filename in new node
		(*head)->filename_list->filename = filename;
		//update count of word in filename
		(*head)->filename_list->word_count = 1;
		//terminate next link of struct filename
		(*head)->filename_list->next = NULL;

		//terminate next link of node
		(*head)->next = NULL;

		//return from function
		return;
	}
	//if word list is not empty
	else
	{
		//compare given word with head node word
		int str_cmp = strcmp(word, (*head)->word);

		//if given word matches with head node word
		if(str_cmp == 0)
		{
			//store head node of filename_list in a temp pointer
			struct filename* temp_ptr = (*head)->filename_list;

			//iterate over filename_list
			while(temp_ptr)
			{
				//if filename matches (this is case of same word of a file)
				if(strcmp(filename, temp_ptr->filename) == 0)
				{
					//then increment the count of that word in that file
					temp_ptr->word_count++;
					//then return from function
					return;
				}
				else
				{
					//if current node is last node
					if(temp_ptr->next == NULL)
					{
						//this means no matching filename is found
						//add new filename at the last of this list
						//allocate dynamic memory for new filename node
						temp_ptr->next = malloc(sizeof(struct filename));

						//store filename in new node
						temp_ptr->next->filename = filename;
						//update word count for the word
						temp_ptr->next->word_count = 1;
						//terminate link of new node
						temp_ptr->next->next = NULL;

						//then return from function
						return;
					}
					else
					{
						//move to next node
						temp_ptr = temp_ptr->next;
					}
				}
			}		
		}
		//if given word is smaller (lexographically) than head node word
		else if(str_cmp < 0)
		{
			//create a new head in heap memory
			struct word *new_head = malloc(sizeof(struct word));

			//store word in new node
			new_head->word = word;

			//allocate dynamic memory for struct filename
			new_head->filename_list = malloc(sizeof(struct filename));
			//store filename in new node
			new_head->filename_list->filename = filename;
			//update count of word in filename
			new_head->filename_list->word_count = 1;
			//terminate next link of struct filename
			new_head->filename_list->next = NULL;

			//connect new head with remaining word_list
			new_head->next = *head;	
			//update head with new head
			*head = new_head;

			//then return from function
			return;
		}
		//if given word is greater (lexographically) than head node word
		else
		{
			//create a temp pointer to store head node
			struct word* temp_ptr1 = *head;

			//iterate over word_list 
			while(temp_ptr1->next)
			{
				//compare given word with temp next node word
				int str_cmp = strcmp(word, temp_ptr1->next->word);

				//if given word matches with temp next node word
				if(str_cmp == 0)
				{
					//store head node of filename_list in a temp pointer
					struct filename* temp_ptr2 = temp_ptr1->next->filename_list;

					//iterate over filename_list
					while(temp_ptr2)
					{
						//if filename matches (this is case of same word of a file)
						if(strcmp(filename, temp_ptr2->filename) == 0)
						{
							//then increment the count of that word in that file
							temp_ptr2->word_count++;
							//then return from function
							return;
						}
						else
						{
							//if current node is last node
							if(temp_ptr2->next == NULL)
							{
								//this means no matching filename is found
								//add new filename at the last of this list
								//allocate dynamic memory for new filename node
								temp_ptr2->next = malloc(sizeof(struct filename));

								//store filename in new node
								temp_ptr2->next->filename = filename;
								//update word count for the word
								temp_ptr2->next->word_count = 1;
								//terminate link of new node
								temp_ptr2->next->next = NULL;

								//then return from function
								return;
							}
							else
							{
								//move to next node
								temp_ptr2 = temp_ptr2->next;
							}
						}
					}
				}
				//if given word is smaller (lexographically) than temp next node word
				else if(str_cmp < 0)
				{
					//then create a new node after temp
					//create a new node in heap memory
					struct word *new_node = malloc(sizeof(struct word));

					//store word in new node
					new_node->word = word;

					//allocate dynamic memory for struct filename
					new_node->filename_list =  malloc(sizeof(struct filename));
					//store filename in new node
					new_node->filename_list->filename = filename;
					//update count of word in filename
					new_node->filename_list->word_count = 1;
					//terminate next link of struct filename
					new_node->filename_list->next = NULL;

					//connect new node next with temp_ptr1->next
					new_node->next = temp_ptr1->next;
					//connect temp to new node
					temp_ptr1->next = new_node;

					//then return from function
					return;
				}
				//if given word is greater (lexographically) than temp next node word
				else
				{
					//move to next node
					temp_ptr1 = temp_ptr1->next;
				}
			}
			
			//if execution reaches this point, that means temp_ptr1 is last node
			//this means no matching word is found
			//add new word at the last of this list
			//allocate dynamic memory for new word node
			temp_ptr1->next = malloc(sizeof(struct word));
						
			//store word in new node
			temp_ptr1->next->word = word;

			//allocate dynamic memory for struct filename
			temp_ptr1->next->filename_list = malloc(sizeof(struct filename));
			//store filename in new node
			temp_ptr1->next->filename_list->filename = filename;
			//update count of word in filename
			temp_ptr1->next->filename_list->word_count = 1;
			//terminate next link of struct filename
			temp_ptr1->next->filename_list->next = NULL;

			//terminate next link of node
			temp_ptr1->next->next = NULL;

			//then return from function
			return;
		}
	}
}

//function definition to write word_list in DatabaseFile
void write_word_list(struct word* word_list)
{
	//if word list is empty
	if(word_list == NULL)
	{
		//print below info and return
		printf("Info    : Word list is empty, can't create database file\n\n");
		return;
	}
	else
	{
		//database filename
		char* database_filename = "DatabaseFile";

		//print below info
		printf("Info    : Opening/Creating database file \"%s\" to write word list\n",database_filename);

		//open database file in write mode
		FILE* fp = fopen(database_filename, "w");

		//if file pointer is NULL
		if(fp == NULL)
		{
			//then print below error msg and return NULL
			printf("Error   : Can't open/create database file \"%s\"\n\n",database_filename);
			return;	
		}
		else
		{
			//write header info of database file
			fprintf(fp, "%-*s %-*s %-*s ...\n",MAX_WORD_SIZE, "WORD", MAX_FILENAME_SIZE, "FILENAME", WORD_COUNT_SIZE, "WORD-COUNT");

			//store word_list in database file
			//iterate over word_list
			while(word_list)
			{
				//write word to database file
				fprintf(fp, "%-*s ",MAX_WORD_SIZE, word_list->word);

				//store head node of filename_list in temp pointer
				struct filename* temp_ptr = word_list->filename_list;

				//iterate over filename_list
				while(temp_ptr)
				{
					//write filename and word count
					fprintf(fp, "%-*s ",MAX_FILENAME_SIZE, temp_ptr->filename);
					fprintf(fp, "%-*d ",WORD_COUNT_SIZE, temp_ptr->word_count);

					//move to next node
					temp_ptr = temp_ptr->next;
				}

				//move to next node and print newline
				word_list = word_list->next;
				fprintf(fp, "\n");
			}

			//print below success msg
			printf("Success : Writing word list to databse file \"%s\" completed\n",database_filename);
			//print below info msg and return
			printf("Info    : Closing database file \"%s\"\n\n",database_filename);
            fclose(fp);

			return;
		}
	}
}

//function definition to read all words of all files and store it in a file
void create_database(char* filelist_filename)
{
	//read one file name at time
	char *filename = NULL;
	FILE* fp1 = fopen(filelist_filename, "r");

	//print below info
	printf("Info    : Creating database\n");

    //create database only if word_list is empty
    if(word_list == NULL)
    {
	    printf("Info    : Opening file \"%s\" to read all filenames\n",filelist_filename);
	    //total_file_count will store number of files store in FileList
	    int total_file_count = 1;

	    //iteratively call function get_filename() to get filenames
	    while(filename = get_filename(fp1, filelist_filename))
	    {
	    	//print below info
	    	printf("\nInfo    : Opening file%d \"%s\" to read all its words\n",total_file_count++, filename);

	    	//open file "filename"
	    	FILE* fp2 = fopen(filename, "r");

	    	//read one valid word at a time from given file pointer
	    	char* word = NULL;
	    	while(word = get_word(fp2, filename))
		    {
                //store only valid words
                if(word != "INVALID")
	    		    //store read word in word_list
	    		    store_word(word, filename, &word_list);
		    }
	    }

    	printf("\n");
    	//write word_list in DatabaseFile
	    write_word_list(word_list);
    }
    //if word_list is not empty, then we can only update databse
    else
    {
        //print below msg
	    printf("Info    : word list is not empty\n"); 
        printf("Error   : Can't create a new database\n");
        printf("Usage   : Use update-database option to update existing database\n\n");
    }
}

//function definition to delete word_list (free dynamic memory)
//this function also erases the content of database file 
void delete_database(void)
{
	//print below info
	printf("Info    : Deleting word linked list (free dynamic memory)\n");

	//if given list is empty
	if(word_list == NULL)
	{
		//then print below info
		printf("Info    : word linked list is already empty\n");
	}
	else
	{
		//iterate over word_list and delete all its last node
		while(1)
		{
			//store head node of word_list in temp pointer
			struct word* temp_ptr1 = word_list;

			//if word_list only have one node
			if(temp_ptr1->next == NULL)
			{
				//free the dynamic memory used by word member of struct word
				free(temp_ptr1->word);

				//iterate over filename_list and delete all its last node
				while(1)
				{
					//store head node of filename_list in temp pointer
					struct filename* temp_ptr2 = temp_ptr1->filename_list;

					//if filename_list only have one node
					if(temp_ptr2->next == NULL)
					{
                        //if filename doesn't contain NULL (it is not deleted yet)
                        if(*temp_ptr2->filename)
                        {
                            //each filename read from Filelist is stored in dynamic memory, this same 
                            //dyamic memory location is used in each word of word_list

                            //temp_ptr2->filename points to the "filename" stored in heap memory
                            //we have to terminate the location at which "filename" is stored
                            *(temp_ptr2->filename) = '\0';

                            //now we have to realloc that dynamic memory to 1 bytes, just to store
                            //a single NULL character, nothing more
                            temp_ptr2->filename = realloc(temp_ptr2->filename, 1);

						    //we will not free the dynamic memory used by filename member of struct filename
                            //because this NULL character will be used to check, if string is empty or not

                            //terminate filename member of struct filename with NULL
                            temp_ptr2->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2);

						    //now all memmory used by filemane_list is free
						    //terminate filename_list member of struct word
						    temp_ptr1->filename_list = NULL;

                            //break from inner while(1) loop
					    	break;	
                        }
                        else
                        {
                            //terminate filename member of struct filename with NULL
                            temp_ptr2->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2);

						    //now all memmory used by filemane_list is free
						    //terminate filename_list member of struct word
						    temp_ptr1->filename_list = NULL;

                            //break from inner while(1) loop
					    	break;
                        }
					}
					//if filename_list have two or more nodes
					else
					{
						//goto second last node of filename_list
						while(temp_ptr2->next->next)
							temp_ptr2 = temp_ptr2->next;

						//now temp_ptr2 will point to second last node
                        //if filename doesn't contain NULL (it is not deleted yet)
                        if(*temp_ptr2->next->filename)
                        {
                            //each filename read from Filelist is stored in dynamic memory, this same 
                            //dyamic memory location is used in each word of word_list

                            //temp_ptr2->filename points to the "filename" stored in heap memory
                            //we have to terminate the location at which "filename" is stored
                            *(temp_ptr2->next->filename) = '\0';

                            //now we have to realloc that dynamic memory to 1 bytes, just to store
                            //a single NULL character, nothing more
                            temp_ptr2->next->filename = realloc(temp_ptr2->next->filename, 1);

						    //we will not free the dynamic memory used by filename member of struct filename
                            //because this NULL character will be used to check, if string is empty or not

                            //terminate filename member of struct filename with NULL
                            temp_ptr2->next->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2->next);

						    //terminate link of second last node
						    temp_ptr2->next = NULL;		
                        }
                        else
                        {
                            //terminate filename member of struct filename with NULL
                            temp_ptr2->next->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2->next);

						    //terminate link of second last node
						    temp_ptr2->next = NULL;
                        }
					}
				}

				//free dynamic memory used by last word_list node
				free(temp_ptr1);

				//now all memmory used by word_list is free
				//terminate word_list with NULL
				word_list = NULL;

                //print below success msg
            	printf("Success : Freeing dynamic memory used by word_list completed\n");


				//break from while(1) loop
				break;
			}
			//if word list have two or more nodes
			else
			{
				//goto second last node of word_list
				while(temp_ptr1->next->next)
					temp_ptr1 = temp_ptr1->next;

				//now temp_ptr1 will point to second last node
				//free the dynamic memory used by word member of last node
				free(temp_ptr1->next->word);

				//iterate over filename_list and delete all its last node
				while(1)
				{
					//store head node of filename_list in temp pointer
					struct filename* temp_ptr2 = temp_ptr1->next->filename_list;

					//if filename_list only have one node
					if(temp_ptr2->next == NULL)
					{
                        //if filename doesn't contain NULL (it is not deleted yet)
                        if(*temp_ptr2->filename)
                        {
                            //each filename read from Filelist is stored in dynamic memory, this same 
                            //dyamic memory location is used in each word of word_list

                            //temp_ptr2->filename points to the "filename" stored in heap memory
                            //we have to terminate the location at which "filename" is stored
                            *(temp_ptr2->filename) = '\0';

                            //now we have to realloc that dynamic memory to 1 bytes, just to store
                            //a single NULL character, nothing more
                            temp_ptr2->filename = realloc(temp_ptr2->filename, 1);

						    //we will not free the dynamic memory used by filename member of struct filename
                            //because this NULL character will be used to check, if string is empty or not

                            //terminate filename member of struct filename with NULL
                            temp_ptr2->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2);

						    //now all memmory used by filemane_list is free
						    //terminate filename_list member of struct word
						    temp_ptr1->next->filename_list = NULL;	

                            //break from inner while(1) loop
						    break;
                        }
                        else
                        {
                            //terminate filename member of struct filename with NULL
                            temp_ptr2->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2);

						    //now all memmory used by filemane_list is free
						    //terminate filename_list member of struct word
						    temp_ptr1->next->filename_list = NULL;	

                            //break from inner while(1) loop
						    break;
                        }
					}
					//if filename_list have two or more nodes
					else
					{
						//goto second last node of filename_list
						while(temp_ptr2->next->next)
							temp_ptr2 = temp_ptr2->next;

                        //now temp_ptr2 will point to second last node
                        //if filename doesn't contain NULL (it is not deleted yet)
                        if(*temp_ptr2->next->filename)
                        {
                            //each filename read from Filelist is stored in dynamic memory, this same 
                            //dyamic memory location is used in each word of word_list

                            //temp_ptr2->filename points to the "filename" stored in heap memory
                            //we have to terminate the location at which "filename" is stored
                            *(temp_ptr2->next->filename) = '\0';

                            //now we have to realloc that dynamic memory to 1 bytes, just to store
                            //a single NULL character, nothing more
                            temp_ptr2->next->filename = realloc(temp_ptr2->next->filename, 1);

						    //we will not free the dynamic memory used by filename member of struct filename
                            //because this NULL character will be used to check, if string is empty or not

                            //terminate filename member of struct filename with NULL
                            temp_ptr2->next->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2->next);

						    //terminate link of second last node
						    temp_ptr2->next = NULL;		
                        }
                        else
                        {
                            //terminate filename member of struct filename with NULL
                            temp_ptr2->next->filename = NULL;

						    //word_count member doesnt use dynamic memory
						    //therefore no need to free its memory

						    //free dynamic memory used by filename node
						    free(temp_ptr2->next);

						    //terminate link of second last node
						    temp_ptr2->next = NULL;	
                        }
					}
				}

				//free dynamic memory used by last word_list node
				free(temp_ptr1->next);

				//terminate link of second last node of word_list
				temp_ptr1->next = NULL;
			}
		}
	}

	//open database file in "w" mode to delete all its content
	FILE* fp = fopen("DatabaseFile", "w");
	if(fp == NULL)
	{
		//then print below info
		printf("Info    : Database file \"Database\" is already deleted\n\n");
	}
	else
	{
		//print below success msg and cose file
		printf("Success : All content of database file \"Database\" is deleted\n\n");
        fclose(fp);
	}
}

//function definition to update database
//first it will delete (free memory) of word_list
//this function will read all words of all files and update word_list
//then it will write updated word_list in database file
void update_database(char *filename)
{
	//print below info
	printf("Info    : Updating database\n");

	//if word_list is empty
	if(word_list == NULL)
	{
        //print below info
	    printf("Info    : Current database is empty\n");
        printf("Usage   : First create a database then update it\n\n");
	}
	else
	{
        //now we must delete already existing word linked list
		//and update it with new content
		delete_database();

        //create new updated database
        //read all words of all files and store it in a linked list
        //and write that linked list to database file
        create_database(filename);	
	}
}