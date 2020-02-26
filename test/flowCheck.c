#include "boggle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"

/* Written by Ian McKechnie and Abdullah Burhan Ogutalan
*  Written on 13/11/19
*/

int flowCheck(int *userScore, char *word)
{

	int totalPassFailCount, word_len, myWord_len, i, *myUserScore, *testScore, originalScore;
	char *myWord = NULL, *testWord1 = NULL, *testWord2 = NULL;
	
	totalPassFailCount = 0;
	
	/******First Test -> Abdullah*/
	
	word_len = strlen(word);
	myWord = malloc(strlen(word)+ 1);
	myUserScore = malloc(sizeof(int));
	
    for(i = 0; i < word_len; i++)
    {        
        myWord[i] = 'a';
    }
	myWord[i] = 0;

    myWord_len = strlen(myWord);
    *myUserScore = *userScore;

    /*if cases for given input*/
    incrementTotalScore(userScore, word);
    /*if cases for my variables*/
    incrementTotalScore(myUserScore, myWord);

    /*Comparing the outputs*/
    if(*userScore != *myUserScore)
    {
        printf("Test failed*\n");
		totalPassFailCount++;
    }
    if(word_len != myWord_len)
    {
        printf("Test failed***\n");
		totalPassFailCount++;
	}
    
	free(myWord);
	free(myUserScore);
	
	/******Second test -> Ian*/
	
	originalScore = *userScore;
	
	testScore = malloc(sizeof(int));
	*testScore = 0;
	
	testWord1 = malloc( sizeof(char) * (strlen(word) + 6) );
	strcpy(testWord1, word);
	strcat(testWord1, "aa\n");

	printf("Length of tested word = %d\n", strlen(word));
	printf("Len larger word = %d\n", strlen(testWord1));
	/*Make sure the word is of valid size otherwise it will crash by adding negative characters to a string*/
	if(strlen(word) <= 2)
	{
	    printf("<= 2\n");
		incrementTotalScore(userScore, word);
		incrementTotalScore(testScore, testWord1);
		
		if (*userScore - *testScore == originalScore) {
			printf("Test Failed-\n");
			totalPassFailCount++;
		}
		
		
	}
    else 
	{
		
		/*Setting up the first test case (smaller word test)*/
		testWord2 = malloc(sizeof(char) * (strlen(word) + 2) );
		
		strcpy(testWord2, "a");
		for (i = 1; i < strlen(word) - 1; i++) {
			strcat(testWord2, "a");
		}
		
		strcat(testWord2, "\0");		
		
		/*Running the first test (smaller word)*/
		incrementTotalScore(userScore, word);
		incrementTotalScore(testScore, testWord1);
		
		
		if (*userScore - *testScore == originalScore) {
			printf("Test Failed, testScore(%d) + originalScore(%d) != userScore(%d)\n", *testScore, originalScore, *userScore);
			totalPassFailCount++;
		}
		
		/*Resetting the value and tring again for a smaller word*/
		*userScore = originalScore;
		*testScore = 0;
		
		incrementTotalScore(userScore, word);
		incrementTotalScore(testScore, testWord2);
		printf("len second word = %d\n", strlen(testWord2));
		
		printf("failed if: %d - %d == %d\n", *userScore, *testScore, originalScore);
		
		if (*userScore - *testScore == originalScore) {
			printf("Test Failed: Incorrect score\n");
			totalPassFailCount++;
		}
	}
	
    if (testWord2)
	    free(testWord2);
    
    if (testWord1)
	    free(testWord1);
    
    if (testScore)
	    free(testScore);

	return totalPassFailCount;

}