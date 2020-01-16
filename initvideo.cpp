#include "initvideo.h"

void initvideo(int hitpointsy, int hitpointsx)
{
	#ifdef INITNCURSESNOW
	
	initscr();
		
	resize_term(hitpointsy, hitpointsx);

	noecho();
	
	cbreak();

	#endif

	#ifdef INITLIBTCODNOW

	TCODConsole::initRoot(hitpointsx, hitpointsy, "playerandai-prototype", false);

	#endif
}
