/*Preprocessor Statements*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/*Global Variables and Constants Declaration*/
char board[3][3];         /*Sets the 3x3 board*/
const char PLAYER1 = 'X'; /*Sets PLAYER1 to be X sign*/
const char PLAYER2 = 'O'; /*Sets PLAYER2 to be O sign*/

/*Function Prototypes*/
void restart();         /*Reset the board*/
void printBoard();      /*Output the board, to be changed to GUI linker!!!!!!!!!!!!!!!!!*/
int checkBlankSpaces(); /*Checks if there are any more available spaces for next move*/
void playerOneMove();   /*Player 1 Next Move*/
void playerTwoMove();   /*Player 2 Next Move*/
char checkWinner();     /*Check if anyone has won*/
void showWinner(char);  /*Displays the winner, either player 1 or 2*/

/*Main Function*/
int main()
{

    char winner = ' ';
    char response = ' ';

    do
    {
        /*Initialisation*/
        winner = ' ';
        response = ' ';
        restart();

        while (winner == ' ' && checkBlankSpaces() != 0) /*while loop till there's no winner AND no more blank spaces*/
        {
            printBoard(); /*Output the board*/

            playerOneMove();        /*Execute Player 1 Function*/
            winner = checkWinner(); /*Check if Player 1 move wins the game*/
            if (winner != ' ' || checkBlankSpaces() == 0)
            {
                break;
            }

            printBoard();           /*Output the board*/
            playerTwoMove();        /*Execute Player 2 Function*/
            winner = checkWinner(); /*Check if Player 2 move wins the game*/
            if (winner != ' ' || checkBlankSpaces() == 0)
            {
                break;
            }
        }

        printBoard();       /*Output final board*/
        showWinner(winner); /*Execute showWinner function*/

        printf("\nWould you like to play again? (Y/N): ");
        scanf("%c");
        scanf("%c", &response);       /*Receive the response*/
        response = toupper(response); /*Change response to uppercase only*/
    } while (response == 'Y');        /*Loop back if user wants to play again*/

    printf("Thanks for playing!"); /*Output if user does not want to play again (N)*/

    return 0;
}

void restart() /*Function for resetting the board*/
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' '; /*Resets all elements in the 2D array board to empty*/
        }
    }
}
void printBoard() /*Function for printing the board*/
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]); /*Setting the 1st row of the board*/
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]); /*Setting the 2nd row of the board*/
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]); /*Setting the 3rd row of the board*/
    printf("\n");
}
int checkBlankSpaces() /*Function to check for blank spaces in the board*/
{
    int blankSpaces = 9; /* Initialise the number of blank spaces */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                blankSpaces--; /*If the spot in the board is filled, decrease blankSpaces by 1*/
            }
        }
    }
    return blankSpaces; /*when there are no more blank spaces, then the game is over*/
}
void playerOneMove() /*Function for player one's move*/
{
    int x; /*local variable x represents row*/
    int y; /*local variable y represents column*/

    do
    {
        printf("Player 1, Enter row #(1-3): "); /*Requests input from Player 1*/
        scanf("%d", &x);
        x--; /*Decrease user input by 1, as index in an array starts with 0*/
        printf("Player 1, Enter column #(1-3): "); /*Requests input from Player 1*/
        scanf("%d", &y);
        y--; /*Decrease user input by 1, as index in an array starts with 0*/

        if (board[x][y] != ' ') /*If the selected spot has a placement then its an invalid move*/
        {
            printf("Invalid move, the spot you've selected has been filled!\n");
        }
        else
        {
            board[x][y] = PLAYER1;
            break;
        }
    } while (board[x][y] != ' '); /*Loop if the selected placement is occupied, the game will prompt the user to retry again*/
}
void playerTwoMove() /*Function for player two's move*/
{
    int x; /*local variable x represents row*/
    int y; /*local variable y represents column*/
    do
    {
        printf("Player 2, Enter Row Number (1-3): "); /*Requests input from Player 2*/
        scanf("%d", &x);
        x--; /*Decrease user input by 1, as index in an array starts with 0*/
        printf("Player 2, Enter Column Number (1-3): "); /*Requests input from Player 2*/
        scanf("%d", &y);
        y--; /*Decrease user input by 1, as index in an array starts with 0*/

        if (board[x][y] != ' ') /*If the selected spot has a placement then its an invalid move*/
        {
            printf("Invalid move, there is already a placement there.\n");
        }
        else
        {
            board[x][y] = PLAYER2;
            break;
        }
    } while (board[x][y] != ' '); /*Loop if the selected placement is occupied, the game will prompt the user to retry again*/
}

char checkWinner() /*Function to check if there's a winner*/
{
    /*check rows*/
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }
    /*check columns*/
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    /*check diagonal*/
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
void showWinner(char winner) /*Function to show the winner or draw*/
{
    if (winner == PLAYER1) /*If player 1 is the winner*/
    {
        printf("\nPlayer 1, You Are A True Maestro At Tic Tac Toe! You Have WON!");
        printf("\nBetter Luck Next Time Player 2...");
    }
    else if (winner == PLAYER2) /*If player 2 is the winner*/
    {
        printf("\nSuch Unconventional Tactics Player 2, You Have Won!");
        printf("\nPlayer 1, It Is Time To Put In More Hours Of Practice!");
    }
    else
    {
        printf("\nNothing Sets Both Of You Apart! It's a DRAW!"); /*If the match ends in a draw*/
    }
}