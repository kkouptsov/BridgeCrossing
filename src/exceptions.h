
#include <stdexcept>

namespace BridgeCrossing {
namespace Exception {
    struct TestFileFormat : public std::exception 
    {
        const char* what() {
            return "Invalid format of test file";
        }
    };
}
}
