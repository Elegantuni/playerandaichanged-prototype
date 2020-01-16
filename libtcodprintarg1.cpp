#include "libtcodprintarg1.h"

void libtcodprintarg1(int y, int x, const char* c, int d)
{
	TCOD_console_print(NULL, x, y, c, d);
}
