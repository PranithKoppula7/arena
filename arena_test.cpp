#include <gtest/gtest.h>

#include "absl/status/statusor.h"

#include "arena.h"

TEST(ArenaTest, AllocateOneInteger) {
    arena::Arena<int> a = arena::Arena<int>(/*bytes=*/4);

    absl::StatusOr<int*> status = a.Allocate(1);
    ASSERT_TRUE(status.ok());
    int* p = *status;

    EXPECT_EQ(*p, 1);
}

TEST(ArenaTest, AllocateTwoInteger) {
    arena::Arena<int> a = arena::Arena<int>(/*bytes=*/8);

    absl::StatusOr<int*> status1 = a.Allocate(1);
    absl::StatusOr<int*> status2 = a.Allocate(2);
    ASSERT_TRUE(status1.ok());
    ASSERT_TRUE(status2.ok());
    int* p1 = *status1; 
    int* p2 = *status2;

    EXPECT_EQ(*p1, 1);
    EXPECT_EQ(*p2, 2);
}

TEST(ArenaTest, AllocateOverflow) {
    arena::Arena<int> a = arena::Arena<int>(/*bytes=*/8);

    absl::StatusOr<int*> status1 = a.Allocate(1);
    absl::StatusOr<int*> status2 = a.Allocate(2);
    absl::StatusOr<int*> status3 = a.Allocate(3);
    ASSERT_TRUE(status1.ok());
    ASSERT_TRUE(status2.ok());
    ASSERT_FALSE(status3.ok());

    EXPECT_EQ(status3.status().code(), absl::StatusCode::kOutOfRange);
}

TEST(ArenaTest, ConstructionWithUndivisibleBytes) {
    EXPECT_THROW({arena::Arena<int>(/*bytes=*/5);}, std::invalid_argument);
}

TEST(ArenaTest, GetTypeSize) {
    ASSERT_EQ(arena::Arena<int>(/*bytes=*/4).GetTypeSize(), 4); // int = 4 bytes
}

TEST(ArenaTest, GetCurrentAllocationWithOneInteger) {
    arena::Arena<int> a = arena::Arena<int>(/*bytes=*/4);
    {
        SCOPED_TRACE("init get allocation");
        EXPECT_EQ(a.GetCurrentAllocation(), 0);
    }
    {
        SCOPED_TRACE("allocating one integer");
        EXPECT_TRUE(a.Allocate(1).ok());
        EXPECT_EQ(a.GetCurrentAllocation(), 4);
    }
}

TEST(ArenaTest, Free) {
    arena::Arena<int> a = arena::Arena<int>(/*bytes=*/4);

    absl::StatusOr<int*> status = a.Allocate(1);
    ASSERT_TRUE(status.ok());
    absl::Status freed_status = a.Free();

    EXPECT_TRUE(freed_status.ok());
}