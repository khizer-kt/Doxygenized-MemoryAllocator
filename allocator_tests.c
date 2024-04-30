#include <ctest.h>
#include "allocator.h"

CTEST(Allocator, Allocation) {
    init_allocator(1024);
    void* ptr = my_malloc(128);
    ASSERT_NOT_NULL(ptr);
    my_free(ptr);
}

// Add more test cases as needed

int main(int argc, const char* argv[]) {
    return ctest_main(argc, argv);
}
