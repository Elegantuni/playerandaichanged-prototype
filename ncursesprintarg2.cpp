#include "ncursesprintarg2.h"

void ncursesprintarg2(int y, int x, const char* c, int d, char* e)
{
	mvprintw(y, x, c, d, e);
}
