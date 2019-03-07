#include "freebsddepends.h"

#if !defined(_MSC_VER)
size_t strnlen(const char *str, size_t len)
{
	for (size_t size = 0; size < len; size++)
	{
		if (str[size] == '\0')
			return size;
	}
	return len;
}
#endif
char *strndup(const char *str, size_t len)
{
	size_t act = strnlen(str, len);
	char *dst = (char *)malloc(act + 1);
	if (dst != 0)
	{
		memmove(dst, str, act);
		dst[act] = '\0';
	}
	return dst;
}
