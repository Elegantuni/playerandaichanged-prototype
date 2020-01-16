#pragma once

#ifdef INITLIBTCODNOW
#include "libtcodprintarg1.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesprintarg1.h"
#endif

void videoprinterarg1(int y, int x, const char* c, int d);
