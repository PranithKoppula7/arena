#include <stddef.h>

#include "absl/status/statusor.h"

namespace arena {
template <typename T>
class Arena {
public:
    Arena(size_t bytes);
    absl::StatusOr<T*> Allocate(T val);

    size_t GetCurrentAllocation();
    size_t GetTypeSize();
private:
    T* bytes_;
    size_t type_size_;
    size_t next_addr_;
    size_t total_bytes_;
};
}