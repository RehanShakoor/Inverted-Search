/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//This file contains definition of functions related to searching

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

//function definition to search for user input word in database
void search_database(char *filename)
{   
    //print below info
	printf("Info    : Search database\n");

	//if word_list is empty
	if(word_list == NULL)
	{
        //print below info
	    printf("Info    : word linked list is empty\n");
        printf("Usage   : First create a database then search in it\n\n");
	}
    else
    {
        //below pointer will store list of matched word nodes
        struct word* matched_word_list = NULL;

        //read search string from user
        char search_string[SEARCH_STRING_SIZE];
        //clear input buffer
        getchar();
        printf("Enter search string : ");
        scanf("%100[^\n]", search_string);

        //iterate over search string to get string token
        int index1 = 0;
        while(1)
        {
            //if NULL character is encountered
            if(search_string[index1] == '\0')
            {
                printf("Success : Reading input search string completed\n\n");
                break;
            }
            //if alphabet is encountered
            else if(isalpha(search_string[index1]))
            {
                //iterate over search string and store string token
                //characters are converted to lower case before storing
                int index2 = 0;
                char word[MAX_WORD_SIZE];
                while(isalpha(search_string[index1]))
                {
                    word[index2] = tolower(search_string[index1]);
                    index1++;
                    index2++;
                }

                //terminate word with NULL character
                word[index2] = '\0';

                //now we get a word which only contains alphabets
                //check validity of word
                if(check_valid_word(word))
                {
                    //print below info
	                printf("\nInfo    : Word read \"%s\" is a valid word \n",word);

                    //now search valid word
                    //if given word is found in the word_list
                    struct word* temp_ptr = NULL;
                    if(temp_ptr = search_word(word))
                    {
                        //print below info
	                    printf("Info    : Word \"%s\" is found in the word list\n",word);

                        //store matched word node in matched_word_list
                        store_matched_word(temp_ptr, &matched_word_list);

                        //print below info
	                    printf("Info    : Word \"%s\" is stored in the matched word list\n",word);
                    }
                    else
                    {
                        //print below info
	                    printf("Info    : Word \"%s\" is not found in the word list\n",word);
                    }
                }
                else
                {
                    //print below info
	                printf("\nInfo    : Word read \"%s\" is not valid word \n",word);
                }
            }
            else
            {
                index1++;
            }
        }

        //if matched_word_list is empty
        if(matched_word_list == NULL)
        {
            //print below info
	        printf("Info    : No matched word is found\n\n");
        }
        else
        {
            //print below info
	        printf("Info    : Searching for common filenames among matched word list\n");

            //below list will contain all the filename which is common among matched word list
            struct filename* common_filenames_list = NULL;

            //iterate over filenamelist of  matched_word_list 
            //only checking of head node of matched word list is required
            struct filename* temp_ptr1 = matched_word_list->filename_list;

            while(temp_ptr1)
            {
                //if current filename node is common to all nodes
                if(is_common_filename(temp_ptr1, matched_word_list))
                {
                    //then store that node to the last of common_filename_list
                    //if common filename list is empty
                    if(common_filenames_list == NULL)
                    {
                        //allocate dynamic memory to store new filename node
                        common_filenames_list = malloc(sizeof(struct filename));
                        //copy filename pointer 
                        common_filenames_list->filename = temp_ptr1->filename;
                        //copy word_count pointer 
                        common_filenames_list->word_count = temp_ptr1->word_count;
                        //terminate the link
                        common_filenames_list->next = NULL;
                    }
                    else
                    {
                        //iterate over common filename list to get the last node
                        struct filename* temp_ptr2 = common_filenames_list;
                        while(temp_ptr2->next)
                            temp_ptr2 = temp_ptr2->next;
                        
                        //now temp_ptr2 will point to the last node
                        //allocate dynamic memory to store filename node
                        temp_ptr2->next = malloc(sizeof(struct filename));
                        //copy filename pointer
                        temp_ptr2->next->filename = temp_ptr1->filename;
                        //copy word_count pointer
                        temp_ptr2->next->word_count = temp_ptr1->word_count;
                        //terminate the link
                        temp_ptr2->next->next = NULL;
                    }

                }
                //move to next node
                temp_ptr1 = temp_ptr1->next;
            }

            //if common filename list is empty
            if(common_filenames_list == NULL)
            {
                //print below info
	            printf("Info    : No common filename is found among matched word/s\n");

                //free the dynamic memory used for searching
                free_word_list(&matched_word_list);
                printf("Info    : All dynamic memory used for searching are freed\n\n");
            }
            else
            {
                printf("Success : Common filename/s are found among matched word/s\n\n");
                printf("Info    : Below is the list of files, which contains the entered search string\n");
                printf("Info    : Weight of file (word count) decreases from left to right\n");
                
                //print common filename list
                temp_ptr1 = common_filenames_list;
                printf("Files   : ");
                while(temp_ptr1)
                {
                    printf("%s\t",temp_ptr1->filename);
                    temp_ptr1 = temp_ptr1->next;
                }
                printf("\n");

                //free the dynamic memory used for searching
                free_word_list(&matched_word_list);
                free_filename_list(&common_filenames_list);
                printf("Info    : All dynamic memory used for searching are freed\n\n");
            }
        }
    }
}

