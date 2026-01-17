#include "videoprinterchar.h"

void videoprinterchar(int y, int x, const char *c, char *d)
{
	#ifdef INITNCURSESNOW
	mvprintw(y, x, c, d);
	#endif

	#ifdef INITLIBTCODNOW
	libtcodprint(y, x, c, d);
	#endif
}
