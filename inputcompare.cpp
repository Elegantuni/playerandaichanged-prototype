#include "inputcompare.h"

int inputcompare(void *type, char character)
{
#ifdef INITNCURSESNOW
	if((int)type == character)
	{
		return 1;
	}
#endif

	return 0;
}
