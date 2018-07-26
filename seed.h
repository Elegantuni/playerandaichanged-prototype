#pragma once

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#ifdef LINUX
#include <stdlib.h>
#endif

#include <stdio.h>
#include <openssl/md5.h>
char *str2md5(const char *str, int length);
