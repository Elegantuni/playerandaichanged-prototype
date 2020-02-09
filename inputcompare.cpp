#include "inputcompare.h"

int inputcompare(void *type, char character)
{
#ifdef INITNCURSESNOW
	if((int)(size_t)type == character)
	{
		return 1;
	}
#endif

#ifdef INITLIBTCODNOW
	if((char)(size_t)type == character)
	{
		return 1;
	}
#endif

	return 0;
}
