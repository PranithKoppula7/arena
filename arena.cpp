#include "arena.h"

#include "absl/status/status.h"

template <typename T>
arena::Arena<T>::Arena(size_t bytes) {
    bytes_ = bytes;
}

template <typename T>
absl::Status arena::Arena<T>::Allocate(T val) {
    if (curr_allocation_ == bytes_) {
        return absl::OutOfRangeError("out of memory");
    }

    return absl::OkStatus();
}
