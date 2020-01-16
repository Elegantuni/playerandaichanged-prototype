#ifndef __SCREENREFRESH_H
#define __SCREENREFRESH_H

#ifdef INITNCURSESNOW
#include <ncurses.h>
#endif

#ifdef INITLIBTCODNOW
#include <libtcod/libtcod.h>
#endif

void screenrefresh();

#endif

