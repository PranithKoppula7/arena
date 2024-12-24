#include <stddef.h>

namespace arena {
template <typename T>
class Arena {
public:
    Arena(size_t bytes);
    T* Allocate(T val);

    size_t GetCurrentAllocation();
private:
    T* bytes_;
    size_t next_addr_;
    size_t total_bytes_;
    size_t curr_allocation_;
};
}