#include "ncursesprintchar.h"

void ncursesprintchar(int y, int x, const char* c, char *d)
{
	mvprintw(y, x, c, d);
}
