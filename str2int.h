#pragma once

#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
	STR2INT_SUCCESS,
	STR2INT_OVERFLOW,
	STR2INT_UNDERFLOW,
	STR2INT_INCONVERTIBLE
} str2int_errno;

str2int_errno str2int(int *out, char *s, int base);