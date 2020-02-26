/*
*Project: Scoreboard.c
*Edited by Ian McKechnie
*Student number 1051662
*Email: imckechn@uoguelph.ca    
*date 24/09/2019
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "scoreboard.h"

 /*
 * Searches through the linked list and searches for a user with the name given.
 * Input: Linked list header, char pointer for the name being searched for.
 * Output: A struct pointer for the user with the name, null if it doesn't exist.
 */
User* findUserWithName(User* head, char* name_to_find) 
{
    if (head == NULL) 
    {
        return head;
    }
    
    User *current = head;
    
    while (current != NULL) 
    {
        if (strcmp(current->name, name_to_find) == 0) 
        {
            return current;
        }
        
        current = (current)->next;
    }
    
    return NULL;
}


/* 
* Frees every element of the linked list.
* Input: The linked list header,
* Output: Void.
*/
void freeAll(User* head)
{
    if (head->next == NULL) 
    {
        free(head);
    }
    else 
    {
        User *current = head->next;
        User *previous = head;
        
        /*Searches through the list until the end is found and free's each node*/
        while (current != NULL)     
        {
            free(previous);
            previous = current;
            current = (current)->next;
        }
    }
}


/*Searches through the linked list for the user.
*Intput:linked list head and the index number of the item being searched for.
*Ouput: the index numbered node, null if it doesn't exist. 
*/
User* getUserAtIndex(User* head, int index) 
{
    int count;
    if (head == NULL) 
    {
        return NULL;
    }
    
    User *current = head;
    count = 0;
    
    while (current != NULL) 
    {
        if (count == index + 1) 
        {
            return current;
        }
        
        current = (current)->next;
        count++;
    }
    return NULL;
}


/*Searches through the linked list for a node with a name equal to the name inputed.
*Inputs: head of the linked list, char pointer of the name that it's looking for.
*Output: the index of the node for which that name is stored at, -1 if nothing is found.
*/
int getIndexOfUserWithName(User* head, char* name_to_find) 
{
    if ((head == NULL) && (head->name != name_to_find)) 
    {
        return -1;
    }
    
    User *current = head;
    int count = 0;
    
    while (current != NULL) 
    {
        if (strcmp(current->name, name_to_find)) 
        {
            return count;
        }
        
        current = current->next;
        count++;
    }
    
    return -1;
}


/*
 * Finds whether or not a an existing user is already in the list. Of they are.
 * Intputs: the header for the linked list, the name being searched for.
 * Output: returns 1. If not, returns 0.
 */
int userIsInList(User* head, char* name_to_find) 
{
    User *current = head;
    
    while (current != NULL) 
    {
        if (strcmp(current->name, name_to_find) == 0) 
        {
            return 1;
        }
        
        current = current->next;
    }
    return 0;
}

/*
*Finds the length of the linked list.
*Input: head of the linked list.
*Output: the length of the linked list.
*/
int getLength(User* head) 
{
    if (head == NULL) {
        return 0;
    }
    
    User *current = head;
    int count = 0;
    
    while (current != NULL) 
    {
        count++;
        
        if (current->next == NULL) 
        {
            return count;
        }
        
        current = current->next;
    }
    
    return 0;
}


/*
 * Helper function. Finds the last node in the linked list and returns it.
 * Input: The linked list head.
 * Output: NULL if called with an empty head, although such a case is not used
 * in the main function add_node.
 */
User* getLastNode(User *head) 
{
    if (head == NULL) 
    {
        return head;
    }
    
    User *current = head;
    
    while (current != NULL) 
    {
        if (current->next == NULL) 
        {
            return current;
        }
        
        current = current->next;
    }
    
    return NULL;
}

/*
* Prints the score board by searching through the list and printing each player.
* Input: Linked list head.
* Output: void (prints to the screen tho.
*/
void printScoreboard(User *head) 
{
    fprintf(stdout, "\n");
    fprintf(stdout, "---- SCORE BOARD ---- \n");
        
    if (head -> next != NULL) 
    {
        User *current = head -> next;
        
        while (current != NULL) 
        {
            printf("\n");
            printf("Player name: %s \n", current->name);
            printf("High score: %d \n", current->max_score);
            printf("Games played: %d \n", current->total_games);
            printf("Total score: %d \n", current->total_score);
            printf("\n");
            printf("--------------------- \n");

            if (current->next == NULL) 
            {
                break;
            }
            
            current = current->next;
        }
    }
}

/*
* Adds a node with the given name to the linked list at the end with the score
* and name inputted.
* Input: The linked list head, char pointer of the name and the max_score for the user
* Output: Void.
*/
void addNode(User *head, char* name, int max_score)
{
    User *user_ptr;
    
    if (head != NULL) 
    {
         user_ptr = malloc(sizeof(struct user));
    }
    
    strcpy(user_ptr->name, name);
    user_ptr->max_score = max_score;
    user_ptr->total_games = 1;
    user_ptr->total_score = max_score;
    user_ptr->next = NULL;

    if (head == NULL) 
    {
        head = user_ptr;
    }
    else {
        getLastNode(head)->next = user_ptr;
    }
}


/*
* Updates a node's score using the name to find the node 
* Input: The linked list head, char pointer holding the name, the updates score
* Output: Void.
*/
void updateNodeWithName(User *head, char* name, int current_score) 
{
    if (userIsInList(head, name) == 1) 
    {
        User *user_ptr = findUserWithName(head, name);
        
        if (current_score > (user_ptr->max_score)) 
        {
            user_ptr->max_score = current_score;
        }
        
        user_ptr->total_games += 1;
        user_ptr->total_score += current_score;
    }
}
