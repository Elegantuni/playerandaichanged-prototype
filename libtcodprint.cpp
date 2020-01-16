#include "libtcodprint.h"

void libtcodprint(int y, int x, const char* c)
{
	TCOD_console_print(NULL, x, y, c);
}
