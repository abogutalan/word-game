#include <stdio.h>
#include "dictionary.h"
#include "board_generator.h"
#include "word_checker.h"
#include "scoreboard.h"
#include "boggle.h"

#define MAX_LINE 100

int main (int argc, char ** argv)
{
    int testPoints = 0;
    char inputWord[100];
    char originalInputWord[100];

    FILE *inputFP;
    char line [MAX_LINE];
    char *fileName;

    const char * dictName = "EnglishWords.txt";
    D_Node* checkEnglish;
    D_Node* checkSubmitted;
    static D_Node* englishDictionary [BIG_HASH_SIZE];
    static D_Node* guessedWords [SMALL_HASH_SIZE];

    int currentScore = 0;
    int turnCount = 0;

    User* head = NULL;
    head = (User*)malloc(sizeof(User));

    PresetDice globalDice[16];
    Rolled_Dice *gameBoard[4];

    FILE *outputFP;


    if (!(inputFP = fopen ( dictName , "r" )))
    {
        fprintf(stderr,"Could not open file \"%s\" for reading dictionary words\n", 
            dictName);
        return 1;
    }

    while( fgets (line, MAX_LINE, inputFP)!=NULL )
    {
        /*trim new line characters*/
        line[strcspn(line, "\r\n")] = '\0';
        insert (englishDictionary, BIG_HASH_SIZE, convertToUpper2(&line));
    }
    fclose (inputFP);


    if (argc == 1)
    {
        fprintf(stdout, "playing in normal mode\n\n");

        system("clear");

        initializePresetDice(globalDice);

        rollDice(gameBoard, globalDice);

        while (turnCount >= 0)
        {
            strcpy(originalInputWord, inputWord);

            convertToUpper2(&inputWord);

            char inputName[100];

            if (strcmp(originalInputWord, "q") == 0)
            {
                /* "q" is the input, print scoreboard and exit game*/
                printScoreboard(head);
                break;
            }
            /* "n" is the input, adds user to/changes user in linked list and
               resets game */

            if (strcmp(originalInputWord, "n") == 0)
            {
                
                printScoreboard(head);
                fprintf(stdout, "Your current score: %d \n", currentScore);
                fprintf(stdout, "What is your name? \n");
                scanf("%s", inputName);

                if (userIsInList(head, inputName) == 0)
                {
                    addNode(head, inputName, currentScore);
                }
                else {
                    updateNodeWithName(head, inputName, currentScore);
                }

                currentScore = 0;

                strcpy(inputWord, "");

                freeAndResetBoard(gameBoard, globalDice);
                turnCount = 0;
                system("clear");
                continue;
            }


            printGameBoard(gameBoard);
            checkEnglish = lookup (englishDictionary, BIG_HASH_SIZE, inputWord);

            /*
            Take in user input and check for required correctness of the word.
            If correct show current score, otherwise show what makes it incurrect.
            */
            if (checkEnglish != NULL)
            {
                checkSubmitted = lookup (guessedWords, SMALL_HASH_SIZE, inputWord);

                /* check if lookup sent any errors */
                if (checkSubmitted == NULL)
                {

                    /* check to make sure the word is longer than 2 characters */
                    if (strlen(inputWord) > 2)
                    {

                        /* check if word abides game rules */
                        if (wordChecker(gameBoard, inputWord))
                        {
                            insert (guessedWords, SMALL_HASH_SIZE, inputWord);
                            incrementTotalScore(&currentScore, inputWord);
                            fprintf (stdout,
                                "Correct! You current score is now: %d \n",
                                currentScore);
                        }

                        /* word isn't valid, display to user*/
                        else
                        {
                            fprintf (stderr, "The submitted word: \'%s\'' does not abide "
                            "game rules. Try again!\n", originalInputWord);
                        }
                    }

                    /* if word is less than 3 letter put up error message to user */
                    else
                    {
                        fprintf (stderr,
                            "The submitted word: \'%s\'' "
                            "must be at least 3 letters long."
                            " Try again!\n", originalInputWord);
                    }
                }

                /* if word has already been submitted show error message */
                else
                {
                    fprintf (stderr,
                        "You have already submitted the word: \'%s\'' Try again!\n",
                        originalInputWord);
                }
            }

            /* if word is not in dictionary display error message */
            else if (turnCount > 0)
            {
                fprintf (stderr,
                   "Incorrect word: \'%s\' is not in the English Dictionary."
                   " Try again!\n", originalInputWord);
            }

            /* ask user to submit a word and grab that input */
            fprintf(stdout, "Submit a word you found:\n");
            scanf("%s", inputWord);
            turnCount++;
            system("clear");
           }

        /* clear game board memory */
        for (int i = 0; i < 4; i++)
        {
            free(gameBoard[i]);
        }

        freeAll(head);
    }

    /* argc is 2 meaning user wishes to run game in test mode */
    else if (argc == 2)
    {
        fileName =  argv[1];
        fprintf(stdout, "playing in test mode with file: %s\n", fileName);
        FILE *testFileFP;
        char testLine [MAX_LINE];
        char *testWords;
        char **testBoard;
        int fileLineCounter = 1;
        int i;
        int j;
        D_Node* testResult;
        int begin = 0;

        /*
        (1) read first line which is the board
        check to make sure file can be opened.
        */
        if (!(testFileFP = fopen ( fileName , "r" )))
        {
            fprintf(stderr,"Could not open test file \'%s\' for reading\n", fileName);
            return 1;
        }

        /* if file could not be opened/found, display to user */
        else if (!(outputFP = fopen("result.txt", "w" )))
        {
            fprintf(stderr,"Could not open result file \'%s\' for writing\n", 
                "result.txt");
            return 1;
        }

        /* read each line within opened file */
        while (fgets (testLine, MAX_LINE, testFileFP)!=NULL )
        {
            /* trim new line characters */
            testLine[strcspn(testLine, "\r\n")] = '\0';

            if (fileLineCounter == 1)
            {
                convertToBoard(testLine, &testBoard);

                /* this can be removed, its just for testing purposes */
                for (i = 0; i < 4; i++)
                {
                    for (j = 0; j < 4; j++)
                    {
                        if (j != 3)
                        {
                            fprintf(stdout, "%c \t", testBoard[i][j] );
                        }

                        else
                        {
                            fprintf(stdout, "%c \n", testBoard[i][j] );
                        }
                    }
                }
            }

            /* while counter is 2, prepare text and look up within dictionary */
            else if (fileLineCounter >= 2)
            {
                for (char *p = strtok(testLine,","); p != NULL; p = strtok(NULL, ","))
                {
                    checkEnglish = lookup (englishDictionary, BIG_HASH_SIZE,
                        convertToUpper(&p));

                    /* test if word is a valid english word */
                    if (checkEnglish != NULL)
                    {
                        checkSubmitted = lookup (guessedWords, SMALL_HASH_SIZE, p);

                        /* test if word has already been submitted yet */
                        if (checkSubmitted == NULL)
                        {
                            /* test if word is correct */
                            if (testWordChecker(testBoard, p))
                            {
                                insert (guessedWords, SMALL_HASH_SIZE, p);
                                incrementTotalScore(&testPoints, p);
                                fprintf(stdout,"Correct! You total score is now: %d \n",
                                    testPoints );
                            }

                            /* if test shows word does not abide by game rules, display */
                            else
                            {
                                if (begin == 0)
                                {
                                    fprintf(outputFP, "%s", p );
                                    begin++;
                                }

                                else
                                {
                                    fprintf(outputFP, ",%s", p );
                                }

                                fprintf(stderr,
                                    "The submitted word: \'%s\'' does"
                                    " not abide game rules. Try again!\n", p);
                            }

                        }

                        /* if test shows word has already been submitted display */
                        else
                        {
                            if (begin == 0)
                            {
                                fprintf(outputFP, "%s", p );
                                begin++;
                            }

                            else
                            {
                                fprintf(outputFP, ",%s", p );
                            }

                            fprintf(stderr,
                                "You have already submitted the word: \'%s\'' "
                                    "Try again!\n", p);
                        }
                     }

                    /* if test shows word is not in dictionary display */
                    else
                    {
                        if (begin == 0)
                        {
                            fprintf(outputFP, "%s", p );
                            begin++;
                        }

                        else
                        {
                            fprintf(outputFP, ",%s", p );
                        }

                         fprintf(stderr,
                            "Incorrect word: \'%s\'' is not in the English Dictionary. "
                            "Try again!\n",
                            p);
                    }
                }
            }
            /* increment counter */
            fileLineCounter++;
        }

        /* display test results */
        fprintf(outputFP, "\n");
        fprintf(outputFP, "%d\n", testPoints);
        fclose (testFileFP);

        /* empty memory */
        for (int i = 0; i < 4; i++)
        {
            free(testBoard[i]);
        }

        free(testBoard);
        fclose(outputFP);
    }

    /* garbage collection */
    freeDictionary(englishDictionary, BIG_HASH_SIZE);
    freeDictionary(guessedWords, SMALL_HASH_SIZE);
    return 0;
}