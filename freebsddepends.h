#pragma once

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#ifndef INITWINDOWSNOW
size_t strnlen(const char *str, size_t len);
#endif

char *strndup(const char *str, size_t len);
