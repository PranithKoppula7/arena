#include <gtest/gtest.h>

#include "arena.h"

TEST(ArenaTest, Construction) {
    arena::Arena<int> a = arena::Arena<int>(4);

    ASSERT_EQ(a.GetCurrentAllocation(), 0);
}

TEST(ArenaTest, GetTypeSize) {
    ASSERT_EQ(arena::Arena<int>(4).GetTypeSize(), 4); // int = 4 bytes
}