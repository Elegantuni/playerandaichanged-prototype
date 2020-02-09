#pragma once

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#ifdef INITLIBTCODNOW
#include <Windows.h>
#endif

#include <tchar.h>

int fileExists(const wchar_t *file);
