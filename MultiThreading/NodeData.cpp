#include "NodeData.h"
#include <Grid.h>

NodeData::NodeData(int t_index, Vector2f t_position) : 
	m_position(t_position),
	m_index(t_index),
	m_marked(false),
	m_cellState(CellState::None),
	m_neighbours(new vector<NodeData*>()),
	m_pathCost(INT32_MAX),
	m_heuristic(INT32_MAX),
	m_tileWeight(0),
	m_previous(nullptr)
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

void NodeData::setTileWeight(int t_tileWeight)
{
	m_tileWeight = t_tileWeight;
}

void NodeData::setMarked(bool t_marked)
{
	m_marked = t_marked;
}

void NodeData::setPrevious(NodeData* t_data)
{
	m_previous = t_data;
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

bool NodeData::getMarked()
{
	return m_marked;
}

NodeData* NodeData::getPrevious()
{
	return m_previous;
}
