#include <map>
#include <queue>
#include <algorithm>

#include "Pathfinding.hpp"

Pathfinding::Pathfinding()
{

}

std::vector<Node*> Pathfinding::path(Node* a, Node* b)
{	
	if (a == b)
	{
		return {};
	}

	std::vector<Node*> visited;
	std::map<Node*, Node*> previous;
	std::queue<Node*> queue;

	//Find the target by searching on the neighbors
	queue.push(a);
	Node* current = a;
	while (current != b)
	{
		for (size_t i = 0; i < current->links.size(); i++)
		{		
			if (!isVisited(visited, current->links[i]))
			{
				queue.push(current->links[i]);
				visited.push_back(current->links[i]);
				previous[current->links[i]] = current;
			}

			if (current == b)
			{
				current = b;
				break;
			}
		}
		current = queue.front();
		queue.pop();
	}
	
	//Reconstruct the path from b
	std::vector<Node*> path;
	Node* backTrack = b;
	while (backTrack != a)
	{
		path.push_back(previous[backTrack]);
		backTrack = previous[backTrack];
	}
	std::reverse(path.begin(), path.end());
	path.push_back(b);
	return path;
}

bool Pathfinding::isVisited(const std::vector<Node*>& nodes, Node* nodeCheck)
{
	for (size_t i = 0; i < nodes.size(); i++)
		if (nodes[i] == nodeCheck)
			return true;

	return false;
}