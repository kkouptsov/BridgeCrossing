#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <ostream>

#pragma once

namespace BridgeCrossing {

/*
    In the beginning and after each crossing the state ofo the problem can be represented
    as a set of 0(false) and 1(true) values. The value of true means the corresponding hiker has already
    crossed the bridge and is on the "right" bank. The value of false means the hiker is still
    at the "left" bank.

    Additional bit is needed to indicate the location of the torch. "true" means it is at the right
    bank, and "false" at the left.

    A short notation of the state is "1001L", which means the first and the fouth hikers
    have crossed the bridge, and the torch is on the left bank.
*/

class State {
public: 
    /**
     * Create a state describing locations of all hikers and the torch.
     */
    State(int n, bool val = false, bool type = false) : 
        m_state(n, val), m_type{type}
    {
    }

    State(std::vector<bool> state, bool type = false) : 
        m_state(state), m_type{type}
    {
    }

    State(const State &s) : 
        m_state {s.m_state}, m_type{s.m_type}
    {
    }

    /**
     * Return a vector with numbers of the hikers, which are on the specified side.
     */
    std::vector<int> index(bool val = false);

    /**
     * Return where the torch is: true if it is on the right and false if on the left.
     */
    bool type() { return m_type; }

    /**
     * Return the list of state "neighbors", that is the states that can be obtained
     * by moving two people left->right or one person right->left, and the associated
     * cost of this move.
     */
    std::vector<std::pair<State, double>> neighbors(std::vector<double> &walk_time);

    /**
     * Return a string representation of the state.
     */
    std::string to_string();
 
    friend std::ostream& operator<<(std::ostream & o, const State & s);

private:
    std::vector<bool> m_state;
    bool m_type;
};

}