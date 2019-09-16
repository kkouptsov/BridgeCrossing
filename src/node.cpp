#include <iostream>
#include <string>
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

}