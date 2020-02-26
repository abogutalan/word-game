#include "boggle.h"
#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int structureCheck(int *userScore, char *word)
{
    int before;
    int diff;
    int numFail = 0;
    int wordLen = strlen(word);
    int expected;
    int actual;

    before = *userScore;
    incrementTotalScore(userScore, word);

    diff = *userScore - before;

    if (wordLen == 3 || wordLen == 4)
        expected = 2;
    else if (wordLen == 5)
        expected = 3;
    else if (wordLen == 6)
        expected = 4;
    else if (wordLen == 7)
        expected = 5;
    else if (wordLen >= 8)
        expected = 6;
    else
        expected = 1;


    if (diff == 1)
        actual = 2;
    else if (diff =  2)
        actual = 3;
    else if (diff = 3)
        actual = 4;
    else if (diff = 5)
        actual = 5;
    else if (diff = 11)
        actual = 6;
    else if (diff = 0)
        actual = 1;


    if (expected != actual)
    {
        numFail++;

        printf ("expected: ");

        switch (expected)
        {
            case 1:
                printf("no statement to run.");
                break;
            case 2:
                printf("if (word_len == 3 || word_len == 4) to run");
                break;
            case 3:
                printf("if (word_len == 5) to run.");
                break;
            case 4:
                printf("if (word_len == 6) to run.");
                break;
            case 5:
                printf("if (word_len == 7) to run.");
                break;
            case 6:
                printf("if (word_len == 8) to run.");
                break;
            default:
                printf("This should not run");
                break;
        }

        printf("\nWhat actually ran: ");

    }
    else
    {
        printf("test succeeded");
    }
    
    switch(actual)
    {
        case 1:
            printf("Just the method was called.");
            break;
        case 2:
            printf("if (word_len == 3 || word_len == 4) ran");
            break;
        case 3:
            printf("if (word_len == 5) ran");
            break;
        case 4:
            printf("if (word_len == 6) ran");
            break;
        case 5:
            printf("if (word_len == 7) ran");
            break;
        case 6:
            printf("if (word_len == 8) ran");
            break;
        default:
            printf("this should not run. ");
            break;
    }


    return numFail;
}