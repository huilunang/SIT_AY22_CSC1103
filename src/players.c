#include "main.h"
#include "players.h"
#include "utils.h"

char *PLAYER1 = "X";
char *PLAYER2 = "O";

// Player
void playerMove(GtkWidget *grid, gpointer data) {
    // Get grid position
    GtkLayoutManager *layoutManager = gtk_widget_get_layout_manager(grid);
    GtkLayoutChild *layoutChild = gtk_layout_manager_get_layout_child(layoutManager, data);
    int row = gtk_grid_layout_child_get_row(GTK_GRID_LAYOUT_CHILD(layoutChild));
    int col = gtk_grid_layout_child_get_column(GTK_GRID_LAYOUT_CHILD(layoutChild));

    gtk_button_set_label(data, curPlayer);
    board[row][col] = *curPlayer;
    --blankSpaces;
}

// AI
/* NOTE: DO THE EASY MINMAX CHECK HERE */
// Easy MINIMAX still wip
/*int minimax(char board[3][3], int player) {
    checkWinner(winner);
    int addWinner = (*winner == 'O') ? 1 : -1;
    if (*winner != ' ') {
        *winner = ' ';
        return addWinner * player;
    }
    int move = -1;
    // Losing moves are preferred to no move
    int bestScore = -2;
    srand(0)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            // Board position is empty
            if (board[row][col] == ' ') {
                if ( rand() % 10 >= 4) { 
                  board[i] = rand() % 9;
                }
                // Try the move
                char playSymbol = (player == 1) ? 'O' : 'X';
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
}*/





void computerMove(char board[3][3], GtkGrid *grid) {
    int bestScore = -2;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == ' ') {
                board[row][col] = 'O';
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

    GtkWidget *button = gtk_grid_get_child_at(grid, aiMove[1], aiMove[0]);
    gtk_button_set_label(GTK_BUTTON(button), curPlayer);
    board[aiMove[0]][aiMove[1]] = *curPlayer;
    --blankSpaces;
}

int minimax(char board[3][3], int player) {
    checkWinner(winner);
    int addWinner = (*winner == 'O') ? 1 : -1;
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
                char playSymbol = (player == 1) ? 'O' : 'X';
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
