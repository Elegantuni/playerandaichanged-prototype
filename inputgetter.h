#pragma once

#ifdef INITLIBTCODNOW
#include "libtcodinput.h"
#endif

#ifdef INITNCURSESNOW
#include "ncursesinput.h"
#endif

void* inputgetter();
