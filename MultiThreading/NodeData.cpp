#include "NodeData.h"
#include <Grid.h>

NodeData::NodeData(int t_index, Vector2f t_position, int t_enemyCount) :
	m_position(t_position),
	m_index(t_index),
	m_marked(false),
	m_cellState(CellState::None),
	m_neighbours(new vector<NodeData*>()), 
	m_tileWeight(0),
	m_occupied(false)
{
	for (int i = 0; i < t_enemyCount; i++)
	{
		m_pathCost.push_back(INT32_MAX);
		m_heuristic = INT32_MAX;
		m_previous.push_back(nullptr);
		m_marked.push_back(false);
	}
}

NodeData::~NodeData()
{
	delete m_neighbours;
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
	m_marked.at(t_id) = t_marked;
}

void NodeData::setPrevious(NodeData* t_data, int t_id)
{
	m_previous.at(t_id) = t_data;
}

void NodeData::setOccupied(bool t_bool)
{
	m_occupied = t_bool;
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

int NodeData::getTileWeight()
{
	return m_tileWeight;
}

bool NodeData::getMarked(int t_id)
{
	return m_marked.at(t_id);
}

NodeData* NodeData::getPrevious(int t_id)
{
	return m_previous.at(t_id);
}

bool NodeData::getOccupied()
{
	return m_occupied;
}
