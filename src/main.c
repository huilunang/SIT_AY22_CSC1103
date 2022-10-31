#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include "main.h"
#include "players.h"
#include "utils.h"

// Main Function - to be replaced with gtk obj
// int play()
// {
//     char response = ' ';

//     do
//     {
//         // Initialise
//         int blankSpaces = 9;
//         char winner = ' ';
//         response = ' ';
//         setBoard();

//         // loop till there's a winner OR no more blank spaces
//         while (winner == ' ' || blankSpaces != 0)
//         {
//             printBoard();
//             playerTurn(PLAYER1);
//             --blankSpaces;
//             winner = checkWinner(); // Check if Player 1 move wins the game
//             if (winner != ' ' || blankSpaces == 0)
//                 break;

//             printBoard();
//             playerTurn(PLAYER2);
//             --blankSpaces;
//             winner = checkWinner(); // Check if Player 2 move wins the game
//             if (winner != ' ' || blankSpaces == 0)
//                 break;
//         }

//         printBoard(); // Output final board
//         showWinner(winner); // Execute showWinner function

//         printf("\n\nWould you like to play again? (Y/N): ");
//         scanf(" %c", &response);
//         response = toupper(response);
//     } while (response == 'Y'); // Loop back if user wants to play again

//     printf("\nThanks for playing!");

//     return 0;
// }

char *curPlayer;
char winner;
int blankSpaces;
int reset;
int winnerReset;

void setUp()
{
  curPlayer = PLAYER1;
  winner = ' ';
  blankSpaces = 10;
  reset = FALSE;
  winnerReset = 1;
}

// test func
static void play_callback(GtkWidget *widget, gpointer data)
{
  // get childButton position
  GtkWidget *parentWidget = gtk_widget_get_parent(data);
  GtkLayoutManager *layoutManager = gtk_widget_get_layout_manager(parentWidget);
  GtkLayoutChild *layoutChild = gtk_layout_manager_get_layout_child(layoutManager, data);
  int row = gtk_grid_layout_child_get_row(layoutChild);
  int col = gtk_grid_layout_child_get_column(layoutChild);

  // set button Label only when it's empty
  int cmpResult = strcmp(gtk_button_get_label(data), " ");
  if (cmpResult == 0)
  {
    gtk_button_set_label(data, curPlayer);
    board[row][col] = curPlayer;
    --blankSpaces;
    winner = checkWinner();
    if ((winner != ' ' && winnerReset == 0) || blankSpaces == 0)
    {
      reset = TRUE;
    }
  }
  --winnerReset;

  // to be moved to reset function
  if (reset == TRUE)
  {
    for (row = 0; row < 3; ++row)
    {
      for (col = 0; col < 3; ++col)
      {
        GtkWidget *childBtn = gtk_grid_get_child_at(parentWidget, row, col);
        gtk_button_set_label(childBtn, " ");
      }
    }

    setUp();
  }

  // set current player to the next player
  curPlayer = (curPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
}

static void quit_callback(GtkWindow *window)
{
  gtk_window_close(window);
}

// Activates main window
static void activate(GtkApplication *app, gpointer user_data)
{
  setUp();
  // Construct a GtkBuilder instance and load our UI description
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "main.ui", NULL);

  // CSS linker
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "./main.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  // Connect signal handlers to the constructed widgets.
  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button;
  char bID[8] = "button";
  char temp[2];
  for (int i = 1; i < 10; ++i)
  {
    // convert int to string
    sprintf(temp, "%d", i);
    bID[6] = temp[0];
    button = gtk_builder_get_object(builder, bID);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(play_callback), button);
  }

  button = gtk_builder_get_object(builder, "quitBtn");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_callback), window);

  gtk_widget_show(GTK_WIDGET(window));

  // We do not need the builder any more
  g_object_unref(builder);
}

int main(int argc, char *argv[])
{
#ifdef GTK_SRCDIR
  g_chdir(GTK_SRCDIR);
#endif

  GtkApplication *app = gtk_application_new("csc1103.tictactoe", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
