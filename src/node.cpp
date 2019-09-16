#include <iostream>
#include <string>
#include <algorithm>
#include "node.h"

namespace BridgeCrossing {

std::map<std::string, Node*> Node::Nodes = {};

std::ostream& operator<<(std::ostream& o, const Node* n)
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
    path.push_back(last);
    Node *n = getNode(last);
    while(n != nullptr && n->previous != first) {
        path.push_back(n->previous);
        n = getNode(n->previous);
    }
    path.push_back(first);
    std::reverse(path.begin(), path.end());
    return path;
}

}