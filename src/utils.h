#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char board[3][3];
char curPlayer[2];
char winner[2];
int blankSpaces;
int reset;

void checkWinner(char *winner);
int checkWinnerOrDraw();
void incCounterScore(GtkLabel *obj);
void setBoard(GtkGrid *grid);
void setUp(GtkGrid *grid);

#endif