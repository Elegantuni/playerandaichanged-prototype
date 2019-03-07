#include "ncursesprint.h"

void ncursesprint(int y, int x, const char* c)
{
	mvprintw(y, x, c);
}
