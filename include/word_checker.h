#include <string.h>
#include "board_generator.h"
#include <stdlib.h>

/* Basically checks if the word is on the board and returns score if it is present */
int wordChecker(struct Rolled_Dice **gameBoard, char *word);
int abidesRules(int i, int j, char *word, 
        struct Rolled_Dice** gameBoard, int subLen, int **visited);
char getLetter(int i, int j, struct Rolled_Dice **gameBoard);

int testWordChecker(char **boggle, char *word);
int testAbidesRules(int i, int j, char *word, 
        char **gameBoard, int subLen, int **visited);
char testGetLetter(int i, int j, char **boggle);

int hcWordChecker(char boggle[][4], char *word);
char hcGetLetter(int i, int j, char boggle[][4]);
int hcAbidesRules(int i, int j, char *word, char boggle[][4], int subLen, int **visited);



