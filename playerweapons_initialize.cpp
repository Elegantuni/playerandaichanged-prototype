#include "playerweapons_initialize.h"

int playerweaponsinitialize()
{
    FILE *fp1 = NULL;

    int theitems1 = 0;

    fp1 = fopen("PLAYERWEAPONSINIT", "r");

    loadnumber(128, &theitems1, fp1);

    fclose(fp1);

    return theitems1;
}
