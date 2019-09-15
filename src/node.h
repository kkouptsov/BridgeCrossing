#include <vector>
#include <limits>
#include "state.h"
	
#pragma once

namespace BridgeCrossing {

class Node {
public:
    State state;
    bool visited;
    double weight;

    static Node* getNode(State &s) {
        Node *node;
        std::string name = s.to_string();
        auto result = Nodes.find(name);
        if (result == Nodes.end()) {
            node = new Node(s);
            Nodes[s.to_string()] = node;
        }
        else {
            node = result->second;
        }
        return node;
    }
    static Node* getNode(std::string &name) {
        auto result = Nodes.find(name);
        if (result == Nodes.end()) {
            return nullptr;
        }
        else {
            return result->second;
        }
    }

private:
    Node(State &s) : 
        state{s}, visited{false},
        weight{std::numeric_limits<double>::infinity()}
    {
    }

    Node(const Node & n) : state{n.state}, visited{n.visited}, weight{n.weight} {}

    // Map is used to store all nodes that we encoutered indexed by their string representaton.
    static std::map<std::string, Node*> Nodes;
};

}