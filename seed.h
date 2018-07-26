#pragma once

#include <Windows.h>
#include <stdio.h>
#include <openssl/md5.h>
char *str2md5(const char *str, int length);
