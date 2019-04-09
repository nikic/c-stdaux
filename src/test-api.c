/*
 * API Visibility Tests
 * This verifies the visibility and availability of the exported API.
 */

#undef NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include "c-stdaux.h"

static _c_const_ int const_fn(void) { return 0; }
static _c_deprecated_ _c_unused_ int deprecated_fn(void) { return 0; }
_c_hidden_ int c_internal_hidden_fn(void) { return 0; }
static _c_printf_(1, 2) int printf_fn(const char *f, ...) { return 0; }
_c_public_ int c_internal_public_fn(void) { return 0; }
static _c_pure_ int pure_fn(void) { return 0; }
static _c_sentinel_ int sentinel_fn(const char *f, ...) { return 0; }
static _c_unused_ int unused_fn(void) { return 0; }

static void cleanup_fn(int p) {}
static void direct_cleanup_fn(int p) {}
C_DEFINE_CLEANUP(int, cleanup_fn);
C_DEFINE_DIRECT_CLEANUP(int, direct_cleanup_fn);

static void test_api_macros(void) {
        /* _c_cleanup_ */
        {
                _c_cleanup_(c_freep) void *foo = NULL;
                assert(!foo);
        }

        /* _c_const_ */
        {
                assert(!const_fn());
        }

        /* _c_deprecated_ */
        {
                /* see deprecated_fn() */
        }

        /* _c_hidden_ */
        {
                assert(!c_internal_hidden_fn());
        }

        /* _c_likely_ */
        {
                assert(_c_likely_(true));
        }

        /* _c_packed_ */
        {
                struct _c_packed_ FooBar {
                        int member;
                } foobar = {};

                assert(!foobar.member);
        }

        /* _c_printf_ */
        {
                assert(!printf_fn("%d", 1));
        }

        /* _c_public_ */
        {
                assert(!c_internal_public_fn());
        }

        /* _c_pure_ */
        {
                assert(!pure_fn());
        }

        /* _c_sentinel_ */
        {
                assert(!sentinel_fn("", NULL));
        }

        /* _c_unlikely_ */
        {
                assert(!_c_unlikely_(false));
        }

        /* _c_unused_ */
        {
                assert(!unused_fn());
        }

        /* C_DEFINE_CLEANUP / C_DEFINE_DIRECT_CLEANUP */
        {
                int v = 0;

                cleanup_fnp(&v);
                direct_cleanup_fnp(&v);
        }
}

static void test_api_functions(void) {
        void *fns[] = {
                (void *)c_assert,
                (void *)c_errno,
                (void *)c_free,
                (void *)c_close,
                (void *)c_fclose,
                (void *)c_closedir,
                (void *)c_freep,
                (void *)c_closep,
                (void *)c_fclosep,
                (void *)c_closedirp,
        };
        size_t i;

        for (i = 0; i < sizeof(fns) / sizeof(*fns); ++i)
                assert(!!fns[i]);
}

int main(int argc, char **argv) {
        test_api_macros();
        test_api_functions();
        return 0;
}
