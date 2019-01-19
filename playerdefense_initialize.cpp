#include "playerdefense_initialize.h"

int playerdefenseinitialize()
{
    FILE *fp1 = NULL;

    int theitems1 = 0;

    fp1 = fopen("PLAYERDEFENSEINIT", "r");

    loadnumber(128, &theitems1, fp1);

    fclose(fp1);

    return theitems1;
}
