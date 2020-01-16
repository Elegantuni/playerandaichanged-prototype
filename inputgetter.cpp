#include "inputgetter.h"

void* inputgetter()
{
	#ifdef INITNCURSESNOW

	return (void *)ncursesinput();

	#endif

	#ifdef INITLIBTCODNOW

	return (void *)libtcodinput();

	#endif
}
