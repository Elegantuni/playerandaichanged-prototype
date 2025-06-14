#include "ncursesprintarg3.h"

void ncursesprintarg3(int y, int x, const char* c, int d, int e, int f)
{
	mvprintw(y, x, c, d, e, f);
}
