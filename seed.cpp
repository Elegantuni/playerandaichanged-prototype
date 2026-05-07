#include "seed.h"

#ifdef INITOPENSSL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

char *str2md5(const char *str, int length) {
    int n;
    EVP_MD_CTX* c = EVP_MD_CTX_new();;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    EVP_DigestInit_ex(c, EVP_md5(), NULL);

    while (length > 0) {
        if (length > 512) {
            EVP_DigestUpdate(c, str, 512);
        } else {
            EVP_DigestUpdate(c, str, length);
        }

        length -= 512;
        str += 512;
    }

    EVP_DigestFinal_ex(c, (unsigned char *)out, (unsigned int *)out);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}
#endif
