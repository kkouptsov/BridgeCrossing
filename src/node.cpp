#include <iostream>
#include <string>
#include <algorithm>
#include "node.h"

namespace BridgeCrossing {

std::map<std::string, std::shared_ptr<Node>> Node::Nodes = {};

std::string Node::to_string()
{
    return state.to_string();
}

std::vector<std::pair<State, double>> Node::neighbors(std::vector<double> &walk_time)
{
    return state.neighbors(walk_time);
}

std::shared_ptr<Node> Node::getNode(State &s)
{
    std::shared_ptr<Node> node;
    std::string name = s.to_string();
    auto result = Nodes.find(name);
    if (result == Nodes.end()) {
        node = std::shared_ptr<Node>(new Node(s));
        Nodes.insert(std::make_pair(s.to_string(), node));
    }
    else {
        node = result->second;
    }
    return node;
}

std::shared_ptr<Node> Node::getNode(std::string &name)
{
    auto result = Nodes.find(name);
    if (result == Nodes.end()) {
        throw BridgeCrossing::Exception::NodeNotFound(name);
    }
    else {
        return result->second;
    }
}

std::vector<std::shared_ptr<Node>> Node::getAllNodes()
{
    std::vector<std::shared_ptr<Node>> res;
    for (auto & e : Nodes) {
        res.push_back(e.second);
    }
    return res;
}

std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Node> n)
{
    o << n->state;
    o << ',' << n->visited;
    o << ',' << n->weight;
    o << ',' << n->previous;
    return o;

}

std::vector<std::string> Node::reconstruct(std::string first, std::string last)
{
    std::vector<std::string> path;
    try {
        path.push_back(last);
        std::shared_ptr<Node> n = getNode(last);
        while(n != nullptr && n->previous != first) {
            path.push_back(n->previous);
            n = getNode(n->previous);
        }
        path.push_back(first);
        std::reverse(path.begin(), path.end());
    }
    catch  (...) {
        /*
           One of the nodes named in the data was not found.
           This should not happen, so it indicates error in logic.
           But we got an exception to catch.
           Since we may be running a batch of tests, and this may
           occur only with one of them, silently suppress the exception,
           return nonsense, and continue.
           
           TODO: better handling
        */
    }
    return path;
}

}