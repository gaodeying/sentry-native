#include "../src/sentry_boot.h"

#include <inttypes.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#ifndef SENTRY_TEST_DEFINE_MAIN
#    define TEST_NO_MAIN
#endif
#include "../vendor/acutest.h"

#define CONCAT(A, B) A##B
#define SENTRY_TEST(Name) void CONCAT(test_sentry_, Name)(void **state)
#define SKIP_TEST() (void)0

#define TEST_CHECK_STRING_EQUAL(Val, ReferenceVal)                             \
    do {                                                                       \
        TEST_CHECK(strcmp(Val, ReferenceVal) == 0);                            \
        TEST_MSG("Expected: %s", ReferenceVal);                                \
        TEST_MSG("Received: %s", Val);                                         \
    } while (0)

#define TEST_CHECK_JSON_VALUE(Val, ReferenceJson)                              \
    do {                                                                       \
        char *json = sentry_value_to_json(Val);                                \
        TEST_CHECK_STRING_EQUAL(json, ReferenceJson);                          \
        sentry_free(json);                                                     \
    } while (0)

#define TEST_CHECK_INT_EQUAL(A, B)                                             \
    do {                                                                       \
        long long _a = (long long)(A);                                         \
        long long _b = (long long)(B);                                         \
        TEST_CHECK_(_a == _b, "%lld == %lld", _a, _b);                         \
    } while (0)