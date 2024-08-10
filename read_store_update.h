/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//this file contains function declarations related to
//read/store/update of database file

#ifndef READ_STORE_UPDATE_H
#define READ_STORE_UPDATE_H 

//function declaration to read one filename at a time and return it
char* get_filename(FILE* fp, char* filename);

//function declaration to read one valid words from given file pointer
char* get_word(FILE *fp, char *filename);

//function declaration to store word in list of struct word
void store_word(char* word, char* filename, struct word** head);

//function declaration to write word_list in DatabaseFile
void write_word_list(struct word* word_list);

//function declaration to read all words of all files and store it in a file
void create_database(char* filelist_filename);

//function definition to delete word_list (free dynamic memory)
//this function also erases the content of database file
void delete_database(void);

//function definition to update database
//first it will delete (free memory) of word_list
//this function will read all words of all files and update word_list
//then it will write updated word_list in database file
void update_database(char *filename);

#endif