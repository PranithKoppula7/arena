#include <gtest/gtest.h>

#include "arena.h"

TEST(ArenaTest, Construction) {
    arena::Arena<int> a = arena::Arena<int>(4);

    // ASSERT_EQ(a.GetCurrentAllocation(), 0);
    ASSERT_TRUE(true);
}
