#include <vector>
#include <limits>
#include <memory>
#include "state.h"
#include "exceptions.h"

#pragma once

namespace BridgeCrossing {

class Node {
private:
    State state;

public:
    /*
       Public for simplicity. These could be private with get() and set().
    */
    bool visited;
    double weight;
    std::string previous;

    /**
     * String representation of the state in this node.
     */
    std::string to_string();

    /**
     * 
     */
    std::vector<std::pair<State, double>> neighbors(std::vector<double> &walk_time);

    /**
     * Find the existing node corresponding to this state or create a new one.
     */
    static std::shared_ptr<Node> getNode(State &s);

    /**
     * Find the existing state corresponding to this string representation.
     */
    static std::shared_ptr<Node> getNode(std::string &name);

    /**
     * Return a list of all encountered.
     */
    static std::vector<std::shared_ptr<Node>> getAllNodes();

    /**
     * Reconstruct a path between start and end nodes, if possible.
     * If the path cannot be reconstructed, return an empty vector.
     */
    static std::vector<std::string> reconstruct(std::string start, std::string end);

    /**
     * Serialize the node to stream.
     */
    friend std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Node> n);

private:
    Node(State &s) : state{s}, visited{false}, weight{-1.} { }

    Node(const Node & n) : state{n.state}, visited{n.visited}, weight{n.weight}, previous{} {}

    /**
     * Nodes is used to store all nodes that we encoutered indexed by their string representaton.
     */
    static std::map<std::string, std::shared_ptr<Node>> Nodes;
};

}