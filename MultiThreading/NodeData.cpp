#include "NodeData.h"

NodeData::NodeData(int t_index, Vector2f t_position) : 
	m_position(t_position),
	m_index(t_index),
	m_marked(false),
	m_cellState(CellState::None)
{
}

NodeData::~NodeData()
{
}

void NodeData::setCellState(CellState t_state)
{
	m_cellState = t_state;
}

Vector2f NodeData::getPosition()
{
	return m_position;
}

CellState NodeData::getCellState()
{
	return m_cellState;
}
