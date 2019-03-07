#include "seed.h"

#ifdef INITOPENSSL
char *str2md5(const char *str, int length) {
	int n;
	MD5_CTX c;
	unsigned char digest[4];
	char *out = (char*)malloc(33);

	MD5_Init(&c);

	while (length > 0) {
		if (length > 512) {
			MD5_Update(&c, str, 512);
		}
		else {
			MD5_Update(&c, str, length);
		}
		length -= 512;
		str += 512;
	}

	MD5_Final(digest, &c);

	for (n = 0; n < 4; ++n) {
		snprintf(&(out[n * 2]), 3, "%02d", (unsigned int)digest[n]);
	}

	return out;
}
#endif
