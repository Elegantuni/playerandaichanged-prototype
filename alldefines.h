#pragma once

#include "playercharacter_initialize.h"
#include "playerweapons_initialize.h"
#include "playerdefense_initialize.h"

const int theplayercharacter1 = playercharacterinitialize();

#define playercharacters theplayercharacter1

const int theitemnumber1 = playerweaponsinitialize();

#define allitems theitemnumber1

#define allitemsenemies 6

const int theitemnumber2 = playerdefenseinitialize();

#define alldefenseitems theitemnumber2

#define alldefenseitemsenemies 5

#define allmagics 5
#define allmagicsenemies 5

#define allarmor 5
#define allarmorenemies 5
