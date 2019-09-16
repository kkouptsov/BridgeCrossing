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

    // In Dijkstra's algorithm we need nodes ordered by increasing weight.
    auto GreaterByWeight = [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) { return a->weight > b->weight; };

    // These are states that were not completely processed.
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(GreaterByWeight)> Q(GreaterByWeight);

    // Start node
    std::shared_ptr<Node> node = Node::getNode(start);
    node->weight = 0;
    Q.push(node);

    // Dijkstra's shortest path algorithm.
    while(!Q.empty()) {
        std::shared_ptr<Node> current = Q.top(); Q.pop();
        if (current->visited)
            continue;
        current->visited = true;
        std::string current_name = current->to_string();
        auto neighbors = current->neighbors(m_walk_time);
        for (auto & e : neighbors) {
            State s = e.first;
            double cost = e.second;
            std::string name = s.to_string();
            std::shared_ptr<Node> node = Node::getNode(s);
            if (node->weight > cost + current->weight) {
                   node->weight = cost + current->weight;
                   node->previous = current_name;
            }
            Q.push(node);
        }
   }

    std::cout << "Test: " << m_test_id << '\n';

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
    std::shared_ptr<Node> end_node = Node::getNode(end_name);
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
