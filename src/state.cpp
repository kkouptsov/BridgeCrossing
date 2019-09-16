#include <vector>
#include <algorithm>
#include <utility>
#include <ostream>
#include <sstream>
#include <iostream>
#include "state.h"

namespace BridgeCrossing {

/*
   Return a vector with numbers of the hikers, which can be moved to the other side.
   val is the location of the torch: false = on the left, true = on the right.
   If val==true, pick those with the value 'true', which means they are on the right side.
   If val==false, pick those with the value 'false', whcih means they are on the left side.
*/
std::vector<int> State::get_index(bool val)
{
    std::vector<int> matches {};
    for(unsigned int i = 0; i < m_state.size(); ++i) {
        if (m_state[i] == val)
            matches.push_back(i);
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
    if (m_type) {
        // who is on the right side
        std::vector<int> index = get_index(true);
        // iterate over those on the left
        for (unsigned int i = 0; i < index.size(); ++i) {
            // make the new state
            std::vector<bool> tmp(m_state);
            // set to true meaning the hiker crossed the bridge to the right
            tmp[index[i]] = false;
            State s(tmp, !m_type);
            double cost = walk_time[index[i]];
            result.push_back(std::make_pair(s, cost));
        }
    }
    else {
        // who is on the left side
        std::vector<int> index = get_index(false);
        // iterate over pairs who can cross the bridge
        for (unsigned int i = 0; i < index.size(); ++i) {
            for (unsigned int j = i + 1; j < index.size(); ++j) {
                // make the new state
                std::vector<bool> tmp(m_state);
                // set to false meaning they crossed the bridge back
                tmp[index[i]] = true;
                tmp[index[j]] = true;
                State s(tmp, !m_type);
                // find associated cost
                double cost = std::max(walk_time[index[i]], walk_time[index[j]]);
                result.push_back(std::make_pair(s, cost));
            }
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
