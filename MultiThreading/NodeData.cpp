#include "NodeData.h"
#include <Grid.h>

NodeData::NodeData(int t_index, Vector2f t_position, int t_enemyCount) :
	m_position(t_position),
	m_index(t_index),
	m_cellState(CellState::None),
	m_neighbours(new vector<NodeData*>()), 
	m_tileWeight(0),
	m_occupied(false),
	m_heuristic((float)INT32_MAX),
	m_pathCost(new vector<pair<int, int>>()),
	m_marked(new vector<pair<int, bool>>()),
	m_previous(new vector<pair<int, NodeData*>>())
{
}

NodeData::~NodeData()
{
	delete m_neighbours;
	delete m_pathCost;
	delete m_marked;
	delete m_previous;
}

void NodeData::setCellState(CellState t_state)
{
	m_cellState = t_state;
}

void NodeData::addNeighbour(NodeData* t_node)
{
	m_neighbours->push_back(t_node);
}

void NodeData::setTileWeight(int t_tileWeight)
{
	m_tileWeight = t_tileWeight;
}

void NodeData::setMarked(bool t_marked, int t_id)
{
	for (pair<int, bool> pair : *m_marked)
	{
		if (pair.first == t_id)
		{
			pair.second = t_marked;
			return;
		}
	}
	m_marked->push_back(pair<int, int>(t_id, t_marked));
}

void NodeData::setPrevious(NodeData* t_data, int t_id)
{
	for (pair<int, NodeData*> pair : *m_previous)
	{
		if (pair.first == t_id)
		{
			pair.second = t_data;
			return;
		}
	}
	m_previous->push_back(pair<int, NodeData*>(t_id, t_data));
}

void NodeData::setOccupied(bool t_bool)
{
	m_occupied = t_bool;
}

void NodeData::setPathCost(int t_pathCost, int t_id)
{
	for (pair<int, int> pair : *m_pathCost)
	{
		if (pair.first == t_id)
		{
			pair.second = t_pathCost;
			return;
		}
	}
	m_pathCost->push_back(pair<int, int>(t_id, t_pathCost));
}

void NodeData::setHeuristic(float t_heuristic)
{
	m_heuristic = t_heuristic;
}

Vector2f NodeData::getPosition()
{
	return m_position;
}

CellState NodeData::getCellState()
{
	return m_cellState;
}

vector<NodeData*>* NodeData::getNeighbours()
{
	return m_neighbours;
}

int NodeData::getIndex()
{
	return m_index;
}

float NodeData::getHeuristic()
{
	return m_heuristic;
}

int NodeData::getTileWeight()
{
	return m_tileWeight;
}

vector<pair<int, NodeData*>>* NodeData::getPreviouss()
{
	return m_previous;
}

vector<pair<int, bool>>* NodeData::getMarkeds()
{
	return m_marked;
}

bool NodeData::getMarked(int t_id)
{
	for (pair<int, bool> pair : *m_marked)
	{
		if (pair.first == t_id)
		{
			return pair.second;
		}
	}
	return false;
}

NodeData* NodeData::getPrevious(int t_id)
{
	for (pair<int, NodeData*> pair : *m_previous)
	{
		if (pair.first == t_id)
		{
			return pair.second;
		}
	}
	return nullptr;
}

bool NodeData::getOccupied()
{
	return m_occupied;
}

int NodeData::getPathCost(int t_id)
{
	for (pair<int, int> pair : *m_pathCost)
	{
		if (pair.first == t_id)
		{
			return pair.second;
		}
	}
	return INT32_MAX;
}

vector<pair<int, int>>* NodeData::getPathCosts()
{
	return m_pathCost;
}
