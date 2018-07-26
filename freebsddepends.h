#pragma once

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

size_t strnlen(const char *str, size_t len);

char *strndup(const char *str, size_t len);
