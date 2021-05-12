#include <AStar.h>

void AStar::astar(Grid* t_grid, NodeData* t_player , NodeData* t_enemy, int t_id, vector<NodeData*>* t_path)
{
	
	{
		unique_lock<mutex> lock(Grid::m_mutex);
		std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn>* open = new std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn>(CompareFn(t_id));
		vector<NodeData*>* closed = new vector<NodeData*>();

		for (NodeData* data : *t_grid->getNodes())
		{
			data->setMarked(false, t_id);
			data->setPrevious(nullptr, t_id);
			data->m_pathCost.at(t_id) = INT32_MAX;
			data->m_heuristic = INT32_MAX;
		}

		t_enemy->m_pathCost.at(t_id) = 0;
		t_enemy->m_heuristic = calculateHeuristic(t_player, t_enemy, t_grid->getCellCount());
		open->push(t_enemy);


		while (open->size() > 0)
		{
			NodeData* current = open->top();

			if (current == t_player)
			{
				constructPath(t_player, t_id, t_path);
				break;
			}

			open->pop();
			closed->push_back(current);

			for (NodeData* node : *current->getNeighbours())
			{
				if (node->getCellState() == CellState::Wall)
					continue;

				float tentG = current->m_pathCost.at(t_id) + 1;

				if (tentG < node->m_pathCost.at(t_id) && !node->getMarked(t_id))
				{
					current->setTileWeight(current->getTileWeight() + 1);
					node->setPrevious(current, t_id);
					node->m_pathCost.at(t_id) = tentG;
					node->m_heuristic = calculateHeuristic(t_player, node, t_grid->getCellCount());
					node->setMarked(true, t_id);
					open->push(node);
				}
			}
		}
		delete closed;
		delete open;
	}
}

float AStar::calculateHeuristic(NodeData* t_goal, NodeData* t_current, int t_cellCount)
{
	return abs(directDistance(t_goal->getPosition(), t_current->getPosition()));
}

void AStar::constructPath(NodeData* t_goal, int t_id, vector<NodeData*>* t_path)
{
	NodeData* current = t_goal->getPrevious(t_id);
	
	while(current != nullptr)
	{
		t_path->push_back(current);
		if (current->getCellState() == CellState::None)
			current->setCellState(CellState::Path);
		current = current->getPrevious(t_id);
	}
}
