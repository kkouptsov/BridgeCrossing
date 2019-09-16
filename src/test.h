#include <vector>
#include <map>
#include <queue>
#include "state.h"

#pragma once

namespace BridgeCrossing {

class Test {

public:
    Test(int test_id, int count, std::vector<double> & walk_time, double crossing_time) :
        m_test_id {test_id}, m_count{count}, m_walk_time{walk_time}, m_crossing_time{crossing_time}
    { }

    void run();
 
private:
    int m_test_id;
    int m_count;
    std::vector<double> m_walk_time;
    double m_crossing_time;
};

}