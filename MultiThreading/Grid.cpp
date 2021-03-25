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
			if (i == 15 && j <= 25 || 
				i == 6 && j >=5 && j < 20 ||
				i == 24 && j >= 5 && j < 20)
			{
				temp->setCellState(CellState::Wall);
			}
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
			if (i == 25 && j <= 85  ||
				i == 75 && j >= 15  ||
				j == 50 && i >= 35 && i <= 65 ||
				i == 10 && j >= 25 && j <= 75 ||
				i == 90 && j >= 25 && j <= 75 ||
				i == 50 && j >= 25 && j <= 75)
			{
				temp->setCellState(CellState::Wall);
			}
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
			if (i == 200 && j <= 850 ||
				i == 400 && j >= 250 ||
				i == 600 && j <= 850 ||
				i == 800 && j >= 250 ||
				i == 100 && j >= 150 && j <= 850 ||
				i == 300 && j >= 250 && j <= 950 ||
				i == 500 && j >= 150 && j <= 850 ||
				i == 700 && j >= 250 && j <= 950 ||
				i == 900 && j >= 150 && j <= 850 ||
				i == 50 && j >= 400 && j <= 600 ||
				i == 150 && j >= 400 && j <= 600 ||
				i == 250 && j >= 400 && j <= 600 ||
				i == 350 && j >= 400 && j <= 600 ||
				i == 450 && j >= 400 && j <= 600 ||
				i == 550 && j >= 400 && j <= 600 ||
				i == 650 && j >= 400 && j <= 600 ||
				i == 750 && j >= 400 && j <= 600 ||
				i == 850 && j >= 400 && j <= 600 ||
				i == 950 && j >= 400 && j <= 600)
			{
				temp->setCellState(CellState::Wall);
			}
			m_nodes.push_back(temp);
		}
	}
}
