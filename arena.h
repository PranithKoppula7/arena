#include <stddef.h>
#include "absl/status/status.h"

namespace arena {
template <typename T>
class Arena {
public:
    Arena(size_t bytes);
    absl::Status Allocate(T val);
private:
    size_t bytes_;
    size_t curr_allocation_;
};
}