#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "boggle.h"

int main() {
	const int NUMTESTS = 10;
	int i, j, totalFails = 0, boundaryFails = 0, flowFails = 0, structureFails = 0;
	int userScore[NUMTESTS * 3];
	char word[NUMTESTS][100];
	
	/*Initialize all test userScores*/
	for (i = 0; i < NUMTESTS * 3; i++) {
		userScore[i] = 0;
	}
	
	/*Initialize default test words*/
	for (i = 0; i < 9; i++) {
		word[i][0] = 'a';
		for (j = 0; j < i; j++) {
			word[i][j + 1] = ('b' + j);
		}
		word[i][i + 1] = '\0';
	}

	/*Initialize custom test words*/
	for (i = 0; i < 90; i++) {
		word[9][i] = 'a';
	}
	word[9][i] = '\0';
	
	/*Run tests*/
	printf("Starting Boundary Analysis Tests\n");
	for (i = 0; i < NUMTESTS; i++) {
		totalFails += (boundaryFails += boundaryCheck(&(userScore[i]), word[i]));
	}
	printf("Boundary Analysis Failures: %d\n", boundaryFails);
	
	printf("Starting Data Flow Tests\n");
	for (i = 0; i < NUMTESTS; i++) {
		totalFails += (flowFails = flowCheck(&(userScore[NUMTESTS + i]), word[i]));
	}
	printf("Data Flow Failures: %d\n", flowFails);
	
	printf("Starting Structured Basis Tests\n");
	for (i = 0; i < NUMTESTS; i++) {
		totalFails += (structureFails = structureCheck(&(userScore[NUMTESTS*2 + i]), word[i]));
	}
	printf("Structured Basis Failures: %d\n", boundaryFails);
	
	printf("Total Failures: %d\n", totalFails);
}