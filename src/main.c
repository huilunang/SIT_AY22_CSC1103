#include "main.h"
#include "players.h"
#include "utils.h"

// Main Function - to be replaced with gtk obj
int main()
{
    char response = ' ';

    do
    {
        // Initialise
        int blankSpaces = 9;
        char winner = ' ';
        response = ' ';
        setBoard();

        // loop till there's a winner OR no more blank spaces
        while (winner == ' ' || blankSpaces != 0)
        {
            printBoard();
            playerTurn(PLAYER1);
            --blankSpaces;
            winner = checkWinner(); // Check if Player 1 move wins the game
            if (winner != ' ' || blankSpaces == 0)
                break;

            printBoard();
            playerTurn(PLAYER2);
            --blankSpaces;
            winner = checkWinner(); // Check if Player 2 move wins the game
            if (winner != ' ' || blankSpaces == 0)
                break;
        }

        printBoard(); // Output final board
        showWinner(winner); // Execute showWinner function

        printf("\n\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);
    } while (response == 'Y'); // Loop back if user wants to play again

    printf("\nThanks for playing!");

    return 0;
}