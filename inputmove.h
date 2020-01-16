#ifndef __INPUTMOVE_H
#define __INPUTMOVE_H

#ifdef INITLIBTCODNOW
#include <libtcod/libtcod.h>
#endif

#ifndef INITLIBTCODNOW
#ifdef INITNCURSESNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

void inputmove(int y, int x);

#endif

