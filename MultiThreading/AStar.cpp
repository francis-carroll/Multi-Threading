#include <AStar.h>

void AStar::astar(Grid* t_grid, NodeData* t_player, NodeData* t_enemy, int t_id, vector<NodeData*>* t_path)
{
	std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn>* open = new std::priority_queue<NodeData*, std::vector<NodeData*>, CompareFn>(CompareFn(t_id));

	Grid::m_mutex.lock();
	t_enemy->setPathCost(0, t_id);
	Grid::m_mutex.unlock();

	Grid::m_mutex.lock();
	t_enemy->setMarked(0, t_id);
	Grid::m_mutex.unlock();

	Grid::m_mutex.lock();
	t_enemy->setHeuristic(calculateHeuristic(t_player, t_enemy, t_grid->getCellCount()));
	Grid::m_mutex.unlock();

	Grid::m_mutex.lock();
	open->push(t_enemy);
	Grid::m_mutex.unlock();

	while (open->size() > 0)
	{
		Grid::m_mutex.lock();
		NodeData* current = open->top();
		Grid::m_mutex.unlock();

		Grid::m_mutex.lock();
		if (current == t_player)
		{
			Grid::m_mutex.unlock();

			constructPath(t_player, t_id, t_path);

			Grid::m_mutex.lock();
			for (NodeData* data : *t_grid->getNodes())
			{
				data->getPathCosts()->erase(remove_if(data->getPathCosts()->begin(),
					data->getPathCosts()->end(),
					[&](pair<int, int> t_pair)->bool {return t_pair.first == t_id; }),
					data->getPathCosts()->end());

				data->getMarkeds()->erase(remove_if(data->getMarkeds()->begin(),
					data->getMarkeds()->end(),
					[&](pair<int, bool> t_pair)->bool {return t_pair.first == t_id; }),
					data->getMarkeds()->end());

				data->getPreviouss()->erase(remove_if(data->getPreviouss()->begin(),
					data->getPreviouss()->end(),
					[&](pair<int, NodeData*> t_pair)->bool {return t_pair.first == t_id; }),
					data->getPreviouss()->end());
			}
			Grid::m_mutex.unlock();

			Grid::m_mutex.lock();
			delete open;
			Grid::m_mutex.unlock();

			return;
		}
		else
		{
			Grid::m_mutex.unlock();
		}

		Grid::m_mutex.lock();
		open->pop();
		Grid::m_mutex.unlock();

		for (NodeData* node : *current->getNeighbours())
		{
			if (node->getCellState() == CellState::Wall)
				continue;


			Grid::m_mutex.lock();
			int tentG = current->getPathCost(t_id) + 1;
			Grid::m_mutex.unlock();

			Grid::m_mutex.lock();
			if(node->getOccupied())
				tentG = current->getPathCost(t_id) + 3;
			else
				tentG = current->getPathCost(t_id) + 1;
			Grid::m_mutex.unlock();

			Grid::m_mutex.lock();
			if (tentG < node->getPathCost(t_id) && !node->getMarked(t_id))
			{
				Grid::m_mutex.unlock();

				Grid::m_mutex.lock();
				current->setTileWeight(current->getTileWeight() + 1);
				Grid::m_mutex.unlock();

				Grid::m_mutex.lock();
				node->setPrevious(current, t_id);
				Grid::m_mutex.unlock();

				Grid::m_mutex.lock();
				node->setPathCost(tentG, t_id);
				Grid::m_mutex.unlock();

				Grid::m_mutex.lock();
				node->setHeuristic(calculateHeuristic(t_player, node, t_grid->getCellCount()));
				Grid::m_mutex.unlock();

				Grid::m_mutex.lock();
				if (!node->getMarked(t_id))
				{
					Grid::m_mutex.unlock();

					Grid::m_mutex.lock();
					open->push(node);
					Grid::m_mutex.unlock();
				}
				else
				{
					Grid::m_mutex.unlock();
				}

				Grid::m_mutex.lock();
				node->setMarked(true, t_id);
				Grid::m_mutex.unlock();
			}
			else
			{
				Grid::m_mutex.unlock();
			}
		}
	}

	Grid::m_mutex.lock();
	delete open;
	Grid::m_mutex.unlock();
}

float AStar::calculateHeuristic(NodeData* t_goal, NodeData* t_current, int t_cellCount)
{
	return abs(directDistance(t_goal->getPosition(), t_current->getPosition()));
}

void AStar::constructPath(NodeData* t_goal, int t_id, vector<NodeData*>* t_path)
{
	NodeData* current;
	Grid::m_mutex.lock();
	current = t_goal->getPrevious(t_id);
	Grid::m_mutex.unlock();
	
	while(current != nullptr)
	{
		Grid::m_mutex.lock();
		t_path->push_back(current);
		Grid::m_mutex.unlock();

		Grid::m_mutex.lock();
		if (current->getCellState() == CellState::None)
			current->setCellState(CellState::Path);
		Grid::m_mutex.unlock();

		Grid::m_mutex.lock();
		current = current->getPrevious(t_id);
		Grid::m_mutex.unlock();
	}
}
