#pragma once

#ifdef INITLIBTCODNOW
#include "libtcodprint.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesprint.h"
#endif

void videoprinterchar(int y, int x, const char* c, char *d);
