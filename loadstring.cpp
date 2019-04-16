#include "loadstring.h"

void loadstring(int lineamount1, char** element, FILE* fp1)
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
#if !defined(_MSC_VER)
	element[0] = strndup(lineBuffer, lineamount1);
#endif

#if defined(_MSC_VER)
	element[0] = _strdup(lineBuffer);
#endif
}
