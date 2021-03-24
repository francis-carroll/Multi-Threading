#include "NodeData.h"

NodeData::NodeData(int t_index, Vector2f t_position) : 
	m_position(t_position),
	m_index(t_index),
	m_marked(false),
	m_occupied(false)
{
}

NodeData::~NodeData()
{
}
