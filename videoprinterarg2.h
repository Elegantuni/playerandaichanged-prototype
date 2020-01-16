#pragma once

#ifdef INITLIBTCODNOW
#include "libtcodprintarg2.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesprintarg2.h"
#endif

void videoprinterarg2(int y, int x, const char* c, int d, char* e);
