#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "getYachtScore.h"
#include "getConsoleControl.h"

#pragma warning(disable:4996)

int switchPos = 0;

int diceDisplay[7][9][3] = {
	{{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,1,0},{0,0,0}},
	{{1,0,0},{0,0,0},{0,0,1}},
	{{1,0,0},{0,1,0},{0,0,1}},
	{{1,0,1},{0,0,0},{1,0,1}},
	{{1,0,1},{0,1,0},{1,0,1}},
	{{1,0,1},{1,0,1},{1,0,1}}
};


typedef struct display {
	bool value;
}display;

display inGameScoreBoard(ScoreBoard *s) {
	char displayTitle[12][14] = {
		" Aces        ",
		" Deuces      ",
		" Threes      ",
		" Fours       ",
		" Fives       ",
		" Sixes       ",
		" Choice      ",
		" 4 of Kinds  ",
		" Full House  ",
		" S. Straight ",
		" L. Straight ",
		" Yacht       ",
	};
	for (int i = 0; i < 22; i++) {
		setColor(0x0F);
		setCursor(0, i);
		switch (i) {
		case 0:
			printf("忙式式式式式式式式式式式式式成式式式式式式式式式成式式式式式式式式式忖");
			break;
		case 1:
			printf("弛             弛  Player 弛 Opponent弛");
			break;
		case 2:
		case 9:
		case 12:
		case 19:
			printf("戍式式式式式式式式式式式式式托式式式式式式式式式托式式式式式式式式式扣");
			break;
		case 3 :
		case 4 :
		case 5:
		case 6:
		case 7: 
		case 8 : 
			printf("弛%s弛", displayTitle[i - 3]);
			if (s[0].score[i - 3].isUsed == true) setColor(0x08);
			else if (s[0].score[i - 3].isHighlighted == true) setColor(0x0a);
			else setColor(0x0F);
			printf("    %02d   ", s[0].score[i - 3].value);
			setColor(0x0F);
			printf("弛");
			if (s[1].score[i - 3].isUsed == true) setColor(0x08);
			else if (s[1].score[i - 3].isHighlighted == true) setColor(0x0a);
			else setColor(0x0F);
			printf("    %02d   ", s[1].score[i - 3].value);
			setColor(0x0F);
			printf("弛");
			break;
		case 10:
			printf("弛 SubTotal    弛   %02d/63 弛   %02d/63 弛", s[0].subTotal, s[1].subTotal);
			break;
		case 11:
			printf("弛 Bonus       弛    %02d   弛    %02d   弛", s[0].bonus, s[1].bonus);
			break;
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
			printf("弛%s弛", displayTitle[i - 7]);
			if (s[0].score[i - 7].isUsed == true) setColor(0x08);
			else if (s[0].score[i - 7].isHighlighted == true) setColor(0x0a);
			else setColor(0x0F);
			printf("    %02d   ", s[0].score[i - 7].value);
			setColor(0x0F);
			printf("弛");
			if (s[1].score[i - 7].isUsed == true) setColor(0x08);
			else if (s[1].score[i - 7].isHighlighted == true) setColor(0x0a);
			else setColor(0x0F);
			printf("    %02d   ", s[1].score[i - 7].value);
			setColor(0x0F);
			printf("弛");
			break;
		case 20:
			printf("弛 Total       弛   %04d  弛   %04d  弛", s[0].total, s[1].total);
			break;
		case 21:
			printf("戌式式式式式式式式式式式式式扛式式式式式式式式式扛式式式式式式式式式戎");
		}
	}
}

display selectArrow(ScoreBoard *scoreBoard, int turn, int buttonPos) {
	int i = 0;

	if (buttonPos == 0) {

		char displayTitle[12][14] = {
			"Aces",
			"Deuces",
			"Threes",
			"Fours",
			"Fives",
			"Sixes",
			"Choice",
			"4 of Kinds",
			"Full House",
			"S. Straight",
			"L. Straight",
			"Yacht"
		};

		if (turn == 1) i += 10;

		switch (switchPos) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			setCursor(16 + i, switchPos + 3);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			setCursor(16 + i, switchPos + 7);
			break;
		}

		printf("Ⅰ");
	}

}

