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

void activate(GtkApplication *app, gpointer user_data);

#endif