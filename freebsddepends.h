#pragma once

#ifdef INITOPENINDIANA
#include <cstdlib>
#include <cstring>
#endif

#ifdef FREEBSD
#include <cstdlib>
#include <cstring>
#endif

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#ifndef INITWINDOWSNOW
#if !defined(_MSC_VER)
size_t strnlen(const char *str, size_t len);
#endif
#endif

char *strndup(const char *str, size_t len);
