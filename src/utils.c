#include "main.h"
#include "init.h"
#include "players.h"
#include "utils.h"

void checkEmptyPos(int boardEmptyPos[9][2]) {
    countEmptyPos = 0;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {            
            if (board[row][col] == ' ') {
                boardEmptyPos[countEmptyPos][0] = row;
                boardEmptyPos[countEmptyPos][1] = col;
                ++countEmptyPos;
            }
        }
    }
}

void checkWinner(char *winner)
{
    int i;

    // check horizontal
    for (i = 0; i < 3; ++i)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            *winner = board[i][0];
            return;
        }
    }

    // check vertical
    for (i = 0; i < 3; ++i)
    {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            *winner = board[0][i];
            return;
        }
    }

    // check diagonal
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        *winner = board[0][0];
        return;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        *winner = board[0][2];
        return;
    }

    *winner = ' ';
    return;
}

int checkWinnerOrDraw()
{
    checkWinner(winner);

    if (*winner != ' ' || blankSpaces == 0)
    {
        reset = TRUE;

        if (*winner == *PLAYER1)
        {
            incCounterScore(p1Score);
            gtk_label_set_label(noticeStatusLabel, "Player 1 Won");
        }
        else if (*winner == *PLAYER2)
        {
            incCounterScore(p2Score);
            if (modeP1 == TRUE)
                gtk_label_set_label(noticeStatusLabel, "Computer Won");
            else
                gtk_label_set_label(noticeStatusLabel, "Player 2 Won");
        }
        else
        {
            incCounterScore(tieScore);
            gtk_label_set_label(noticeStatusLabel, "It's a tie");
        }

        // gtk_widget_show(winDisplayModal);
        return 1;
    }

    return 0;
}

void incCounterScore(GtkLabel *obj)
{
    int winnerCount;
    char temp[10];

    winnerCount = atoi(gtk_label_get_label(obj)) + 1;
    sprintf(temp, "%d", winnerCount);
    gtk_label_set_text(obj, temp);
}

void setBoard(GtkGrid *grid)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = ' ';
            GtkWidget *gridBtn = gtk_grid_get_child_at(grid, row, col);
            gtk_button_set_label(GTK_BUTTON(gridBtn), " ");
        }
    }
}

void setUp()
{
    strcpy(curPlayer, PLAYER1);
    *winner = ' ';
    blankSpaces = 9;
    reset = FALSE;
    setBoard(grid);
}

void resetBoard() {
    setUp();
    gtk_label_set_label(noticeStatusLabel, "Player 1's Turn");
    gtk_label_set_text(p1Score, "0");
    gtk_label_set_text(p2Score, "0");
    gtk_label_set_text(tieScore, "0");
}
