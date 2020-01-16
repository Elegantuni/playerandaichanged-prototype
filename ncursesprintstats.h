#pragma once

#ifndef INITLIBTCODNOW
#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

void ncursesprintstats(int y, int x, const char* m1, int a1, char* b1, int c1, int d1, int e1, char* f1, int g1, int h1, char* i1, char* j1, char* k1, int l1);
