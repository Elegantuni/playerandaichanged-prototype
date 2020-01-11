#pragma once

#ifdef INITLIBTCODNOW
#include "libtcod.hpp"
#endif

#ifndef INITLIBTCODNOW
#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

void initvideo(int hitpointsy, int hitpointsx);
