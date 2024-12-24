#include "arena.h"

// #include "absl/status/status.h"
// #include "absl/status/statusor.h"

#include <stdexcept>

template <typename T>
arena::Arena<T>::Arena(size_t bytes) {
    if (bytes % sizeof(T) != 0) {
        throw std::invalid_argument("need bytes '%' sizeof(T) == 0");
    }
    total_bytes_ = bytes;
    next_addr_ = 0;
    curr_allocation_ = 0;
    bytes_ = (T*)malloc(bytes);
}

template <typename T>
T* arena::Arena<T>::Allocate(T val) {
    if (curr_allocation_ == total_bytes_) {
        throw std::out_of_range("out of memory");
        // return absl::OutOfRangeError("out of memory");
    }

    bytes_[next_addr_] = val;
    next_addr_++;
    // TODO: have to give the correct address!!!
    return bytes_;
}

template <typename T>
size_t arena::Arena<T>::GetCurrentAllocation() {
    return curr_allocation_;
}

 template class arena::Arena<int>;
