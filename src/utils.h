#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

int blankSpaces;
char board[3][3];
int boardEmptyPos[9][2];
int countEmptyPos;
char curPlayer[2];
int reset;
char winner[2];
int modeP1;
int aiEasyMode;

void checkEmptyPos(int boardEmptyPos[9][2]);
void checkWinner(char *winner);
int checkWinnerOrDraw();
void incCounterScore(GtkLabel *obj);
void setBoard(GtkGrid *grid);
void setUp(GtkGrid *grid);

#endif