#include "inputgetter.h"

void* inputgetter()
{
	#ifdef INITNCURSESNOW

	return (void *)ncursesinput();

	#endif
}
