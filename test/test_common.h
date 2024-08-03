// SPDX-License-Identifier: Apache-2.0 AND MIT

#include <openssl/err.h>
#include <openssl/provider.h>
#include <stdio.h>

/* For controlled success */
#define T(e)                                 \
    if (!(e)) {                              \
        ERR_print_errors_fp(stderr);         \
        OPENSSL_die(#e, __FILE__, __LINE__); \
    }
/* For controlled failure */
#define TF(e)                                \
    if ((e)) {                               \
        ERR_print_errors_fp(stderr);         \
    } else {                                 \
        OPENSSL_die(#e, __FILE__, __LINE__); \
    }
#define cRED              "\033[1;31m"
#define cDRED             "\033[0;31m"
#define cGREEN            "\033[1;32m"
#define cDGREEN           "\033[0;32m"
#define cBLUE             "\033[1;34m"
#define cDBLUE            "\033[0;34m"
#define cNORM             "\033[m"
#define PROVIDER_NAME_OQS "oqsprovider"
#define TEST_ASSERT(e)                                 \
    {                                                  \
        if (!(test = (e)))                             \
            printf(cRED "  Test FAILED" cNORM "\n");   \
        else                                           \
            printf(cGREEN "  Test passed" cNORM "\n"); \
    }

void hexdump(const void *ptr, size_t len);
int alg_is_enabled(const char *algname);

/** \brief Loads the default provider.
 *
 * \param libctx Top-level OpenSSL context.
 *
 * \returns The default provider. */
OSSL_PROVIDER *load_default_provider(OSSL_LIB_CTX *libctx);

/* Loads the oqs-provider. */
OSSL_PROVIDER *load_oqs_provider(OSSL_LIB_CTX *libctx, const char *modulename,
                                 const char *configfile);
