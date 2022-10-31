#include "main.h"
#include "utils.h"

char *PLAYER1 = "X";
char *PLAYER2 = "O";

// Player
void playerTurn(char playerSym)
{
    int row, col;

    printf("\n----- %c's TURN -----\n", playerSym);
    do
    {
        do {
            printf("Enter row #(1-3): ");
            scanf("%d", &row);
        } while (row < 1 || row > 3);
        --row; // decrease for array index

        do {
            printf("Enter col #(1-3): ");
            scanf("%d", &col);
        } while (col < 1 || col > 3);
        --col; // decrease for array index

        if (board[row][col] != ' ') {
            printf("\nInvalid move, the spot you've selected is occupied!\n");
        }
        else {
            board[row][col] = playerSym;
            break;
        }
            
    } while (board[row][col] != ' ');
}

// Ai
