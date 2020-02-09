#include "libtcodprint.h"

void libtcodprint(int y, int x, const char* c)
{
	TCOD_console_printf(NULL, x, y, c);
}
