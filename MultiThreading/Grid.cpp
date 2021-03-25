#include "Grid.h"

Grid::Grid(GridSize t_size, Vector2f t_nodeSize) :
	 m_gridSize(t_size),
	 m_nodeSize(t_nodeSize)
{
	setupGrid();
}

Grid::~Grid()
{
	for (NodeData* node : m_nodes)
	{
		delete node;
	}
}

vector<NodeData*> Grid::getNodes()
{
	return m_nodes;
}

void Grid::setupGrid()
{
	switch (m_gridSize)
	{
	case GridSize::ThirtyX:
		thirtyGrid();
		break;
	case GridSize::HundredX:
		hundredGrid();
		break;
	case GridSize::ThousandX:
		thousandGrid();
		break;
	default:
		break;
	}
}

void Grid::thirtyGrid()
{
	for (int i = 0; i < THIRTY_X; i++)
	{
		for (int j = 0; j < THIRTY_X; j++)
		{
			NodeData* temp = new NodeData(i * THIRTY_X + j, Vector2f(i * m_nodeSize.x, j * m_nodeSize.y));
			m_nodes.push_back(temp);
		}
	}
}

void Grid::hundredGrid()
{
	for (int i = 0; i < HUNDRED_X; i++)
	{
		for (int j = 0; j < HUNDRED_X; j++)
		{
			NodeData* temp = new NodeData(i * HUNDRED_X + j, Vector2f(i * m_nodeSize.x, j * m_nodeSize.y));
			m_nodes.push_back(temp);
		}
	}
}

void Grid::thousandGrid()
{
	for (int i = 0; i < THOUSAND_X; i++)
	{
		for (int j = 0; j < THOUSAND_X; j++)
		{
			NodeData* temp = new NodeData(i * THOUSAND_X + j, Vector2f(i * m_nodeSize.x, j * m_nodeSize.y));
			m_nodes.push_back(temp);
		}
	}
}
