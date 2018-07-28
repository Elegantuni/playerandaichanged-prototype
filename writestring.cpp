#include "writestring.h"

void writestring(char lineBuffer[], int lineamount1, char* element, FILE *fp)
{
	for (int j = 0; j < lineamount1; j++)
	{
		lineBuffer[j] = '\0';
	}

	strncpy(lineBuffer, element, lineamount1 - 1);

	int k = 0;

	while (lineBuffer[k] != '\0')
	{
		k++;
	}

	lineBuffer[k] = '\n';

	fwrite(lineBuffer, 1, k + 1, fp);
}
