#include <vector>
#include <algorithm>
#include <utility>
#include <ostream>
#include <sstream>
#include <iostream>
#include "state.h"

namespace BridgeCrossing {

/*
   Return a vector with numbers of the hikers, which are on the specified side.
*/
std::vector<int> State::index(bool val)
{
    std::vector<int> matches {};
    auto i = m_state.begin(), end = m_state.end();
    int pos = 0;
    for (; i != end; ++i, ++pos) {
        if (*i == val) {
            matches.push_back(pos);
        }
    }
    return matches;
}

/*
   For a given state get a list of the neighboring states in the graph
   along with the edge weight (or cost of crossing).
*/
std::vector<std::pair<State, double>> State::neighbors(std::vector<double> &walk_time)
{
    std::vector<std::pair<State, double>> result{};
    if (type()) {
        // who is on the right side
        std::vector<int> right = index(true);
        // iterate over pairs who can cross the bridge
        for (unsigned int i = 0; i < right.size(); ++i) {
            for (unsigned int j = 1; j < right.size(); ++j) {
                // make the new state
                std::vector<bool> tmp(m_state);
                // set to false meaning they crossed the bridge back
                tmp[right[i]] = false;
                tmp[right[j]] = false;
                State s(tmp, !m_type);
                // find associated cost
                double cost = std::max(walk_time[right[i]], walk_time[right[j]]);
                result.push_back(std::make_pair(s, cost));
            }
        }
    }
    else {
        // who is on the left side
        std::vector<int> left = index(false);
        // iterate over those on the left
        for (unsigned int i = 0; i < left.size(); ++i) {
            // make the new state
            std::vector<bool> tmp(m_state);
            // set to true meaning the hiker crossed the bridge to the right
            tmp[left[i]] = true;
            State s(tmp, !m_type);
            double cost = walk_time[left[i]];
            result.push_back(std::make_pair(s, cost));
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& o, const State & s)
{
    for (auto && e : s.m_state) {
        o << (e ? '1' : '0');
    }
    o << (s.m_type ? 'R' : 'L');
    return o;
}

std::string State::to_string()
{
    std::stringstream s;
    for (auto && e : this->m_state) {
        s << (e ? '1' : '0');
    }
    s << (this->m_type ? 'R' : 'L');
    return s.str();
}

}
