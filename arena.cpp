#include "arena.h"

#include <stdexcept>

#include "absl/status/statusor.h"

template <typename T>
arena::Arena<T>::Arena(size_t bytes) {
    if (bytes % sizeof(T) != 0) {
        throw std::invalid_argument("need bytes '%' sizeof(T) == 0");
    }

    // global counts
    total_bytes_ = bytes;
    type_size_ = sizeof(T);

    // iterative counts
    next_addr_ = 0;
    curr_allocation_ = 0;

    bytes_ = (T*)malloc(bytes);
}

template <typename T>
absl::StatusOr<T*> arena::Arena<T>::Allocate(T val) {
    if (curr_allocation_ == total_bytes_) {
        return absl::OutOfRangeError("out of memory");
    }

    bytes_[next_addr_] = val;
    next_addr_++;
    curr_allocation_ += type_size_;
    return &bytes_[next_addr_ - 1];
}

template <typename T>
size_t arena::Arena<T>::GetCurrentAllocation() {
    return curr_allocation_;
}

template <typename T>
size_t arena::Arena<T>::GetTypeSize() {
    return type_size_;
}

 template class arena::Arena<int>;
