#include "Grid.h"

mutex Grid::m_mutex;

Grid::Grid(GridSize t_size) :
	m_gridSize(t_size),
	m_nodes(new vector<NodeData*>()),
	m_vonNewmanDirection({ 3,5,1,7 }),
	m_texture(new RenderTexture)
{
	setupGrid();
}

Grid::~Grid()
{
	for (NodeData* node : *m_nodes)
		delete node;
	delete m_nodes;
	delete m_texture;
	delete m_player;
}

vector<NodeData*>* Grid::getNodes()
{
	return m_nodes;
}

GridSize Grid::getGridSize()
{
	return m_gridSize;
}

int Grid::getCellCount()
{
	return m_cellCount;
}

RenderTexture* Grid::getTexture()
{
	return m_texture;
}

void Grid::setupRenderTexure(RectangleShape t_shape)
{
	m_texture->create(SCREEN_SIZE.x, SCREEN_SIZE.y);

	m_texture->clear();

	vector<NodeData*>* nodes = getNodes();
	for (NodeData* n : *nodes)
	{
		if (n->getCellState() == CellState::Wall)
			t_shape.setFillColor(Color::Black);
		else if (n->getCellState() == CellState::Path)
			t_shape.setFillColor(Color::Yellow);
		else
			t_shape.setFillColor(Color::White);

		t_shape.setPosition(n->getPosition());

		m_texture->draw(t_shape);
	}

	m_texture->display();
}

Vector2i Grid::getRowCol(int t_nodeIndex, int t_cellCount)
{
	return Vector2i(t_nodeIndex / int(t_cellCount), t_nodeIndex % int(t_cellCount));
}

int Grid::getIndex(int t_row, int t_col, int t_cellCount)
{
	return int(t_col + (t_row * t_cellCount));
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
	setupNodeNeighbours();
}

void Grid::thirtyGrid()
{
	m_cellCount = THIRTY_X;
	for (int i = 0; i < THIRTY_X; i++)
	{
		for (int j = 0; j < THIRTY_X; j++)
		{
			NodeData* temp = new NodeData(i * THIRTY_X + j, Vector2f(i * (SCREEN_SIZE.x / THIRTY_X), j * (SCREEN_SIZE.y / THIRTY_X)), THIRTY_GRID_ENEMIES);
			if (i == 15 && j <= 25 || 
				i == 6 && j >=5 && j < 20 ||
				i == 24 && j >= 5 && j < 20)
			{
				temp->setCellState(CellState::Wall);
			}
			m_nodes->push_back(temp);
		}
	}
}

void Grid::hundredGrid()
{
	m_cellCount = HUNDRED_X;
	for (int i = 0; i < HUNDRED_X; i++)
	{
		for (int j = 0; j < HUNDRED_X; j++)
		{
			NodeData* temp = new NodeData(i * HUNDRED_X + j, Vector2f(i * (SCREEN_SIZE.x / HUNDRED_X), j * (SCREEN_SIZE.y / HUNDRED_X)), HUNDRED_GRID_ENEMIES);
			if (i == 25 && j <= 85  ||
				i == 75 && j >= 15  ||
				j == 50 && i >= 35 && i <= 65 ||
				i == 10 && j >= 25 && j <= 75 ||
				i == 90 && j >= 25 && j <= 75 ||
				i == 50 && j >= 25 && j <= 75)
			{
				temp->setCellState(CellState::Wall);
			}
			m_nodes->push_back(temp);
		}
	}
}

void Grid::thousandGrid()
{
	m_cellCount = THOUSAND_X;
	for (int i = 0; i < THOUSAND_X; i++)
	{
		for (int j = 0; j < THOUSAND_X; j++)
		{
			NodeData* temp = new NodeData(i * THOUSAND_X + j, Vector2f(i * (SCREEN_SIZE.x / THOUSAND_X), j * (SCREEN_SIZE.y / THOUSAND_X)), THOUSAND_GRID_ENEMIES);
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
			m_nodes->push_back(temp);
		}
	}
}

void Grid::setupNodeNeighbours()
{
	//mooreNeighbours();
	vonNewmanNeighbours();
}

void Grid::mooreNeighbours()
{
	for (NodeData* node : *m_nodes) {
		//for each direction of the node
		for (int d = 0; d < 9; d++) {
			//execpt 4, the current node
			if (d == 4) { continue; }

			Vector2i temp = getRowCol(node->getIndex(), m_cellCount);
			int neighbourRow = temp.x + ((d % 3) - 1); //calculates neighbour rows
			int neighbourCol = temp.y + ((d / 3) - 1); //calculates neighbour columns

			//if the neighbor row or col is outside the boundry, skip
			if (neighbourRow >= 0 && neighbourRow < m_cellCount &&
				neighbourCol >= 0 && neighbourCol < m_cellCount)
			{
				int nodeIndex = getIndex(neighbourRow, neighbourCol, m_cellCount);
				//add the neighbour
				node->addNeighbour(m_nodes->at(nodeIndex));
			}
		}
	}
}

void Grid::vonNewmanNeighbours()
{
	for (NodeData* node : *m_nodes) {
		//for each direction of the node
		for (int d : m_vonNewmanDirection) {

			Vector2i temp = getRowCol(node->getIndex(), m_cellCount);
			int neighbourRow = temp.x + ((d % 3) - 1); //calculates neighbour rows
			int neighbourCol = temp.y + ((d / 3) - 1); //calculates neighbour columns

			//if the neighbor row or col is outside the boundry, skip
			if (neighbourRow >= 0 && neighbourRow < m_cellCount &&
				neighbourCol >= 0 && neighbourCol < m_cellCount)
			{
				int nodeIndex = getIndex(neighbourRow, neighbourCol, m_cellCount);
				//add the neighbour
				node->addNeighbour(m_nodes->at(nodeIndex));
			}
		}
	}
}
