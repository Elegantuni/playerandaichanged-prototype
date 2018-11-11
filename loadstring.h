#pragma once

#include <stdio.h>

#ifdef INITWINDOWSNOW
#include "freebsddepends.h"
#elif defined(FREEBSD)
#include "freebsddepends.h"
#elif defined(INITOPENINDIANA)
#include "freebsddepends.h"
#else
#include <string.h>
#endif

void loadstring(int lineamount1, char** element, FILE* fp1);
