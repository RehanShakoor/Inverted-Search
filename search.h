/*
Name : Rehan Shakoor
Date : 09/08/2024

Description : 
DSA Inverted Search Project Submission
*/

//this file contains function declarations related to searching

#ifndef SEARCH_H
#define SEARCH_H

//function declaration to search for user input word in database
void search_database(char *filename);

//function declaration to search for a given word in word list
//if word matches then it returns pointer to word of word_list
struct word* search_word(char *word);

//function declaration to store matched word node in new list of struct word
//we have to copy every member of struct word to new list, because we would
//be updating word_count here and that should not affect the original word_list
void store_matched_word(struct word* matched_node, struct word** head);

//function declaration to check whether given filename node is common among matched word list or not
int is_common_filename(struct filename* given_filename_node, struct word* matched_word_list);

//function declaration to free the dynamic memory used by matched word list
void free_word_list(struct word** matched_word_list);

//function declaration to free the dynamic memory used by common filename list
void free_filename_list(struct filename** common_filenames_list);

#endif