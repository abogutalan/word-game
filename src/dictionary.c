/*******************************************************************************
This file was edited by Chris VanDoodewaard.
ID: 1053471 Email: cvandood@uoguelph.ca

Project: CIS 3250 A2
last edit: September, 30, 2019
*******************************************************************************/

#include <string.h>
#include "dictionary.h"
#include <stdio.h>

/*******************************************************************************
Purpose: accepts a string and uses this as the starting value
for creating a hashValue used to start the creation of a dictionary array.

Parameters:
    -const char *inputString:

Returns:
    -hasVal:
*******************************************************************************/
unsigned int hash(const char *inputString)
{
    unsigned int hashVal;

    for (hashVal = 0; *inputString != '\0'; inputString++)
    {
            /*added some brackets around this equation that may have changed
            the intended functionality*/
            hashVal = (*inputString) + (31 * hashVal);
    }
    return hashVal;
}

/*******************************************************************************
Purpose: searches through a dictionary and checks if the word entered is a
valid english word.

Parameters:
    -D_Node **dicitonary:
    -int hashSize:
    -const char *key:

Returns:
    -D_Node *np: if succesfully iterates through the loop to the desired node
    -or NULL if desired node not found
*******************************************************************************/
D_Node *lookup (D_Node **dictionary, int hashSize, const char *key)
{
    D_Node *np;
    unsigned int hashVal;

    hashVal = hash(key);

    for (np = dictionary [hashVal % hashSize]; np !=NULL; np = np->next)
    {
        if (strcmp (key, np->key) == 0)
        {
            return np;
        }
    }
    /*if the desired node cannot be found, this function returns NULL*/
    return NULL;
}

/*************************************************************************
Purpose: if the guessed word is a valid english word, then it is allowable
to be inserted into the list of guessed words.

Parameters:
    -D_Node **dicitonary:
    -int hashSize:
    -const char *key:

Returns:
    -D_Node *np: if succesfully iterates through the loop to the desired node
    -or NULL if desired node not found
****************************************************************************/
D_Node *insert (D_Node **dictionary, int hashSize,  const char *key)
{
    unsigned int hashVal;
    D_Node *np;

    np = lookup(dictionary, hashSize, key);

    if (np == NULL )
    {
        np = (D_Node *) malloc(sizeof (*np));

        if ((np == NULL) || ((np->key = copyStr(key)) == NULL))
        {
            return NULL;
        }

        hashVal = hash(key) % hashSize;
        np->next = dictionary[hashVal];
        dictionary[hashVal] = np;
    }
    return np;
}

/*************************************************************************
Purpose: loops through the list of words in the dictionary or guessed words and
frees each word. 

Parameters:
    -D_Node **dictionary:
    -int hashSize:

Returns: n/a
****************************************************************************/
void freeDictionary (D_Node **dictionary, int hashSize)
{
    int i;
    for (i = 0; i < hashSize; i++)
    {
        if (dictionary [i] != NULL)
        {
            D_Node *head = dictionary[i];
            D_Node *current = head;

            while (current != NULL)
            {
                D_Node * temp = current;
                current = current->next;
                free (temp);
            }
            dictionary[i] = NULL;  
            /*BUG FIX*/
        }
    }
}

/*************************************************************************
Purpose: accepts an input string and makes a caopy of that string and
returns it

Parameters:
    -const char *inputString

Returns:
    -char *copyStr
****************************************************************************/
char *copyStr(const char *inputString)
{ 
    /* make a duplicate of s */
    char *copyStr;
    int strLen;
    strLen = strlen(inputString);

    copyStr = (char *) malloc(strLen+1); /* +1 for ?\0? */

    if (copyStr != NULL)
    {
        strncpy(copyStr, inputString, strLen);
    }
    copyStr[strLen] = '\0';

    return copyStr;
}
