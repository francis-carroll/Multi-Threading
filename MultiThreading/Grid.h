#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>
#include <NodeData.h>
#include <Player.h>
#include <mutex>

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
	int getCellCount();

	static Vector2i getRowCol(int t_nodeIndex, int t_cellCount);
	static int getIndex(int t_row, int t_col, int t_cellCount);
	static mutex m_mutex;
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
	Player* m_player;
};