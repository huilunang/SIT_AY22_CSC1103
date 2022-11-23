#include "main.h"
#include "init.h"
#include "players.h"
#include "utils.h"

char *PLAYER1 = "X";
char *PLAYER2 = "O";

// AI easy mode enabled to make a easy move
static int easyMove()
{
    // get all the empty position coordinates in the board
    checkEmptyPos(boardPos);
    // randomly select a position to place the move
    int randPos = rand() % blankSpaces;

    return randPos;
}

// AI hard mode enabled to make a hard move
static int hardMove()
{
    // Losing move is preferred to no move
    int bestScore = -2;

    // For every empty position, recursively call minimax to check 
    // for the next most optimal move
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ') {
                board[row][col] = *PLAYER2;
                // AI: 1, Human Player: -1
                int score = -minimax(board, -1);
                board[row][col] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    boardPos[0][0] = row;
                    boardPos[0][1] = col;
                }
            }
        }
    }
    return 0;
}

// Minimax function to find the most optimal move to win
static int minimax(char board[3][3], int player) {
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

                // Call minimax for the next player
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

// If 1 player mode is enabled, it gets triggers next after player makes a move
void computerMove(char board[3][3], GtkGrid *grid) {
    int position;
    // 30% chance to have AI randomly choose a position
    if (aiEasyMode == TRUE && rand() % 9 <= 2) {
        position = easyMove();
    } else {
        position = hardMove();
    }

    // update GUI with move AI made
    GtkWidget *button = gtk_grid_get_child_at(grid,
                                              boardPos[position][1],
                                              boardPos[position][0]);
    gtk_button_set_label(GTK_BUTTON(button), curPlayer);

    // set to occupy board
    board[boardPos[position][0]][boardPos[position][1]] = *curPlayer;
    --blankSpaces;

    // reset the board empty position for next use
    memset(boardPos, 0, sizeof(boardPos[0][0]) * 9 * 2);
}

// Triggers when player makes a move and set player symbol on the board
void playerMove(GtkWidget *grid, gpointer data) {
    // Get grid position when user click from GUI
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
