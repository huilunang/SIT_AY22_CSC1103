

#include "main.h"
#include "players.h"
#include "utils.h"


static void play_callback(GtkWidget *widget, gpointer data)
{
  // get childButton position
  GtkWidget *parentWidget = gtk_widget_get_parent(data);
  GtkLayoutManager *layoutManager = gtk_widget_get_layout_manager(parentWidget);
  GtkLayoutChild *layoutChild = gtk_layout_manager_get_layout_child(layoutManager, data);
  int row = gtk_grid_layout_child_get_row(GTK_GRID_LAYOUT_CHILD(layoutChild));
  int col = gtk_grid_layout_child_get_column(GTK_GRID_LAYOUT_CHILD(layoutChild));

  // setUp game again
  if (reset == TRUE)
  {
    setUp();
    setGrid(parentWidget);
    return;
  }

  // set button Label only when it's empty
  int cmpResult = strcmp(gtk_button_get_label(data), " ");
  if (cmpResult == 0)
  {
    gtk_button_set_label(data, curPlayer);
    board[row][col] = *curPlayer;
    --blankSpaces;
  }

  checkWinner(winner);
  
  if (*winner != ' ' || blankSpaces == 0) {
    g_print("\nTHE WINNER IS: %s", winner);
    reset = TRUE;

    // GtkBuilder *builder = gtk_builder_new();
    // gtk_builder_add_from_file(builder, "main.ui", NULL);
    // GObject *winnerLabel;
    // if (*winner == *PLAYER1)
    //   winnerLabel = gtk_builder_get_object(builder, "p1LabelScore");
    // else
    //   winnerLabel = gtk_builder_get_object(builder, "p2LabelScore");
  
    
    // char temp[2] = "a";
    // int winnerCount = (*gtk_label_get_label(GTK_LABEL(winnerLabel)) - '0') + 1;
    // g_print("\nThis is winnerCount: %d", winnerCount);
    // sprintf(temp, "%d", winnerCount);
    // gtk_label_set_label(GTK_LABEL(winnerLabel), temp);
    // g_print("\nThis is label: %s", gtk_label_get_label(GTK_LABEL(winnerLabel)));

    // g_object_unref(builder);
  }
  
  // set current player to the next player
  *curPlayer = (strcmp(curPlayer, PLAYER1) == 0) ? *PLAYER2 : *PLAYER1;
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
    g_signal_connect(button, "clicked", G_CALLBACK(play_callback), button);
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
