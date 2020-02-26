#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdlib.h>

/*Node struct called user*/
typedef struct user
{
    char name[100];
    int max_score;
    int total_games;
    int total_score;
    struct user *next;

} User;

User* findUserWithName(User* head, char* name_to_find);

User* getUserAtIndex(User* head, int index);

int getIndexOfUserWithName(User* head, char* name_to_find);

int getLength(User* head);

User* getLastNode(User *head);

void printScoreboard(User *head);

void freeAll(User* head);

void addNode(User *head, char* name, int max_score);

int userIsInList(User* head, char* name_to_find);

void updateNodeWithName(User *head, char* name, int current_score);

#endif
