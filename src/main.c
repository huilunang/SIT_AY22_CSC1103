#include "main.h"
#include "players.h"
#include "utils.h"

static void quit_callback(GtkWindow *window)
{
  gtk_window_close(window);
}

static void reset_callback(GtkWidget *widget, gpointer data)
{
  resetBoard();
}

static void aiDifficulty_callback(GtkWidget *widget, gpointer data) {
  modeP1 = TRUE;
  resetBoard();

  if (strcmp(gtk_button_get_label(data), "Easy") == 0)
    aiEasyMode = TRUE;
  else
    // Hard mode
    aiEasyMode = FALSE;
  
  gtk_widget_hide(aiDifficultyModal);
}

static void modePlayer_callback(GtkWidget *widget, gpointer data)
{
  if (strcmp(gtk_button_get_label(data), "2 Player") == 0) {
    modeP1 = FALSE;
    resetBoard();
  } else {
    gtk_widget_show(aiDifficultyModal);
  }
  gtk_widget_hide(modeModal);
}

static void mode_callback(GtkWidget *widget, gpointer data)
{
  gtk_widget_show(modeModal);
}

static void closeModal_callback(GtkWidget *widget, gpointer data)
{
  if (strcmp(gtk_widget_get_css_name(data), "modeCloseBtn") == 0) {
    gtk_widget_hide(modeModal);
  } else {
    gtk_widget_hide(aiDifficultyModal);
  }
}

static void play_callback(GtkWidget *widget, gpointer data)
{
  // reset game
  if (reset == TRUE)
  {
    setUp();
    return;
  }

  // Set button label only if grid position not taken
  if (strcmp(gtk_button_get_label(data), " ") == 0)
  {
    playerMove(GTK_WIDGET(grid), data);

    int checkWinnerOrDrawStatus = checkWinnerOrDraw();
    if (checkWinnerOrDrawStatus == 1)
      return;

    // set curPlayer to the next player
    *curPlayer = (strcmp(curPlayer, PLAYER1) == 0) ? *PLAYER2 : *PLAYER1;

    // Play with AI is enabled
    if (modeP1 == TRUE)
    {
      // Get move from AI
      computerMove(board, grid);

      checkWinnerOrDrawStatus = checkWinnerOrDraw();
      if (checkWinnerOrDrawStatus == 1)
        return;

      *curPlayer = (strcmp(curPlayer, PLAYER1) == 0) ? *PLAYER2 : *PLAYER1;
    }
  }
}

// Activates GtkApp main window
static void activate(GtkApplication *app, gpointer user_data)
{
  // Construct a GtkBuilder instance and load our UI description
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "main.ui", NULL);

  // CSS linker
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "main.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  // Connect signal handlers to the constructed widgets
  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button;
  char gridBtnId[8] = "button";
  char temp[2];
  for (int i = 1; i < 10; ++i)
  {
    sprintf(temp, "%d", i);
    gridBtnId[6] = *temp;
    button = gtk_builder_get_object(builder, gridBtnId);
    g_signal_connect(button, "clicked", G_CALLBACK(play_callback), button);
  }

  button = gtk_builder_get_object(builder, "modeBtn");
  g_signal_connect(button, "clicked", G_CALLBACK(mode_callback), button);
  modeModal = GTK_WIDGET(gtk_builder_get_object(builder, "modeModal"));

  button = gtk_builder_get_object(builder, "1PlayerBtn");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(modePlayer_callback), button);
  button = gtk_builder_get_object(builder, "2PlayerBtn");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(modePlayer_callback), button);
  button = gtk_builder_get_object(builder, "modeCloseBtn");
  g_signal_connect(button, "clicked", G_CALLBACK(closeModal_callback), button);
  aiDifficultyModal = GTK_WIDGET(gtk_builder_get_object(builder, "aiDifficultyModal"));

  button = gtk_builder_get_object(builder, "aiEasyBtn"); 
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(aiDifficulty_callback), button);
  button = gtk_builder_get_object(builder, "aiHardBtn"); 
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(aiDifficulty_callback), button);
  button = gtk_builder_get_object(builder, "aiDiffCloseBtn");
  g_signal_connect(button, "clicked", G_CALLBACK(closeModal_callback), button);

  button = gtk_builder_get_object(builder, "resetBtn");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(reset_callback), button);

  button = gtk_builder_get_object(builder, "quitBtn");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_callback), window);

  p1Score = GTK_LABEL(gtk_builder_get_object(builder, "p1LabelScore"));
  p2Score = GTK_LABEL(gtk_builder_get_object(builder, "p2LabelScore"));
  tieScore = GTK_LABEL(gtk_builder_get_object(builder, "tieLabelScore"));
  grid = GTK_GRID(gtk_builder_get_object(builder, "playGrid"));

  // Initialise game variables
  setUp();
  modeP1 = FALSE;

  gtk_widget_show(GTK_WIDGET(window));

  // We do not need the builder any more
  g_object_unref(builder);
}

int main(int argc, char *argv[])
{
#ifdef GTK_SRCDIR
  g_chdir(GTK_SRCDIR);
#endif

  // Initialise GtkApp
  GtkApplication *app = gtk_application_new("csc1103.tictactoe", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