//function definition to free the dynamic memory used by matched word list
void free_word_list(struct word** matched_word_list)
{
    //matched word list is not empty (this check is already done)

    //we will only free the dynamic memory used by node
    //we will not free the dynamic memory used by node members
    //because same pointers are used to store word_list

    //iterate over matched_word_list and delete last nodes
    while(1)
    {
        //if list have only one node
        struct word* temp_ptr1 = *matched_word_list;
        if(temp_ptr1->next == NULL)
        {
            //free the dynamic memory used by head node
            free(temp_ptr1);

            //terminate head node
            *matched_word_list = NULL;

            //then return from function
            return;
        }
        else
        {
            //get second last node of list
            while(temp_ptr1->next->next)
                temp_ptr1 = temp_ptr1->next;

            //now temp_ptr1 will point to second last node of list
            //free the dynamic memory used by last node
            free(temp_ptr1->next);

            //terminate the link of second last node
            temp_ptr1->next = NULL;
        }
    }
}


//function definition to free the dynamic memory used by common filename list
void free_filename_list(struct filename** common_filenames_list)
{
    //common filename list is not empty (this check is already done)

    //we will only free the dynamic memory used by node
    //we will not free the dynamic memory used by node members
    //because same pointers are used to store word_list

    //iterate over common_filenames_list and delete last nodes
    while(1)
    {
        //if list have only one node
        struct filename* temp_ptr1 = *common_filenames_list;
        if(temp_ptr1->next == NULL)
        {
            //free the dynamic memory used by head node
            free(temp_ptr1);

            //terminate head node
            *common_filenames_list = NULL;

            //then return from function
            return;
        }
        else
        {
            //get second last node of list
            while(temp_ptr1->next->next)
                temp_ptr1 = temp_ptr1->next;

            //now temp_ptr1 will point to second last node of list
            //free the dynamic memory used by last node
            free(temp_ptr1->next);

            //terminate the link of second last node
            temp_ptr1->next = NULL;
        }
    }
}

//function definition to check whether given filename node is common among matched word list or not
int is_common_filename(struct filename* given_filename_node, struct word* matched_word_list)
{
    //if matched_word_list only have one node
    if(matched_word_list->next == NULL)
    {
        //then return one for all the filename of current word node
        return 1;
    }
    else
    {
        //store next matched-word node in a temp pointer
        struct word* temp_ptr1 = matched_word_list->next;

        //flag used to check filename matches or not
        int filename_matches = 0;

        //iterate over next matched word node
        while(temp_ptr1)
        {
            //store filename list in a temp pointer
            struct filename* temp_ptr2 = temp_ptr1->filename_list;

            //iterate over temp_ptr2
            while(temp_ptr2)
            {
                //if filename matches then break
                if(strcmp(given_filename_node->filename, temp_ptr2->filename) == 0)
                {
                    //if given filename word_count is less than current filename word_count
                    if(given_filename_node->word_count < temp_ptr2->word_count)
                        //then update it with current filename word_count
                        given_filename_node->word_count = temp_ptr2->word_count;

                    //update filename_matches to one
                    filename_matches = 1;
                    break;
                }
                //else move to next node
                else
                {
                    //update filename_matches to zero
                    filename_matches = 0;
                    temp_ptr2 = temp_ptr2->next;
                }
            }

            //if filename doesn't match then break
            if(filename_matches == 0)
            {
                break;
            }
            else
            {
                //move to next node
                temp_ptr1 = temp_ptr1->next;
            }
        }

        //return filename_matches
        return filename_matches;
    }
}

//function definition to search for a given word in word list
//if word matches then it returns pointer to word of word_list
struct word* search_word(char *word)
{
    //word_list empty check is not required, as it is done earlier

    //iterate over word list
    struct word *temp_ptr = word_list;
    while(temp_ptr)
    {
        //if given word matched with word_list word
        if(strcmp(word, temp_ptr->word) == 0)
        {
            //then return pointer of current word node
            return temp_ptr;
        }
        else
        {
            temp_ptr = temp_ptr->next;
        }
    }

