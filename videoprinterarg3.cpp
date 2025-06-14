#include "videoprinterarg3.h"

void videoprinterarg3(int y, int x, const char* c, int d, int e, int f)
{
	#ifdef INITNCURSESNOW
	ncursesprintarg3(y, x, c, d, e, f);
	#endif

	#ifdef INITLIBTCODNOW
	libtcodprintarg3(y, x, c, d, e, f);
	#endif
}