display diceRollResult(Dice dice, int i) {
	setCursor(10 * i + 40, 2);
	printf("忙式式式式式式式忖");
	for (int y = 0; y < 3; y++) {
		setCursor(10 * i + 40, y + 3);
		printf("弛 ");
		for (int x = 0; x < 3; x++) {
			if (diceDisplay[dice.value[i]][y][x] == 1) printf("≒");
			else printf("  ");
		}
		printf("弛");
	}
	setCursor(10 * i + 40, 6);
	printf("戌式式式式式式式戎");
	setColor(0x0F);
	setCursor(36, 0);
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");
	setCursor(36, 8);
	printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");
	for (int j = 1; j <= 7; j++) {
		setCursor(36, j);
		printf("弛");
		setCursor(92, j);
		printf("弛");
	}
}

display bestCombination(Dice dice, ScoreBoard *s, int turn) {
	setCursor(57, 9);
	printf("               ");
	setCursor(36, 9);
	printf("弛 ");
	setCursor(92, 9);
	printf("弛");
	setCursor(36, 10);
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
	setColor(0x0E);
	if (getYacht(dice) != 0 && s[turn].score[11].isUsed == false) {
		setCursor(61, 9);
		printf("Yacht!");
	}
	else if (getLargeStraight(dice) != 0 && s[turn].score[10].isUsed == false) {
		setCursor(57, 9);
		printf("Large Straight");
	}
	else if (getFourKinds(dice) != 0 && s[turn].score[7].isUsed == false) {
		setCursor(57, 9);
		printf("Four of a Kind");
	}
	else if (getSmallStraight(dice) != 0 && s[turn].score[9].isUsed == false) {
		setCursor(57, 9);
		printf("Small Straight");
	}
	else if (getFullHouse(dice) != 0 && s[turn].score[8].isUsed == false) {
		setCursor(59, 9);
		printf("Full House");
	}


}

display rerollButton(int buttonPos, int rerollCount) {
	if (buttonPos == 0) {
		setColor(0x07);
		setCursor(36, 18);
		printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");
		setCursor(36, 19);
		printf("弛");
		printf("               Reroll Dice (%d/3 Rolled)                ", 3 - rerollCount);
		printf("弛");
		setColor(0x07);
		setCursor(36, 20);
		printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
	}
	if (buttonPos == 1) {
		setColor(0x0A);
		setCursor(36, 18);
		printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");
		setCursor(36, 19);
		printf("弛");
		printf("               Reroll Dice (%d/3 Rolled)                ", 3 - rerollCount);
		printf("弛");
		setColor(0x0A);
		setCursor(36, 20);
		printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
	}
}

