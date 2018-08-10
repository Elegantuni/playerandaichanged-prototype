#pragma once

#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif

void ncursesprintarg2(int y, int x, const char* c, int d, char* e);
