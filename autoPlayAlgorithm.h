#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "getYachtScore.h"

void moveArrow() {

}

int opponentBestPlayAlgorithm(Dice dice, ScoreBoard scoreBoard, int rerollCount) {
	if (rerollCount > 0) {

		int diceValues[5] = { dice.value[0], dice.value[1], dice.value[2], dice.value[3], dice.value[4] };
		bubbleSort(diceValues);

		for (int i = 0; i < 5; i++) {
			dice.value[i] = diceValues[i];
		}

		int max = 0, bestCombination = 0;
		for (int i = 0; i < 12; i++) {
			if (max < scoreBoard.score[i].value) {
				if (scoreBoard.score[i].isHighlighted == true) {
					max = scoreBoard.score[i].value;
					bestCombination = i;
				}
			}
		}

		if (bestCombination == 10 || bestCombination == 11) {
			scoreBoard.score[bestCombination].isHighlighted == false;
			scoreBoard.score[bestCombination].isUsed == true;
			return 0;
		}
	}
}

// Return Value : "0 : Selected", "1 : Requested Reroll"