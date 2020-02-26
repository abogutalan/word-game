/*
 * Name: Alexander Blankenstein
 * Student Number: 1094640
 * Email: ablanken@uoguelph.ca
 * 
 * Name: Aaron Cooper
 * Student Number: 1065641
 * Email: acoope07@uoguelph.ca
 * 
 * Project: CIS3250 A2
 * Date: 10/8/2019
 * 
 * 
 */

#include "boggle.h"

/**
 - set up board,
 - set up dictionary,
 **/
void incrementTotalScore(int *userScore, char *word)
{
    int word_len = strlen(word);
    fprintf(stdout, "word_len: %d\n",word_len );

    if (word_len == 3 || word_len == 4)
    {
        *userScore += 1;
    }

    else if (word_len == 5)
    {
        *userScore += 2;
    }

    else if (word_len == 6)
    {
        *userScore += 3;
    }

    else if (word_len == 7)
    {
        *userScore += 5;
    }

    else if (word_len >= 8)
    {
        *userScore += 11;
    }
}



void freeAndResetBoard(struct Rolled_Dice** gameBoard,
    struct Preset_Dice* inputArrayOfDice)
{

    for (int i = 0; i < 4; i++)
    {
        free(gameBoard[i]);
    }
    rollDice(gameBoard, inputArrayOfDice);
}


char *convertToUpper(char **upper)
{
    char *upperDeref = *upper;

    for(int i = 0; upperDeref[i]; i++)
    {
      upperDeref[i] = toupper(upperDeref[i]);
    }
    return upperDeref;
}


char *convertToUpper2(char (*upper)[])
{
    char *upperDeref = *upper;

    for(int i = 0; upperDeref[i]; i++)
    {
      upperDeref[i] = toupper(upperDeref[i]);
    }
    return upperDeref;
}






