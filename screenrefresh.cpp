#include "screenrefresh.h"

void screenrefresh()
{
#ifdef INITNCURSESNOW
	refresh();
#endif

#ifdef INITLIBTCODNOW
	TCODConsole::flush();
#endif
}

