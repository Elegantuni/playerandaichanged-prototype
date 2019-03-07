
#include "writenumber.h"

void writenumber(char lineBuffer[], int lineamount1, int element, FILE* fp)
{
	for (int j = 0; j < lineamount1; j++)
	{
		lineBuffer[j] = '\0';
	}

	snprintf(lineBuffer, lineamount1, "%d", element);

	int k = 0;

	while (lineBuffer[k] != '\0')
	{
		k++;
	}

	lineBuffer[k] = '\n';

	fwrite(lineBuffer, 1, k + 1, fp);
}
