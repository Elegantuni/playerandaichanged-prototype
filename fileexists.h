#pragma once

#ifdef INITWINDOWSNOW
#include <windows.h>
#endif

#ifdef INITLIBTCODNOW
#include <windows.h>
#endif

#include <tchar.h>

int fileExists(const wchar_t *file);
