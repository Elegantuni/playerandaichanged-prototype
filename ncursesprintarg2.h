#pragma once

#ifndef INITLIBTCODNOW
#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

void ncursesprintarg2(int y, int x, const char* c, int d, char* e);
