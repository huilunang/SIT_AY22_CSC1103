#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char board[3][3]; // Sets the 3x3 board
char curPlayer[2];
char winner[2];
int blankSpaces;
int reset;

void checkWinner(char *winner);     // Check for winner
void printBoard();      // Output the board, to be changed to GUI linker!!!!!!!!!!!!!!!!!
void setBoard();         // Set the board to empty
void setGrid(GtkWidget *grid);
void setUp();
void showWinner(char *winner);  // Displays the winner
int checkWinnerOrDraw();

#endif