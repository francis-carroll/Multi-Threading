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

	vector<NodeData*>* getNodes();
	GridSize getGridSize();
	Vector2i getRowCol(int t_nodeIndex);
	int getIndex(int t_row, int t_col);
private:
	void setupGrid();
	void thirtyGrid();
	void hundredGrid();
	void thousandGrid();
	void setupNodeNeighbours();
	void mooreNeighbours();
	void vonNewmanNeighbours();

	GridSize m_gridSize;
	int m_cellCount;
	vector<NodeData*>* m_nodes;
	vector<int> m_vonNewmanDirection;
};