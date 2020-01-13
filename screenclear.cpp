#include "screenclear.h"

void screenclear()
{
#ifdef INITNCURSESNOW
	clear();
#endif

#ifdef INITLIBTCODNOW
	TCODConsole::root->clear();
#endif
}

