#pragma once
#include <vector>
#include "Node.hpp"

class Pathfinding
{
public :
    static std::vector<Node*> path(Node* a, Node* b);

private :
    Pathfinding();
    static bool isVisited(const std::vector<Node*>& nodes, Node* nodeCheck);
};

