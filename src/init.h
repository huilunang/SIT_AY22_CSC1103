#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

GtkLabel *p1Score;
GtkLabel *p2Score;
GtkLabel *tieScore;
GtkGrid *grid;
GtkLabel *noticeStatusLabel;

void activate(GtkApplication *app, gpointer user_data);

#endif