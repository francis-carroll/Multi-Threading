#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <NodeData.h>

using namespace std;
using namespace sf;

enum class GridSize
{
	ThirtyX,
	HundredX,
	ThousandX
};

class Grid
{
public:
	Grid(GridSize t_size, Vector2f t_nodeSize);
	~Grid();

	vector<NodeData*> getNodes();
private:
	const int THIRTY_X = 30;
	const int HUNDRED_X = 100;
	const int THOUSAND_X = 1000;

	void setupGrid();
	void thirtyGrid();
	void hundredGrid();
	void thousandGrid();

	GridSize m_gridSize;
	vector<NodeData*> m_nodes;
	Vector2f m_nodeSize;
};