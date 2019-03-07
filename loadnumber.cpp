#include "loadnumber.h"

void loadnumber(int lineamount1, int* element, FILE* fp1)
{
	int j;
	int c;

#if defined(_MSC_VER)
	char lineBuffer[128];
	lineamount1 = 128;
#else
	char lineBuffer[lineamount1];
#endif

	for (int k = 0; k < lineamount1; k++)
	{
		lineBuffer[k] = '\0';
	}

	j = 0;

	while ((c = fgetc(fp1)) != '\n' && j < lineamount1)
	{
		lineBuffer[j] = c;

		j++;
	}

	str2int(&(*element), lineBuffer, 10);
}