    //if execution reaches this points, that means given word 
    //is not present in the word_list, then return NULL
    return NULL;
}

//function definition to store matched word node in new list of struct word
//we have to copy every member of struct word to new list, because we would
//be updating word_count here and that should not affect the original word_list
void store_matched_word(struct word* matched_node, struct word** head)
{
	//if matched word list is empty
	if(*head == NULL)
	{
		//create a new node in heap memory
		*head = malloc(sizeof(struct word));
		//copy matched node word in new node
		(*head)->word = matched_node->word;

        //allocate dynamic memory for new filename node
		(*head)->filename_list = malloc(sizeof(struct filename));

        //store head node of filename_list of matched node in a temp pointer1
		struct filename* temp_ptr1 = matched_node->filename_list;
        //store head node of filename_list of new node in a temp pointer2
        struct filename* temp_ptr2 = (*head)->filename_list;

        //copy first filename node of matched node to new node
        temp_ptr2->filename = temp_ptr1->filename;
		//copy word_count of matched node to new node
		temp_ptr2->word_count = temp_ptr1->word_count;

		//move to next filename node of matched ndoe
        temp_ptr1 = temp_ptr1->next;

		//iterate over filename_list of matched nodes
		while(temp_ptr1)
		{
			//allocate dynamic memory for new filename node
			temp_ptr2->next = malloc(sizeof(struct filename));

            //copy filename of matched node to new node
            temp_ptr2->next->filename = temp_ptr1->filename;

			//copy word_count of matched node to new node
			temp_ptr2->next->word_count = temp_ptr1->word_count;

			//move to next node
            temp_ptr1 = temp_ptr1->next;
			temp_ptr2 = temp_ptr2->next;
		}

        //terminate link of filename_list of new node
        temp_ptr2->next = NULL;

		//terminate next link of new head node
		(*head)->next = NULL;

		//return from function
		return;
	}
	//if matched word list is not empty
	else
	{
        //store head node of matched-word list in a temp pointer1
		struct word* temp_ptr1 = *head;

        //iterate over matched-node list
        while(temp_ptr1)
        {
		    //compare matched node word with temp_ptr1 word
		    int str_cmp = strcmp(matched_node->word, temp_ptr1->word);

		    //if given word matches with head node word
		    if(str_cmp == 0)
		    {
                //store head node of filename_list of temp_ptr1 in  temp pointer2
                struct filename* temp_ptr2 = temp_ptr1->filename_list;

                //iterate over filename_list
	    	    while(temp_ptr2)
		        {
                    //then increment the word count of matched word 
				    int word_count = temp_ptr2->word_count;
                    temp_ptr2->word_count += word_count;

			        //move to next node
			        temp_ptr2 = temp_ptr2->next;
		        }

                //then return from function
                return;
            }
            else
            {
                //if we are at last node of matched_word_list, that means no word
                //is matched and we have to add this node at the last 
                if(temp_ptr1->next == NULL)
                {
                    //create a last node in heap memory
		            temp_ptr1->next = malloc(sizeof(struct word));
		            //copy matched node word in last node
		            temp_ptr1->next->word = matched_node->word;

                    //allocate dynamic memory for new filename node
		            temp_ptr1->next->filename_list = malloc(sizeof(struct filename));

                    //store head node of filename_list of matched node in a tp1
		            struct filename* tp1 = matched_node->filename_list;
                    //store head node of filename_list of last node in a tp2
                    struct filename* tp2 = temp_ptr1->next->filename_list;

                    //copy first filename node of matched node to last node
                    tp2->filename = tp1->filename;
		            //copy word_count of matched node to last node
		            tp2->word_count = tp1->word_count;

		            //move to next filename node of matched ndoe
                    tp1 = tp1->next;

		            //iterate over filename_list of matched nodes
	            	while(tp1)
		            {
			            //allocate dynamic memory for new filename node
			            tp2->next = malloc(sizeof(struct filename));

                        //copy filename of matched node to last node
                        tp2->next->filename = tp1->filename;

			            //copy word_count of matched node to last node
			            tp2->next->word_count = tp1->word_count;

			            //move to next node
                        tp1 = tp1->next;
			            tp2 = tp2->next;
		            }

                    //terminate link of last node of filename list
                    tp2->next = NULL;

                    //terminate link of last node of matched-word list
                    temp_ptr1->next->next = NULL;

                    //then return from function
                    return;
                }
                else
                {
                    //move to next node
			        temp_ptr1 = temp_ptr1->next;
                }
            }
        }
    }
}