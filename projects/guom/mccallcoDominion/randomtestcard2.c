/*
Random test for the council room card

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define MAXPLAYERS 10

int main(int argc, char *argv[]){

	srand(time(NULL));
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	int prevNumBuys, prevHandCount, prevCoinCount;

	struct gameState Game;

	int debug = 0;

	for(int j = 0; j < 2000; j++){
		int numPlayers = (rand() % MAXPLAYERS) + 1;
		int council_roomPos = 0;


		initializeGame(numPlayers, k, 20, &Game);

		Game.coins = (rand() % 100) + getCost(council_room);
		prevCoinCount = Game.coins;

		int done = rand() % 100 + 1;
		Game.numBuys = done + 1;
		Game.supplyCount[council_room] = done;
		int count = 0;

		for(int i = 0; i < done; i++){
			if(Game.coins >= getCost(council_room)){
				Game.phase = 0;
				buyCard(council_room, &Game);
				count++;
			}

		}

		if(Game.coins == (prevCoinCount - (count*getCost(council_room))) || Game.coins < 5){
			printf("Iteration %d for Council Room cost good \n", j);
		}
		else{
			printf("Iteration %d for Council Room cost failed, coins at %d \n", j, Game.coins);
			debug++;
		}

		for(int i = 0; i < numHandCards(&Game); i++){
			if(handCard(i, &Game) == council_room){
				council_roomPos = i;
				printf("council room card found at position %d \n", i);
				break;
			}
		}

		Game.handCount[whoseTurn(&Game)] = (rand() % 100) + council_room;

		prevHandCount = numHandCards(&Game);
		Game.numBuys = (rand() % 100) + 1;
		prevNumBuys = Game.numBuys;
		Game.phase = 0;

		playCard(council_roomPos, -1, -1, -1, &Game);

		if(Game.handCount[whoseTurn(&Game)] == prevHandCount - 4){
			printf("Iteration %d for Council Room hand count good \n", j);
		}
		else{
			printf("Iteration %d for Council Room hand count failed \n", j);
			debug++;
		}

		if(Game.numBuys == prevNumBuys + 1){
			printf("Iteration %d for Council Room buys good \n", j);
		}
		else{
			printf("Iteration %d for Council Room buys failed \n", j);
			debug++;
		}


	}

	if(!debug){
		printf("ALL TESTS PASSED \n");
	}
	else{
		printf("ALL TESTS FAILED \n");
	}





	





return 0;
}