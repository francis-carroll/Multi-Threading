#include "NodeData.h"
#include <Grid.h>

NodeData::NodeData(int t_index, Vector2f t_position) : 
	m_position(t_position),
	m_index(t_index),
	m_marked(false),
	m_cellState(CellState::None),
	m_neighbours(new vector<NodeData*>()),
	pathCost(INT32_MAX),
	heuristic(INT32_MAX)
{
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
