#pragma once

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#ifndef INITWINDOWSNOW
#include <stdlib.h>
#endif

#include <stdio.h>
#include <openssl/md5.h>
#include <openssl/evp.h>
char *str2md5(const char *str, int length);
