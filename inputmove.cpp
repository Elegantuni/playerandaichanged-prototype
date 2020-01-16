#include "inputmove.h"

void inputmove(int y, int x)
{
#ifdef INITNCURSESNOW
	move(y, x);
#endif

#ifdef INITLIBTCODNOW
	TCOD_console_print(NULL, x, y, "@");
#endif
}

