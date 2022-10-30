#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include "main.h"
#include "players.h"
#include "utils.h"

// Main Function - to be replaced with gtk obj
int play()
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

// test func
static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

static void
quit_cb (GtkWindow *window)
{
  gtk_window_close (window);
}

// Activates main window
static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  /* Construct a GtkBuilder instance and load our UI description */
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "main.ui", NULL);

  /* CSS linker */
  GtkCssProvider * cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "./main.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  /* Connect signal handlers to the constructed widgets. */
  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button = gtk_builder_get_object(builder, "button1");
  g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object(builder, "button2");
  g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object(builder, "quitBtn");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK (quit_cb), window);

  gtk_widget_show(GTK_WIDGET (window));

  /* We do not need the builder any more */
  g_object_unref(builder);
}

int
main (int   argc,
      char *argv[])
{
#ifdef GTK_SRCDIR
  g_chdir(GTK_SRCDIR);
#endif

  GtkApplication *app = gtk_application_new("gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);

  int status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}
