#include "main.h"
#include "players.h"
#include "utils.h"

// Function to check if there's a winner
char checkWinner()
{
    // check horizontal
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // check vertical
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    // check diagonal
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

void printBoard() // setting the board
{
    printf("\n");
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void showWinner(char winner) // Function to show the winner or draw
{
    if (winner == PLAYER1)
    {
        printf("\nPlayer 1 (X), you are a true maestro at Tic Tac Toe! You Have WON!");
        printf("\nBetter luck next time Player 2 (O)...");
    }
    else if (winner == PLAYER2)
    {
        printf("\nSuch unconventional tactics Player 2 (O), you have won!");
        printf("\nPlayer 1 (X), it is time to put in more hours of practice!");
    }
    else
    {
        printf("\nNothing Sets Both Of You Apart! It's a DRAW!");
    }
}

void setBoard() // Function for setting the 2D board to empty
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
