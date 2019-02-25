/*
Random test for the great hall card

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define MAXPLAYER 10
#define MAXNUMACTIONS 10

int main(int argc, char *argv[]){

	srand(time(NULL));
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	int prevNumAction, prevHandCount;
	int debug = 0;

	struct gameState Game;

	for(int i = 0; i < 2000; i++){
		int numPlayer = rand() % MAXPLAYER + 1;

		initializeGame(numPlayer, k, 20, &Game);

		int great_hallPos = -1;

		Game.numBuys = 1;
		Game.coins = 10;
		buyCard(great_hall, &Game);

		int check = 0;

		for(int j = 0; j < numHandCards(&Game); j++){
			if(handCard(j, &Game) == great_hall){
				great_hallPos = j;
				check = 1;
				printf("great hall found! At position %d \n", j);
			}
		}

		if(!check){
			printf("No great hall cards in hand \n");
		}


		Game.numActions = rand() % MAXNUMACTIONS + 1;
		prevNumAction = Game.numActions;
		Game.handCount[whoseTurn(&Game)] = rand() % 100 + great_hallPos;
		prevHandCount = numHandCards(&Game);
		Game.phase = 0;

		playCard(great_hallPos, -1, -1, -1, &Game);

		if(Game.numActions != prevNumAction){
			printf("Iteration %d for number actions failed \n", i);
			debug++;
		}
		else{
			printf("Iteration %d for number actions good \n", i);
		}

		if(numHandCards(&Game) != prevHandCount){
			printf("Iteration %d for number hand count failed at new: %d and old: %d \n", i, numHandCards(&Game), prevHandCount);
			debug++;
		}
		else{
			printf("Iteration %d for number hand count good \n", i);
		}
	}

	if(!debug){
		printf("ALL TEST PASSED \n");
	}
	else{
		printf("TEST FAILED\n");
	}
	







	return 0;
}