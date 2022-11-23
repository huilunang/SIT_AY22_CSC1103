#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

extern char *PLAYER1;
extern char *PLAYER2;

static int easyMove();
static int hardMove();
static int minimax(char board[3][3], int player);
void computerMove(char board[3][3], GtkGrid *grid);
void playerMove(GtkWidget *grid, gpointer data);

#endif