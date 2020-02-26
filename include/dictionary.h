/*******************************************************************************
This file was edited by Chris VanDoodewaard.
ID: 1053471 Email: cvandood@uoguelph.ca

Project: CIS 3250 A2
last edit: September, 30, 2019
*******************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>

#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

struct D_Node
{
    char *key;
    struct D_Node *next;
};
typedef struct D_Node D_Node;

char *copyStr(const char *inputString);

unsigned int hash(const char *inputString);

D_Node * lookup(D_Node **dictionary, int hashSize, const char *key);

D_Node * insert(D_Node **dictionary, int hashSize, const char *key);

void freeDictionary(D_Node **dictionary, int hashSize);

#endif
