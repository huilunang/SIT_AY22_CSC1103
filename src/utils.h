#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

// Number of blank spaces left to check for draw
int blankSpaces;
// Array to store the moves made by player
char board[3][3];
// Array to store the empty positions coordinates
int boardEmptyPos[9][2];
// To track the current player symbol
char curPlayer[2];
// Set flag to enable game reset
int reset;
// To track the winner
char winner[2];
// Set flag if playing against computer is easy or hard
int aiEasyMode;
// Set flag if current play mode is 1 or 2 Player
int modeP1;

void checkEmptyPos(int boardEmptyPos[9][2]);
void checkWinner(char *winner);
int checkWinnerOrTie();
void incCounterScore(GtkLabel *obj);
void setBoard(GtkGrid *grid);
void setUp();
void resetBoard();

#endif