int main() {
	clearCursor();
	resizeConsole(95, 22);
	int turn = 0;
	int buttonPos = 1; // 0 = Scoreboard, 1 = Reroll Button

	ScoreBoard scoreBoard[2] = {
		{ {{false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}},0,0,0 },
		{ {{false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}, {false,false,0}},0,0,0 }
	};

	srand(time(NULL));

	Dice dice;

	for (int i = 0; i < 5; i++) {
		dice.value[i] = rand() % 6 + 1;
		dice.isStored[i] = false;
		diceRollResult(dice, i);
		setCursor(2 * i + 36, 6);
	}

	switchPos = 0;
	int rerollCount = 2;
	int playCount = 0;
	rerollButton(buttonPos, rerollCount);

	while (1) {
		if (playCount > 11) {
			// End
			system("cls");
			break;
		}
		getScore(dice, scoreBoard, turn);
		bestCombination(dice, scoreBoard, turn);
		inGameScoreBoard(scoreBoard);
		selectArrow(scoreBoard, turn, buttonPos);

		if (_kbhit()) {
			char key = _getch();
			setCursor(40, 8);
			printf("%d", key);
			if (key == 114)
				if (rerollCount > 0) {
					for (int i = 0; i < 5; i++) {
						if (dice.isStored[i] == false) {
							dice.value[i] = rand() % 6 + 1;
						}
						setCursor(i + 36, 1);
						if (dice.isStored[i] == true) setColor(0x08);
						else setColor(0x0F);
						diceRollResult(dice, i);
					}
					rerollCount--;
				}

			if (key == 80) { // down
				if (scoreBoard[turn].score[switchPos + 1].isUsed == true && switchPos < 11) {
					switchPos++;
					while (scoreBoard[turn].score[switchPos].isUsed && switchPos < 11) switchPos++;
				}
				else {
					if (switchPos < 11) switchPos++;
				}

			}

			if (key == 72) { // up
				if (scoreBoard[turn].score[switchPos - 1].isUsed == true && switchPos > 0) {
					switchPos--;
					while (scoreBoard[turn].score[switchPos].isUsed && switchPos > 0) switchPos--;
				}
				else {
					if (switchPos > 0) switchPos--;
				}

			}

			if (key == 13) { // enter
				if (buttonPos == 0) {
					if (switchPos >= 0 && switchPos <= 11) {
						if (scoreBoard[turn].score[switchPos].isUsed == false) {
							scoreBoard[turn].score[switchPos].isUsed = true;
							getScore(dice, scoreBoard, turn);
							for (int j = 0; j < 12; j++) {
								if (scoreBoard[turn].score[j].isUsed == false) {
									scoreBoard[turn].score[j].isHighlighted = false;
									scoreBoard[turn].score[j].value = 0;
								}
							}
							if (turn == 0)
								turn = 1; // turn = 1;
							else
								turn = 0;

							if (turn == 0)
								playCount++;

							for (int i = 0; i < 5; i++) {
								dice.isStored[i] = false;
								if (dice.isStored[i] == false) {
									dice.value[i] = rand() % 6 + 1;
								}
								setCursor(i + 36, 1);
								if (dice.isStored[i] == true) setColor(0x08);
								else setColor(0x0F);
								diceRollResult(dice, i);
							}
							rerollCount = 2;
							rerollButton(buttonPos, rerollCount);
							selectArrow(scoreBoard, turn, buttonPos);
						}
					}
				}
				if (buttonPos == 1) {
					if (rerollCount > 0) {
						for (int i = 0; i < 5; i++) {
							if (dice.isStored[i] == false) {
								dice.value[i] = rand() % 6 + 1;
							}
							setCursor(i + 36, 1);
							if (dice.isStored[i] == true) setColor(0x08);
							else setColor(0x0F);
							diceRollResult(dice, i);
						}
						rerollCount--;
						rerollButton(buttonPos, rerollCount);
						selectArrow(scoreBoard, turn, buttonPos);
					}
				}
			}

			if (key == 75) {
				buttonPos = 0;
				rerollButton(buttonPos, rerollCount);
				selectArrow(scoreBoard, turn, buttonPos);
			}

			if (key == 77) {
				buttonPos = 1;
				rerollButton(buttonPos, rerollCount);
				selectArrow(scoreBoard, turn, buttonPos);
			}

			for (int i = 0; i < 5; i++) {
				if (key == i + 49) {
					if (dice.isStored[i] == false)
						dice.isStored[i] = true;
					else {
						dice.isStored[i] = false;
					}
				}
			}

			for (int i = 0; i < 5; i++) {
				setCursor(i + 36, 1);
				if (dice.isStored[i] == true) setColor(0x08);
				else setColor(0x0F);
				diceRollResult(dice, i);
			}
		}

		Sleep(10);

	}

	setColor(0x00);
	getchar();

}

