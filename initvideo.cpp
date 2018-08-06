#include "initvideo.h"
#ifndef INITWINDOWSNOW
#include <ncurses.h>
#else
#include <curses.h>
#endif

void initvideo(int hitpointsy, int hitpointsx)
{
	#ifdef INITNCURSESNOW
	
	initscr();
		
	resize_term(hitpointsy, hitpointsx);

	noecho();
	
	cbreak();

	#endif
}
