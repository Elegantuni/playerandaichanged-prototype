#include "aicharacter_initialize.h"

int aicharacterinitialize()
{
    FILE *fp1 = NULL;

    int theitems1 = 0;

    fp1 = fopen("AICHARACTERINIT", "r");

    loadnumber(128, &theitems1, fp1);

    fclose(fp1);

    return theitems1;
}
