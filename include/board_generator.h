#ifndef BOARD_GEN
#define BOARD_GEN

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


/*The pre-set dice which keep their values between games.*/
typedef struct Preset_Dice
{
    char *configurations;
    int position;
} PresetDice;

/*The rolled dice which do not keep their values between games.*/
typedef struct Rolled_Dice
{
    char character;
    int position;
} Rolled_Dice;


void initializePresetDice(struct Preset_Dice* inputArrayOfDice);
void rollButNotShuffleDice(struct Rolled_Dice* gameDice,
        struct Preset_Dice* inputArrayOfDice);

void shuffleRolledDicePositions(struct Rolled_Dice* gameDice);
void printGameBoard(struct Rolled_Dice** gameBoard);
void rollDice(struct Rolled_Dice** gameBoard,
        struct Preset_Dice* inputArrayOfDice);

void convertToBoard(char *letters, char ***board);
void printHcBoard(char boggle[][4]);

#endif
