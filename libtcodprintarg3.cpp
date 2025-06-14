#include "libtcodprintarg3.h"

void libtcodprintarg3(int y, int x, const char* c, int d, int e, int f)
{
	TCOD_console_printf(NULL, x, y, c, d, e, f);
}
