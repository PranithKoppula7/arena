#include <gtest/gtest.h>

#include "absl/status/statusor.h"

#include "arena.h"

TEST(ArenaTest, AllocateOneInteger) {
    arena::Arena<int> a = arena::Arena<int>(4);

    absl::StatusOr<int*> status = a.Allocate(1);
    int* p = *status;

    ASSERT_TRUE(status.ok());
    ASSERT_EQ(*p, 1);
}

TEST(ArenaTest, GetTypeSize) {
    ASSERT_EQ(arena::Arena<int>(4).GetTypeSize(), 4); // int = 4 bytes
}