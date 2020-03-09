#include "utl.c"
#include <utl/assert.h>
#include <utl/log.h>
#include <utl/test.h>

#include <cmc/sortedlist.h>

CMC_GENERATE_SORTEDLIST(sl, sortedlist, size_t)

struct sortedlist_ftab_val *sl_ftab_val =
    &(struct sortedlist_ftab_val){ .cmp = cmp,
                                   .cpy = copy,
                                   .str = str,
                                   .free = custom_free,
                                   .hash = hash,
                                   .pri = pri };

CMC_CREATE_UNIT(sortedlist_test, true, {
    CMC_CREATE_TEST(new, {
        struct sortedlist *sl = sl_new(1000000, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);
        cmc_assert_not_equals(ptr, NULL, sl->buffer);
        cmc_assert_equals(size_t, 1000000, sl_capacity(sl));
        cmc_assert_equals(size_t, 0, sl_count(sl));
        cmc_assert_not_equals(ptr, NULL, sl->buffer);

        sl_free(sl);
    });

    CMC_CREATE_TEST(new[capacity = 0], {
        struct sortedlist *sl = sl_new(0, sl_ftab_val);

        cmc_assert_equals(ptr, NULL, sl);
    });

    CMC_CREATE_TEST(new[capacity = UINT64_MAX], {
        struct sortedlist *sl = sl_new(UINT64_MAX, sl_ftab_val);

        cmc_assert_equals(ptr, NULL, sl);
    });

    CMC_CREATE_TEST(clear[count capacity], {
        struct sortedlist *sl = sl_new(100, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        for (size_t i = 0; i < 50; i++)
            cmc_assert(sl_insert(sl, i));

        cmc_assert_equals(size_t, 50, sl_count(sl));

        sl_clear(sl);

        cmc_assert_equals(size_t, 0, sl_count(sl));
        cmc_assert_equals(size_t, 100, sl_capacity(sl));

        sl_free(sl);
    });

    CMC_CREATE_TEST(buffer_growth[capacity = 1], {
        struct sortedlist *sl = sl_new(1, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        for (size_t i = 0; i < 50; i++)
            cmc_assert(sl_insert(sl, i));

        sl_sort(sl);

        cmc_assert_equals(size_t, 50, sl_count(sl));
        cmc_assert_array_sorted_any(size_t, sl->buffer, cmp, 0, sl->count - 1);

        sl_free(sl);
    });

    CMC_CREATE_TEST(insert, {
        struct sortedlist *sl = sl_new(100, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        cmc_assert(sl_insert(sl, 1));

        sl_free(sl);
    });

    CMC_CREATE_TEST(remove, {
        struct sortedlist *sl = sl_new(100, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        cmc_assert(sl_insert(sl, 32));

        cmc_assert(sl_remove(sl, 0));

        sl_free(sl);
    });

    CMC_CREATE_TEST(remove[count = 0], {
        struct sortedlist *sl = sl_new(100, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        cmc_assert(!sl_remove(sl, 0));

        sl_free(sl);
    });

    CMC_CREATE_TEST(remove[out of range], {
        struct sortedlist *sl = sl_new(100, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        cmc_assert(sl_insert(sl, 32));

        cmc_assert(!sl_remove(sl, 2));

        sl_free(sl);
    });

    CMC_CREATE_TEST(index_of, {
        struct sortedlist *sl = sl_new(1, sl_ftab_val);

        cmc_assert_not_equals(ptr, NULL, sl);

        for (size_t i = 0; i < 20; i++)
            cmc_assert(sl_insert(sl, i % 10));

        /* 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9 */
        cmc_assert_equals(size_t, 4, sl_index_of(sl, 2, true));
        cmc_assert_equals(size_t, 5, sl_index_of(sl, 2, false));

        cmc_assert_equals(size_t, 0, sl_index_of(sl, 0, true));
        cmc_assert_equals(size_t, 1, sl_index_of(sl, 0, false));

        cmc_assert(sl_remove(sl, 0));

        cmc_assert_equals(size_t, 0, sl_index_of(sl, 0, true));
        cmc_assert_equals(size_t, 0, sl_index_of(sl, 0, false));

        cmc_assert(sl_remove(sl, 0));

        cmc_assert_equals(size_t, sl_count(sl), sl_index_of(sl, 0, true));
        cmc_assert_equals(size_t, sl_count(sl), sl_index_of(sl, 0, false));

        sl_free(sl);
    });
});
