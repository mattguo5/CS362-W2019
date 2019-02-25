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

	int debug = 0;

	struct gameState Game;

	for(int j = 0; j < 30000; j++){
		printf("Iteration number %d \n", j);
		int numPlayers = rand() % MAXPLAYERS + 1;

		initializeGame(numPlayers, k, 20, &Game);

		int totalCoinCards, prevHandCount, handCopper, handSilver, handGold;
		int count = 0;
		int newCount = 0;

		int adventurerPos = -1;

		Game.coins = 10;
		Game.numBuys = 1;

		Game.supplyCount[adventurer] = rand() % 100 + 1;

		buyCard(adventurer, &Game);

		for(int i = 0; i < numHandCards(&Game); i++){
			if(handCard(i, &Game) == adventurer){
				adventurerPos = i;
				printf("Adventurer found at position %d \n", i);
				break;
			}
		}

		Game.deckCount[whoseTurn(&Game)] = rand() % 100;
		Game.supplyCount[copper] = rand() % 10 + 1;
		Game.supplyCount[silver] = rand() % 10 + 1;
		Game.supplyCount[gold] = rand() % 10 + 1;

		handCopper = rand() % 10 + 1;
		handSilver = rand() % 10 + 1;
		handGold = rand() % 10 + 1;

		for(int i = 0; i < handCopper; i++){
			if(i < Game.supplyCount[copper]){
				gainCard(copper, &Game, 0, whoseTurn(&Game));
				count++;
			}
		}

		for(int i = 0; i < handSilver; i++){
			if(i < Game.supplyCount[silver]){
				gainCard(silver, &Game, 0, whoseTurn(&Game));
				count++;
			}
		}

		for(int i = 0; i < handGold; i++){
			if(i < Game.supplyCount[gold]){
				gainCard(gold, &Game, 0, whoseTurn(&Game));
				count++;
			}
		}

		shuffle(whoseTurn(&Game), &Game);

		totalCoinCards = count;
		prevHandCount = numHandCards(&Game);

		Game.phase = 0;
		playCard(adventurerPos, -1, -1, -1, &Game);

		for(int i = 0; i < Game.deckCount[whoseTurn(&Game)]; i++){
			if(Game.deck[whoseTurn(&Game)][i] == copper || Game.deck[whoseTurn(&Game)][i] == silver || Game.deck[whoseTurn(&Game)][i] == gold){
				newCount++;
			}
		}

		if(newCount == totalCoinCards - 2){
			printf("Number of deck coin cards good at before: %d and after: %d \n", totalCoinCards, newCount);
		}
		else{
			printf("Number of deck coin cards failed at before: %d and after: %d \n", totalCoinCards, newCount);
			debug++;
		}

		if(numHandCards(&Game) == prevHandCount + 2){
			printf("Number of hand cards good at before: %d and after: %d \n", prevHandCount, numHandCards(&Game));
		}
		else{
			printf("Number of hand cards failed at before: %d and after: %d \n", prevHandCount, numHandCards(&Game));
			debug++;
		}
	}

	if(debug){
		printf("ALL TEST FAILED \n");

	}
	else{
		printf("ALL TEST PASSED \n");
	}



	return 0;
}