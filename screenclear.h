#ifndef __SCREENCLEAR_H
#define __SCREENCLEAR_H

#ifdef INITNCURSESNOW2
#include <ncurses.h>
#endif

#ifdef INITWINDOWSNOW
#include <curses.h>
#endif

#ifdef INITLIBTCODNOW
#include <libtcod/libtcod.h>
#endif

void screenclear();

#endif

