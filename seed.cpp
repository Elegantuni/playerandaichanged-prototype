#include "seed.h"

#ifdef INITOPENSSL
char *str2md5(const char *str, int length) {
	int n;
	EVP_MD_CTX* mdctx;
	const EVP_MD* md;
	unsigned char digest[4];
	char *out = (char*)malloc(33);
	unsigned int md_len;

	md = EVP_get_digestbyname("SHA256");

	mdctx = EVP_MD_CTX_new();

	EVP_DigestInit_ex(mdctx, md, NULL);

	while (length > 0) {
		if (length > 512) {
			EVP_DigestUpdate(mdctx, str, 512);
		}
		else {
			EVP_DigestUpdate(mdctx, str, length);
		}
		length -= 512;
		str += 512;
	}

	EVP_DigestFinal_ex(mdctx, digest, &md_len);

	for (n = 0; n < 4; ++n) {
		snprintf(&(out[n * 2]), 3, "%02d", (unsigned int)digest[n]);
	}

	return out;
}
#endif
