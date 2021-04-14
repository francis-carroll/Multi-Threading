#include <AStar.h>

vector<NodeData*>* AStar::astar(Grid* t_grid, NodeData* t_player , NodeData* t_enemy)
{
	std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn>* open = new std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn>();
	vector<NodeData*>* closed = new vector<NodeData*>();

	for (NodeData* data : *t_grid->getNodes())
	{
		data->setMarked(false);
		data->setPrevious(nullptr);
		data->m_pathCost = INT32_MAX;
		data->m_heuristic = INT32_MAX;
	}

	t_enemy->m_pathCost = 0;
	t_enemy->m_heuristic = calculateHeuristic(t_player, t_enemy, t_grid->getCellCount());
	open->push(t_enemy);

	while (open->size() > 0)
	{
		NodeData* current = open->top();

		if (current == t_player)
		{
			delete closed;
			delete open;
			return constructPath(t_player);
		}

		open->pop();
		closed->push_back(current);

		for (NodeData* node : *current->getNeighbours())
		{
			if (node->getCellState() == CellState::Wall)
				continue;

			float tentG = current->m_pathCost + 1 /*+ (node->getTileWeight() * 2)*/;

			if (tentG < node->m_pathCost && !node->getMarked())
			{
				current->setTileWeight(current->getTileWeight() + 1);
				node->setPrevious(current);
				node->m_pathCost = tentG;
				node->m_heuristic = calculateHeuristic(t_player, node, t_grid->getCellCount());
				node->setMarked(true);
				open->push(node);
			}
		}
	}
	delete closed;
	delete open;
	return nullptr;
}

float AStar::calculateHeuristic(NodeData* t_goal, NodeData* t_current, int t_cellCount)
{
	return abs(directDistance(t_goal->getPosition(), t_current->getPosition()));
}

vector<NodeData*>* AStar::constructPath(NodeData* t_goal)
{
	vector<NodeData*>* path = new vector<NodeData*>();
	NodeData* current = t_goal->getPrevious();
	
	while(current != nullptr)
	{
		path->push_back(current);
		if (current->getCellState() == CellState::None)
			current->setCellState(CellState::Path);
		current = current->getPrevious();
	}
	return path;
}
