/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//This header file contains structs and global variables

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

//macros to define max. characters in filename and word
#define MAX_FILENAME_SIZE  15
#define MAX_WORD_SIZE      15
#define WORD_COUNT_SIZE    15
#define SEARCH_STRING_SIZE 101

//below struct will store file name
//word_count is used to store count of a particular word present in that file
typedef struct filename
{
	char* filename;
	struct filename* next;
	int word_count;
} file_name;

//below struct will store word index 
//it will store word, list of filenames which contains that word and link to next node
typedef struct word
{
	char* word;
	struct filename* filename_list;
	struct word* next;
} word;

//create a pointer to a node of struct word
//this will store all words, its filename and its word_count
extern struct word* word_list;

#endif