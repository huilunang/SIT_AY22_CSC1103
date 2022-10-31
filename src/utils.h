#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char *board[3][3]; // Sets the 3x3 board

char checkWinner();     // Check for winner
void printBoard();      // Output the board, to be changed to GUI linker!!!!!!!!!!!!!!!!!
void setBoard();         // Set the board to empty
void showWinner(char winner);  // Displays the winner

#endif