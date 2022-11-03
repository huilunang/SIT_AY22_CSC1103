#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

extern char *PLAYER1;
extern char *PLAYER2;

int aiMove[3];

void playerMove(GtkWidget *grid, gpointer data);
void computerMove(char board[3][3], GtkGrid *grid);
int minimax(char board[3][3], int player);

#endif