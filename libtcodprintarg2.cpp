#include "libtcodprintarg2.h"

void libtcodprintarg2(int y, int x, const char* c, int d, char* e)
{
	TCOD_console_print(NULL, x, y, c, d, e);
}
