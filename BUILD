cc_library(
  name = "arena",
  hdrs = ["arena.h"],
  srcs = ["arena.cpp"],
  deps = [
    "@abseil-cpp//absl/status:status",
    "@abseil-cpp//absl/status:statusor",
  ]
)

cc_binary(
  name = "main",
  srcs = ["main.cc"],
)

cc_test(
  name = "arena_test",
  size = "small",
  srcs = ["arena_test.cpp"],
  deps = [
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    ":arena",
  ]
)