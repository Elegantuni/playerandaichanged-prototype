#include "ncursesprintarg1.h"

void ncursesprintarg1(int y, int x, const char* c, int d)
{
	mvprintw(y, x, c, d);
}
