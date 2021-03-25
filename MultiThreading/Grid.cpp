#include "Grid.h"

Grid::Grid(GridSize t_size) :
	 m_gridSize(t_size)
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

GridSize Grid::getGridSize()
{
	return m_gridSize;
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
			NodeData* temp = new NodeData(i * THIRTY_X + j, Vector2f(i * (SCREEN_SIZE.x / THIRTY_X), j * (SCREEN_SIZE.y / THIRTY_X)));
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
			NodeData* temp = new NodeData(i * HUNDRED_X + j, Vector2f(i * (SCREEN_SIZE.x / HUNDRED_X), j * (SCREEN_SIZE.y / HUNDRED_X)));
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
			NodeData* temp = new NodeData(i * THOUSAND_X + j, Vector2f(i * (SCREEN_SIZE.x / THOUSAND_X), j * (SCREEN_SIZE.y / THOUSAND_X)));
			m_nodes.push_back(temp);
		}
	}
}
