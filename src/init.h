#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

// Player 1 Score
GtkLabel *p1Score;
// Player 2 Score
GtkLabel *p2Score;
// Tie Score
GtkLabel *tieScore;
// GUI Grid widget
GtkGrid *grid;
// GUI Label widget to display current status of game
GtkLabel *noticeStatusLabel;

static void quit_callback(GtkWindow *window);
static void reset_callback(GtkWidget *widget, gpointer data);
static void aiDifficulty_callback(GtkWidget *widget, gpointer data);
static void modePlayer_callback(GtkWidget *widget, gpointer data);
static void closeModal_callback(GtkWidget *widget, gpointer data);
static void mode_callback(GtkWidget *widget, gpointer data);
static void play_callback(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);

#endif