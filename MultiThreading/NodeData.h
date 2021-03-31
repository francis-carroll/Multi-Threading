#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum class CellState
{
	None,
	Occupied,
	Wall
};


class NodeData
{
public:
	NodeData(int t_index, Vector2f t_position);
	~NodeData();

	void setCellState(CellState t_state);
	void addNeighbour(NodeData* t_node);

	Vector2f getPosition();
	CellState getCellState();
	vector<NodeData*>* getNeighbours();
	int getIndex();
private:
	int m_index;
	Vector2f m_position;
	CellState m_cellState;
	bool m_marked;
	vector<NodeData*>* m_neighbours;
};