#include "libtcodinput.h"

char libtcodinput()
{
	TCOD_key_t key;
	
	key = TCODConsole::checkForKeypress();

	return key.c;
}
