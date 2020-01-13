#ifndef __SCREENCLEAR_H
#define __SCREENCLEAR_H

#ifdef INITNCURSESNOW
#include <ncurses.h>
#endif

#ifdef INITLIBTCODNOW
#include <libtcod.h>
#endif

void screenclear();

#endif

