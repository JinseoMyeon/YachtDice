#include <stdio.h>
#include <stdbool.h>
#pragma warning(disable:4996)

typedef struct Dice {
	int value[5];
	bool isStored[5];
} Dice;

typedef struct Score {
	bool isUsed;
	bool isHighlighted;
	int value;
}Score;

typedef struct ScoreBoard {
	Score score[12];
	int subTotal;
	int bonus;
	int total;
}ScoreBoard;


void bubbleSort(int arr[]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4 - i; j++)
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}


int getDiceLists(Dice dice, int cmpNum) {
	int result = 0;
	for (int i = 0; i < 5; i++) {
		if (dice.value[i] == cmpNum) {
			result += dice.value[i];
		}
	}
	return result;
}

int getChoice(Dice dice) {
	int result = 0;
	for (int i = 1; i <= 6; i++) {
		result += getDiceLists(dice, i);
	}
	return result;
}

int getFourKinds(Dice dice) {
	int result = 0;
	int diceValues[5] = {dice.value[0], dice.value[1], dice.value[2], dice.value[3], dice.value[4]};

	bubbleSort(diceValues);

	if (diceValues[0] == diceValues[1] && diceValues[2] == diceValues[3] && diceValues[1] == diceValues[2])
		result = getChoice(dice);
	if (diceValues[1] == diceValues[2] && diceValues[3] == diceValues[4] && diceValues[2] == diceValues[3])
		result = getChoice(dice);
	if (diceValues[0] == diceValues[1] && diceValues[2] == diceValues[3] && diceValues[1] == diceValues[2] && diceValues[3] == diceValues[4])
		result = getChoice(dice);
	return result;
}

int getFullHouse(Dice dice) {
	int result = 0;
	int diceValues[5] = { dice.value[0], dice.value[1], dice.value[2], dice.value[3], dice.value[4] };

	bubbleSort(diceValues);

	if (diceValues[0] == diceValues[1] && diceValues[1] != diceValues[2] && diceValues[2] == diceValues[3] && diceValues[3] == diceValues[4])
		result = getChoice(dice);
	else if (diceValues[0] == diceValues[1] && diceValues[1] == diceValues[2] && diceValues[2] != diceValues[3] && diceValues[3] == diceValues[4])
		result = getChoice(dice);
	return result;
}

int getSmallStraight(Dice dice) {
	int diceValues[5] = { dice.value[0], dice.value[1], dice.value[2], dice.value[3], dice.value[4] };
	bubbleSort(diceValues);
	for (int i = 0; i < 4; i++)
		if (diceValues[i] == diceValues[i + 1])
			diceValues[i] = -1;

	bubbleSort(diceValues);
	if (diceValues[0] + 1 == diceValues[1] && diceValues[1] + 1 == diceValues[2] && diceValues[2] + 1 == diceValues[3])
		return 15;
	if (diceValues[1] + 1 == diceValues[2] && diceValues[2] + 1 == diceValues[3] && diceValues[3] + 1 == diceValues[4])
		return 15;
	if (diceValues[1] + 1 == diceValues[2] && diceValues[2] + 1 == diceValues[3] && diceValues[3] + 1 == diceValues[4] && diceValues[0] + 1 == diceValues[1])
		return 15;
	else return 0;
}

int getLargeStraight(Dice dice) {
	int diceValues[5] = { dice.value[0], dice.value[1], dice.value[2], dice.value[3], dice.value[4] };
	bubbleSort(diceValues);
	if (diceValues[1] + 1 == diceValues[2] && diceValues[2] + 1 == diceValues[3] && diceValues[3] + 1 == diceValues[4] && diceValues[0] + 1 == diceValues[1])
		return 30;
	else return 0;
}

int getYacht(Dice dice) {
	if (dice.value[0] == dice.value[1] && dice.value[2] == dice.value[3] && dice.value[1] == dice.value[2] && dice.value[3] == dice.value[4])
		return 50;
	else
		return 0;
}

void getScore(Dice dice, ScoreBoard* scoreBoard, int turn) {
	scoreBoard[turn].subTotal = 0;
	for (int i = 1; i <= 6; i++) {
		if (scoreBoard[turn].score[i - 1].isUsed == false) {
			scoreBoard[turn].score[i - 1].value = getDiceLists(dice, i);
			if (scoreBoard[turn].score[i - 1].value != 0)
				scoreBoard[turn].score[i - 1].isHighlighted = true;
			else
				scoreBoard[turn].score[i - 1].isHighlighted = false;
		}
		else scoreBoard[turn].subTotal += scoreBoard[turn].score[i - 1].value;
	}

	if (scoreBoard[turn].subTotal >= 63)
		scoreBoard[turn].bonus = 35;

	if (scoreBoard[turn].score[6].isUsed == false) {
		scoreBoard[turn].score[6].value = getChoice(dice);
		if (scoreBoard[turn].score[6].value != 0)
			scoreBoard[turn].score[6].isHighlighted = true;
		else
			scoreBoard[turn].score[6].isHighlighted = false;
	}
	if (scoreBoard[turn].score[7].isUsed == false) {
		scoreBoard[turn].score[7].value = getFourKinds(dice);
		if (scoreBoard[turn].score[7].value != 0)
			scoreBoard[turn].score[7].isHighlighted = true;
		else
			scoreBoard[turn].score[7].isHighlighted = false;
	}
	if (scoreBoard[turn].score[8].isUsed == false) {
		scoreBoard[turn].score[8].value = getFullHouse(dice);
		if (scoreBoard[turn].score[8].value != 0)
			scoreBoard[turn].score[8].isHighlighted = true;
		else
			scoreBoard[turn].score[8].isHighlighted = false;
	}
	if (scoreBoard[turn].score[9].isUsed == false) {
		scoreBoard[turn].score[9].value = getSmallStraight(dice);
		if (scoreBoard[turn].score[9].value != 0)
			scoreBoard[turn].score[9].isHighlighted = true;
		else
			scoreBoard[turn].score[9].isHighlighted = false;
	}
	if (scoreBoard[turn].score[10].isUsed == false) {
		scoreBoard[turn].score[10].value = getLargeStraight(dice);
		if (scoreBoard[turn].score[10].value != 0)
			scoreBoard[turn].score[10].isHighlighted = true;
		else
			scoreBoard[turn].score[10].isHighlighted = false;
	}
	if (scoreBoard[turn].score[11].isUsed == false) {
		scoreBoard[turn].score[11].value = getYacht(dice);
		if (scoreBoard[turn].score[11].value != 0)
			scoreBoard[turn].score[11].isHighlighted = true;
		else
			scoreBoard[turn].score[11].isHighlighted = false;

	}

	scoreBoard[turn].total = scoreBoard[turn].bonus;
	for (int i = 0; i < 12; i++) {
		if (scoreBoard[turn].score[i].isUsed != false)
			scoreBoard[turn].total += scoreBoard[turn].score[i].value;
	}
}