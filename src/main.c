#include "main.h"
#include "init.h"
#include "players.h"
#include "utils.h"

int main(int argc, char *argv[])
{
  // Initialise GtkApp
  GtkApplication *app = gtk_application_new("csc1103.tictactoe", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
