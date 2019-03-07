#pragma once

#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif

void ncursesprint(int y, int x, const char* c);
