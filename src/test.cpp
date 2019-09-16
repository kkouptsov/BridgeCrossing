#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <queue>
#include <string>
#include "test.h"
#include "state.h"
#include "node.h"

namespace BridgeCrossing {

void Test::run()
{
    State start(m_count);
    State end(m_count, 1, true);
    std::string start_name = start.to_string();
    std::string end_name = end.to_string();

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

#if 0
    // Visualize the data
    std::cout << "Visited nodes:\n";
    std::vector<Node*> nodes = Node::getAllNodes();
    for (auto &e : nodes) {
        std::cout << e << '\n';
    }
    std::cout << '\n';
 #endif

    // Get weight
    Node* end_node = Node::getNode(end_name);
    std::cout << "Total crossing time: ";
    std::cout << end_node->weight << '\n';
    if (std::abs(end_node->weight - m_crossing_time) < 1.e-3) {
        std::cout << "Test suceeded\n";
    }
    else {
        std::cout << "Test failed. ";
        std::cout << "Expected crossing time: " << m_crossing_time << "\n";
    }

    // Get path
    std::vector<std::string> path = Node::reconstruct(start_name, end_name);
    for (auto &e : path) {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    std::cout << "----------------------------------------------------\n";
}

}
