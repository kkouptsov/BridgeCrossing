#include <vector>
#include <iostream>
#include "test.h"

void run_test(int test_id, int count, std::vector<double>& walk_time, double crossing_time)
{
    // testing code
    // TODO: replace with the actual test
    std::cout << test_id << " " << count << "\n";
    std::cout << "[";
    for (auto &e : walk_time) {
        std::cout << e << ", ";
    }
    std::cout << "]\n";
    std::cout << crossing_time << "\n";
    std::cout << "\n";
}