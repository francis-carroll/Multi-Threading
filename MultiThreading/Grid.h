#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>
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
	Grid(GridSize t_size);
	~Grid();

	vector<NodeData*> getNodes();
	GridSize getGridSize();
private:
	void setupGrid();
	void thirtyGrid();
	void hundredGrid();
	void thousandGrid();

	GridSize m_gridSize;
	vector<NodeData*> m_nodes;
};