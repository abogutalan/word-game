#ifndef BOGGLE_H
#define BOGGLE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "board_generator.h"
#include "word_checker.h"
#include "scoreboard.h"


void incrementTotalScore(int *userScore, char *word);

void freeAndResetBoard(struct Rolled_Dice** gameBoard,
    struct Preset_Dice* inputArrayOfDice);

char *convertToUpper(char **upper);

char *convertToUpper2(char (*upper)[]);

#endif