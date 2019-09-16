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
    std::string start_name = start.to_string();

    // These are states that were not completely processed.
    std::queue<Node*> Q;
    Node *node = Node::getNode(start);
    node->weight = 0;
    Q.push(node);

    // Dijkstra's shortest path algorithm.
    while(!Q.empty()) {
        Node *current = Q.front();
        Q.pop();
        if (current->visited)
            continue;
        std::string current_name = current->state.to_string();
        auto neighbors = current->state.neighbors(m_walk_time);
        for (auto & e : neighbors) {
            State s = e.first;
            double cost = e.second;
            std::string name = s.to_string();
            Node *node = Node::getNode(s);
            if (node->weight > cost + current->weight) {
                   node->weight = cost + current->weight;
                   node->previous = current_name;
            }
            Q.push(node);
        }
        current->visited = true;
    }

    // Visualize the data
    std::cout << "Visited nodes: \n";
    std::vector<Node*> nodes = Node::getAllNodes();
    for (auto &e : nodes) {
        std::cout << e << '\n';
    }
    std::cout << '\n';

}

}
