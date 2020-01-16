#pragma once

#ifdef INITLIBTCODNOW
#include "libtcodprint.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesprint.h"
#endif

void videoprinternorm(int y, int x, const char* c);
