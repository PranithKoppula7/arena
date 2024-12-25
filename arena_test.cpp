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

TEST(ArenaTest, AllocateTwoInteger) {
    arena::Arena<int> a = arena::Arena<int>(8);

    absl::StatusOr<int*> status1 = a.Allocate(1);
    absl::StatusOr<int*> status2 = a.Allocate(2);
    int* p1 = *status1; 
    int* p2 = *status2;

    ASSERT_TRUE(status1.ok());
    ASSERT_TRUE(status2.ok());
    ASSERT_EQ(*p1, 1);
    ASSERT_EQ(*p2, 2);
}

TEST(ArenaTest, GetTypeSize) {
    ASSERT_EQ(arena::Arena<int>(4).GetTypeSize(), 4); // int = 4 bytes
}