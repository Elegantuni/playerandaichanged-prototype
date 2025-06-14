#pragma once

#ifdef INITLIBTCODNOW
#include "libtcodprintarg3.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesprintarg3.h"
#endif

void videoprinterarg3(int y, int x, const char* c, int d, int e, int f);
