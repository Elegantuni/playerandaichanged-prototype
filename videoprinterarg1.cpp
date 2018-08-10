#include "videoprinterarg1.h"

void videoprinterarg1(int y, int x, const char* c, int d)
{
	#ifdef INITNCURSESNOW
	ncursesprintarg1(y, x, c, d);
	#endif
}
