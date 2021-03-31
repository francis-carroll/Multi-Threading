#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum class CellState
{
	None,
	Occupied,
	Wall,
	Path
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

	int pathCost;
	int heuristic;
	NodeData* prev;
	bool m_marked;
private:
	int m_index;
	Vector2f m_position;
	CellState m_cellState;
	vector<NodeData*>* m_neighbours;
};

struct CompareFn
{
	float operator()(NodeData const* node1, NodeData const* node2)
	{
		return (node1->pathCost + node1->heuristic) > (node2->pathCost + node2->heuristic);
	}
};