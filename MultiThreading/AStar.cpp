#include <AStar.h>

vector<NodeData*>* AStar::astar(Grid* t_grid, NodeData* t_player , NodeData* t_enemy)
{
	std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn> open;
	queue<NodeData*> closed;

	t_enemy->pathCost = 0;
	t_enemy->heuristic = calculateHeuristic(t_player, t_enemy, t_grid->getCellCount());
	open.push(t_enemy);

	while (open.size() > 0)
	{
		NodeData* current = open.top();

		if (current == t_player)
		{
			return constructPath(t_player);
		}

		open.pop();
		closed.push(current);

		for (NodeData* node : *current->getNeighbours())
		{
			if (node->getCellState() == CellState::Wall)
				continue;

			float tentG = current->pathCost + 1;
			//if (node->getCellState() == CellState::Wall) tentG += 100;

			if (tentG < node->pathCost)
			{
				node->prev = current;
				node->pathCost = current->pathCost + 1;
				node->heuristic = calculateHeuristic(t_player, node, t_grid->getCellCount());
				if (!node->m_marked)
				{
					node->m_marked = true;
					open.push(node);
				}
			}
		}
	}
	return nullptr;
}

float AStar::calculateHeuristic(NodeData* t_goal, NodeData* t_current, int t_cellCount)
{
	return abs(directDistance(t_goal->getPosition(), t_current->getPosition()));
}

vector<NodeData*>* AStar::constructPath(NodeData* t_goal)
{
	vector<NodeData*>* path = new vector<NodeData*>();
	NodeData* current = t_goal->prev;
	
	while(current->prev != nullptr)
	{
		path->push_back(current);
		current->setCellState(CellState::Path);
		current = current->prev;
	}
	return path;
}
