#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <queue>
#include "test.h"
#include "state.h"
#include "node.h"

namespace BridgeCrossing {

void Test::run()
{
    State start(m_count);
    std::string name = start.to_string();

    // These are states that were not completely processed.
    std::queue<Node*> Q;
    Node *node = Node::getNode(start);
    Q.push(node);

    //
    while(!Q.empty()) {
        Node *current = Q.front();
        Q.pop();
        auto neighbors = current->state.neighbors(m_walk_time);
        for (auto & e : neighbors) {
            std::string next = e.first.to_string();
            double cost = e.second;
            // TODO
            std::cout << next << " " << cost << '\n';
        }
    }
}

}
