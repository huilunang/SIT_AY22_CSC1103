#include "main.h"
#include "init.h"
#include "players.h"
#include "utils.h"

char *PLAYER1 = "X";
char *PLAYER2 = "O";

// Player
void playerMove(GtkWidget *grid, gpointer data) {
    // Get grid position from GUI
    GtkLayoutManager *layoutManager = gtk_widget_get_layout_manager(grid);
    GtkLayoutChild *layoutChild = gtk_layout_manager_get_layout_child(layoutManager, data);
    int row = gtk_grid_layout_child_get_row(GTK_GRID_LAYOUT_CHILD(layoutChild));
    int col = gtk_grid_layout_child_get_column(GTK_GRID_LAYOUT_CHILD(layoutChild));

    // update GUI
    gtk_button_set_label(data, curPlayer);

    // set to occupy board
    board[row][col] = *curPlayer;
    --blankSpaces;
}

// AI
void computerMove(char board[3][3], GtkGrid *grid) {

    if (aiEasyMode == TRUE) {
        srand(time(0));
        
        // enable 60% of chance to have AI randomly choose a position
        if (rand() % 10 >= 4) {
            // get all the empty position coordinates in the board
            checkEmptyPos(boardEmptyPos);
            // randomly select a position to place the move
            int randPos = rand() % countEmptyPos;

            // update GUI
            GtkWidget *button = gtk_grid_get_child_at(grid,
                                                    boardEmptyPos[randPos][1],
                                                    boardEmptyPos[randPos][0]);
            gtk_button_set_label(GTK_BUTTON(button), curPlayer);

            // set to occupy board
            board[boardEmptyPos[randPos][0]][boardEmptyPos[randPos][1]] = *PLAYER2;
            --blankSpaces;

            // reset the board empty position for next use
            memset(boardEmptyPos, 0, sizeof(boardEmptyPos[0][0]) * 9 * 2);

            return;
        }
    }

    int bestScore = -2;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ') {
                board[row][col] = *PLAYER2;
                // AI: 1, Human Player: -1
                int score = -minimax(board, -1);
                board[row][col] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    aiMove[0] = row;
                    aiMove[1] = col;
                }
            }
        }
    }

    // update GUI
    GtkWidget *button = gtk_grid_get_child_at(grid, aiMove[1], aiMove[0]);
    gtk_button_set_label(GTK_BUTTON(button), curPlayer);

    // set to occupy board
    board[aiMove[0]][aiMove[1]] = *curPlayer;
    --blankSpaces;
}

int minimax(char board[3][3], int player) {
    checkWinner(winner);
    int addWinner = (*winner == *PLAYER2) ? 1 : -1;
    if (*winner != ' ') {
        *winner = ' ';
        return addWinner * player;
    }

    int move = -1;
    // Losing moves are preferred to no move
    int bestScore = -2;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Board position is empty
            if (board[row][col] == ' ') {
                // Try the move
                char playSymbol = (player == 1) ? *PLAYER2 : *PLAYER1;
                board[row][col] = playSymbol;

                int score = -minimax(board, player*-1);

                // Pick the move that's worst for the opponent
                if (score > bestScore) {
                    bestScore = score;
                    move = 1;
                }

                // Reset board position after try
                board[row][col] = ' ';
            }
        }
    }
    // AI never make any movement
    if (move == -1)
        return 0;
    return bestScore;
}
