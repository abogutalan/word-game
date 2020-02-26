#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boggle.h"
#include "test.h"

int boundaryCheck (int *score, char *word) {
  int expectedVal;
  int inputScore;
  int len;

  inputScore = *score;

  /*determines the expected output score*/
  if (word == NULL) {
    expectedVal = *score;
  } else if ((len = strlen(word)) == 1) {
    expectedVal = *score;
  } else if ((strlen(word) > 2) && (strlen(word) < 5)) {
    expectedVal = *score + 1;
  } else if (strlen(word) == 5) {
    expectedVal = *score + 2;
  } else if (strlen(word) == 6) {
    expectedVal = *score + 3;
  } else if (strlen(word) == 7) {
    expectedVal = *score + 5;
  } else if (strlen(word) > 8) {
    expectedVal = *score + 11;
  } else {
    expectedVal = *score;
  }
  /*calls function with test values*/
  incrementTotalScore(score, word);

  if (expectedVal == *score) {
    /*the test is passed, print out stuff*/
    printf("----------- PASSED THE TEST -------------\n");
    printf("input:    int *score: %d char *word: %s\n",inputScore, word);
    printf("expected: int *score: %d\n", expectedVal);
    printf("actual:   int *score: %d\n", *score);
    printf("------------------------------------------\n");
    return 0;
  } else {
    /*the test failed*/
    printf("----------- FAILED THE TEST -------------\n");
    printf("input:    int *score: %d char *word: %s\n",inputScore, word);
    printf("expected: int *score: %d\n", expectedVal);
    printf("actual:   int *score: %d\n", *score);
    printf("------------------------------------------\n");
    return 1;
  }

  return 0;
}
