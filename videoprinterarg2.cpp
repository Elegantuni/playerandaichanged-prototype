#include "videoprinterarg2.h"

void videoprinterarg2(int y, int x, const char* c, int d, char* e)
{
	#ifdef INITNCURSESNOW
	ncursesprintarg2(y, x, c, d, e);
	#endif

	#ifdef INITLIBTCODNOW
	libtcodprintarg2(y, x, c, d, e);
	#endif
}
