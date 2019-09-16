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
    std::string previous;

    static Node* getNode(State &s)
    {
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

    static Node* getNode(std::string &name)
    {
        auto result = Nodes.find(name);
        if (result == Nodes.end()) {
            return nullptr;
        }
        else {
            return result->second;
        }
    }

    static std::vector<Node*> getAllNodes()
    {
        std::vector<Node*> res;
        for (auto & e : Nodes) {
            res.push_back(e.second);
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& o, const Node* n);

private:
    Node(State &s) : 
        state{s}, visited{false},
        weight{100000.}
    {
    }

    Node(const Node & n) : state{n.state}, visited{n.visited}, weight{n.weight}, previous{} {}

    // Map is used to store all nodes that we encoutered indexed by their string representaton.
    static std::map<std::string, Node*> Nodes;
};

}