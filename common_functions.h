/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//This header file contains declaration of common functions
//which is used in both read/store and searching part of project

#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

//function declaration to print main menu
char print_main_menu(void);

//function declaration to print help menu
void print_help_menu(void);

//function declaration to display content of DatabaseFile
void display_database(void);

//function declaration to print word_list
void print_word_list(struct word* word_list);

//function declaration to check validity of word
int check_valid_word(char* word);

//function declaration to create a backup file of database file
void create_backup(void);

#endif