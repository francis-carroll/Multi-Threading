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
			NodeData* temp = new NodeData(i * THIRTY_X + j, Vector2f(i * 10.0f + 10.0f, j * 10.0f));
			m_nodes.push_back(temp);
		}
	}
}

void Grid::hundredGrid()
{
}

void Grid::thousandGrid()
{
}
